#include "StdAfx.h"
#include "Analyze.h"


Analyze::Analyze(void)
{
	conn = NULL;
	res = NULL;
	DBclass = new DBConnection;
	myRoot = new osg::Group;
}


Analyze::~Analyze(void)
{
}


char * Analyze::callBackValue(char *(*callfunct)(const PGresult * res,int tup_num,int field_num),const PGresult * res,int tup_num,int field_num)
{
	return callfunct(res,tup_num,field_num);
}



/*type ---0 和 ---1
  ---0 表示从选中管线的起点点号方向 计算相关联的管线
  ---1 表示从选中管线的终点点号方向 计算相关联的管线
*/
vector<CString> Analyze::getIDs(CString tableName,CString objectID,int type)
{
	//string result = "";
	//connect to db
	vector<CString> vec;
	int *row_num=new int(0);

	char *startID,*endID;
	startID = NULL;
	endID = NULL;
	if (!conn)
	{
		DBclass->ConnectToDB(conn,"192.168.1.111","5432","HRBPipe","postgres","123456");
	}
	//char *sql = "select rs.起点点号,rs.终点点号 from (select 起点点号,终点点号 from baoguan('"+tableName+"', '"+objectID+"',"+type+")) as rs";
	CString sql ;
	sql.Format("select rs.起点点号,rs.终点点号,st_astext(rs.geom) from (select 起点点号,终点点号,geom from baoguan('%s','%s','%d')) as rs",tableName,objectID,type);
	//std::cout<<"sql getIDs() is :"<<sql<<endl;
	res=DBclass->ExecSQL(conn,sql,row_num);

	for (int i=0;i<(*row_num);i++)
	{
	startID = this->callBackValue(PQgetvalue,res,i,0);
	endID = this->callBackValue(PQgetvalue,res,i,1);
	vec.push_back(startID);
	vec.push_back(endID);
	}

	return vec;
}
vector<CString> Analyze::getAllIDs(CString tableNameOfLine,CString objectID)
{
	vector<CString> vec;
	vector<CString> vec_end ;
	vector<CString> vec_start ;

	vec_end =  this->getIDs(tableNameOfLine, objectID, 0);//[F26RSG21637, F26RSG21636, F26RSG21631, F26RSG21630, F26RSG21632]
	vec_start = this->getIDs(tableNameOfLine, objectID, 1);//[F26RSG21640, F26RSG21638, F26RSG21639, F26RSG21637, F26RSG21636]

	

	for(vector<CString>::iterator it1=vec_end.begin();it1!=vec_end.end();it1++){
		CString key = (CString) *it1;
		vec.push_back(key);
	}

	
	for(vector<CString>::iterator it2=vec_start.begin();it2!=vec_start.end();it2++){
		CString key = (CString) *it2;
		vec.push_back(key);
		
	}
	
	return vec;
}

//在管点表中获取单个管点 添加marker;
void Analyze::addMarker(MapNode * mapNode,osg::Group * root,CString tableNameOfPoint,CString objectID)
{
	CString result = "";
	CString sql = "";
	char * startGeometry;
	char * endGeometry;
	startGeometry = NULL;
	endGeometry = NULL;
	sql.Format("select 附属物,st_astext(geom),地面高程,标识码 as mygeom from %s where 物探点号='%s'",tableNameOfPoint,objectID);
	std::cout<<"sql getValve()  is  :"<<sql<<endl;
	int *row_num=new int(0);
	if (!conn)
	{
		DBclass->ConnectToDB(conn,"192.168.1.111","5432","HRBPipe","postgres","123456");
		res=DBclass->ExecSQL(conn,sql,row_num);
	}else
	{
		res=DBclass->ExecSQL(conn,sql,row_num);
	}
	
	Style pin;		
	std::string noteName="hello";
	GeoPoint geoPoint;
	pin.getOrCreate<IconSymbol>()->url()->setLiteral( "E:/HRB/data/placemark32.png" );
	const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();

	// just one record
	PipePoint * _point;
	_point = NULL;
	for (int i=0;i<(*row_num);i++)
	{
		string fushuwu;//附属物;
		char * geom_temp;
		char * elevation;
		char * idOfPoint;
		fushuwu = this->callBackValue(PQgetvalue,res,i,0);
		geom_temp = this->callBackValue(PQgetvalue,res,i,1);
		elevation = this->callBackValue(PQgetvalue,res,i,2);
		idOfPoint = this->callBackValue(PQgetvalue,res,i,3);

		_point = new PipePoint(geom_temp,elevation);

		if (fushuwu == "雨水井")
		{
			myRoot->addChild(new PlaceNode(mapNode, GeoPoint(geoSRS, _point->getLon(),_point->getLat(),_point->getEle()),idOfPoint, pin));
			cout<<"添加成功"<<endl;
			objectIDsVector.insert(idOfPoint);
		}
	}
	
	/*bgMarkerLayer=new ModelLayer("bgMarker",myRoot);
	mapNode->getMap()->addModelLayer(bgMarkerLayer);*/
	if (_point!=NULL)
	{
		delete _point;
		_point = NULL;
	}
}
void Analyze::addMarkers(MapNode * mapNode,osg::Group * root,CString tableNameOfLine,CString tableNameOfPoint,CString objectID)
{
	vector<CString> IDs;
	CString geom;
	IDs = this->getAllIDs(tableNameOfLine,objectID);
	for (vector<CString>::iterator it = IDs.begin();it!=IDs.end();it++)
	{
		this->addMarker(mapNode,root,tableNameOfPoint,(*it));
	}
	bgMarkerLayer=new ModelLayer("bgMarker",myRoot);
	mapNode->getMap()->addModelLayer(bgMarkerLayer);
}

boolean Analyze::clearMarkers(MapNode * mapNode)
{
	//dynamic_cast<osgEarth::ModelLayer*>(mapNode->getMap()->getModelLayerByName("bgMarker"))->setVisible(false);
	bgMarkerLayer->setVisible(false);
	return 1;
}

