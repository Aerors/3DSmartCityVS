#include "StdAfx.h"
#include "AddPipe.h"
#include "HighLightVisitor.h"

AddPipe::AddPipe(void)
{
}


AddPipe::~AddPipe(void)
{
}

void AddPipe::InitAddPipe(string lineTableName,string pointTableName,string host,string port,string database,string userName,string pwd)
//void AddPipe::InitAddPipe(string lineTableName,string pointTableName,string host="localhost",string port="5432",string database="HRBPipe",string userName="postgres",string pwd="123456")
{
	this->lineTableName=lineTableName;
	this->pointTableName=pointTableName;
	
	this->host=new char[host.length()+1];
	strcpy(this->host,host.c_str());

	this->port=new char[port.length()+1];
	strcpy(this->port,port.c_str());

	this->database=new char[database.length()+1];
	strcpy(this->database,database.c_str());

	this->userName=new char[userName.length()+1];
	strcpy(this->userName,userName.c_str());

	this->pwd=new char[pwd.length()+1];
	strcpy(this->pwd,pwd.c_str());
}

char * AddPipe::callBackValue(char *(*callfunct)(const PGresult * res,int tup_num,int field_num),const PGresult * res,int tup_num,int field_num)
{
	return callfunct(res,tup_num,field_num);
}

void AddPipe::Addpipes(MapNode * mapNode)
{
	osg::ref_ptr<osg::Group>  pipeGroup=new osg::Group;
	DBConnection *DBclass=new DBConnection();
	PGconn *conn;
	PGresult *res;
	int *row_num=new int(0);
	//char * sql="select line.gid as gid , st_astext(s.geom) as startPoint ,st_astext(e.geom) as endPoint from ysgpoint84 as s , ysgpoint84 as e , ysgline84 as line where line.起点点号=s.物探点号 and line.终点点号=e.物探点号";
	string sql="select line.标识码 as gid , st_astext(s.geom) as startPoint,s.地面高程\
			   as startpointelevation ,st_astext(e.geom) as endPoint,e.地面高程 as endpointelevation\
			   from "+pointTableName+" as s , "+pointTableName+" as e , "+
			   lineTableName+" as line where line.起点点号=s.物探点号 and line.终点点号=e.物探点号";
	DBclass->ConnectToDB(conn,this->host,this->port,this->database,this->userName,this->pwd);
	res=DBclass->ExecSQL(conn,const_cast<char*>(sql.c_str()),row_num);
	char * startPointLatLon, * endPointLatLon , *startPointElevation, * endPointElevation;
	PipePoint * startPoint, * endPoint;
	if (res!=NULL)
	{
		osg::ref_ptr<osgModeling::Curve> section =new osgModeling::Curve();
		//生成圆环横截面
		{
			osg::ref_ptr<osg::Vec3Array> pathArray = new osg::Vec3Array;
			osg::Vec3 center = osg::Vec3(0.0f,0.0f,0.0f);
			//double radius=1.0f;
			int numSamples=50;
			float yaw = 0.0f;
			float yaw_delta = 2.0f*osg::PI/((float)numSamples-1.0f);

			for(int i=0;i<numSamples;++i)
			{
				osg::Vec3 position(center+osg::Vec3(sinf(yaw)*RADIUS,cosf(yaw)*RADIUS,0.0f));
				yaw -= yaw_delta;
				pathArray->push_back(position);		
			}			
			section->setPath(pathArray.get());			
		}

		for (int i=0;i<(*row_num);i++)
		{
			lineID=this->callBackValue(PQgetvalue,res,i,0);
			startPointLatLon=this->callBackValue(PQgetvalue,res,i,1);
			startPointElevation=this->callBackValue(PQgetvalue,res,i,2);
			endPointLatLon= this->callBackValue(PQgetvalue,res,i,3);			
			endPointElevation=this->callBackValue(PQgetvalue,res,i,4);

			//试验用数据
			//startPointElevation="155.0";
			//endPointElevation="155.0";
			
			startPoint=new PipePoint(startPointLatLon,startPointElevation);
			endPoint =new PipePoint(endPointLatLon,endPointElevation);

			this->APipe(mapNode,pipeGroup,section,startPoint,endPoint,lineID);
			//this->ASphere(mapNode,root,startPoint,RADIUS);
		}
	}
	
	ModelLayer* pipeLayer=new ModelLayer(lineTableName,pipeGroup);
	mapNode->getMap()->addModelLayer(pipeLayer);
	if (*row_num !=0)
	{
		delete startPoint;
		delete endPoint;
		delete DBclass;
	}
}

osg::Group* AddPipe::Addpipes(MapNode * mapNode,osg::Group * mRoot)
{
	osg::ref_ptr<osg::Group>  pipeGroup=new osg::Group;
	DBConnection *DBclass=new DBConnection();
	PGconn *conn;
	PGresult *res;
	int *row_num=new int(0);
	//char * sql="select line.gid as gid , st_astext(s.geom) as startPoint ,st_astext(e.geom) as endPoint from ysgpoint84 as s , ysgpoint84 as e , ysgline84 as line where line.起点点号=s.物探点号 and line.终点点号=e.物探点号";
	string sql="select line.标识码 as gid , st_astext(s.geom) as startPoint,s.地面高程\
			   as startpointelevation ,st_astext(e.geom) as endPoint,e.地面高程 as endpointelevation\
			   from "+pointTableName+" as s , "+pointTableName+" as e , "+
			   lineTableName+" as line where line.起点点号=s.物探点号 and line.终点点号=e.物探点号";
	DBclass->ConnectToDB(conn,this->host,this->port,this->database,this->userName,this->pwd);
	res=DBclass->ExecSQL(conn,const_cast<char*>(sql.c_str()),row_num);
	char * startPointLatLon, * endPointLatLon , *startPointElevation, * endPointElevation;
	PipePoint * startPoint, * endPoint;
	if (res!=NULL)
	{
		osg::ref_ptr<osgModeling::Curve> section =new osgModeling::Curve();
		//生成圆环横截面
		{
			osg::ref_ptr<osg::Vec3Array> pathArray = new osg::Vec3Array;
			osg::Vec3 center = osg::Vec3(0.0f,0.0f,0.0f);
			//double radius=1.0f;
			int numSamples=50;
			float yaw = 0.0f;
			float yaw_delta = 2.0f*osg::PI/((float)numSamples-1.0f);

			for(int i=0;i<numSamples;++i)
			{
				osg::Vec3 position(center+osg::Vec3(sinf(yaw)*RADIUS,cosf(yaw)*RADIUS,0.0f));
				yaw -= yaw_delta;
				pathArray->push_back(position);		
			}			
			section->setPath(pathArray.get());			
		}

		for (int i=0;i<(*row_num);i++)
		{
			lineID=this->callBackValue(PQgetvalue,res,i,0);
			startPointLatLon=this->callBackValue(PQgetvalue,res,i,1);
			startPointElevation=this->callBackValue(PQgetvalue,res,i,2);
			endPointLatLon= this->callBackValue(PQgetvalue,res,i,3);			
			endPointElevation=this->callBackValue(PQgetvalue,res,i,4);

			//试验用数据
			//startPointElevation="155.0";
			//endPointElevation="155.0";
			
			startPoint=new PipePoint(startPointLatLon,startPointElevation);
			endPoint =new PipePoint(endPointLatLon,endPointElevation);

			this->APipe(mapNode,pipeGroup,section,startPoint,endPoint,lineID);
			//this->ASphere(mapNode,root,startPoint,RADIUS);
		}
	}
	
	//ModelLayer* pipeLayer=new ModelLayer(lineTableName,pipeGroup);
	//mapNode->getMap()->addModelLayer(pipeLayer);
	mRoot->addChild(pipeGroup.get());
	pipeGroup->setName("pipes");
	pipeGroup->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	//pipeGroup->getOrCreateStateSet()->setAttribute(
	
	if (*row_num !=0)
	{
		delete startPoint;
		delete endPoint;
		delete DBclass;
	}
	return pipeGroup.get();
}

void AddPipe::APipe(MapNode * mapNode,osg::Group * group,osg::ref_ptr<osgModeling::Curve> section,PipePoint *startPoint, PipePoint * endPoint,char * lineID)
{	
	osg::ref_ptr<osg::CoordinateSystemNode> csn;
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	csn = geoSRS->createCoordinateSystemNode();

	osg::ref_ptr<osgModeling::Curve> path = new osgModeling::Curve;
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;

	double x,y,z,a,b,c;	
	csn->getEllipsoidModel()->convertLatLongHeightToXYZ(osg::DegreesToRadians(startPoint->getLat()),osg::DegreesToRadians(startPoint->getLon()),startPoint->getEle(),a,b,c);
	csn->getEllipsoidModel()->convertLatLongHeightToXYZ(osg::DegreesToRadians(endPoint->getLat()),osg::DegreesToRadians(endPoint->getLon()),endPoint->getEle(),x,y,z);
	path->addPathPoint(osg::Vec3(0.0f,0.0f,0.0f));
	path->addPathPoint(osg::Vec3(x-a,y-b,z-c));
	
	//生成
	{
		osg::ref_ptr<osgModeling::Loft> geom =
			new osgModeling::Loft( path.get(), section.get() );
		osg::Vec3Array* normals = new osg::Vec3Array;
		normals->push_back(osg::Vec3(1.0f,0.0f,1.0f));
		//normals->push_back(osg::Vec3(1.0f,0.0f,0.0f)^osg::Vec3(0.0f,0.0f,1.0f));
		geom->setNormalArray(normals, osg::Array::BIND_OVERALL);
		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(0.1f,0.2f,0.7f,0.8f)); // 
		//colors->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f)); // 
		geom->setColorArray(colors, osg::Array::BIND_PER_PRIMITIVE_SET);

		geode->addDrawable( geom.get() );
		geode->setName(string(lineTableName)+" "+lineID);
	}
	//变换到地球坐标系  修改为平移至地球表面
	{
		mt->setMatrix(osg::Matrixd::translate(a,b,c));
		mt->addChild(geode);  
		mt->setName(lineTableName);
		group->addChild(mt);
	}

}

//加管点的另外写一个类
void AddPipe::ASphere(MapNode * mapNode,osg::Group * group,PipePoint *center, double radius)
{
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	osg::ref_ptr<osg::CoordinateSystemNode> csn=mapNode->getMapSRS()->getGeographicSRS()->createCoordinateSystemNode();
	

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;

	double a,b,c;	
	csn->getEllipsoidModel()->convertLatLongHeightToXYZ(osg::DegreesToRadians(center->getLat()),osg::DegreesToRadians(center->getLon()),center->getEle(),a,b,c);
	
	{
		osg::ref_ptr<osg::Shape> sphere =new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),(float)radius);
		osg::ref_ptr<osg::ShapeDrawable> drawSphere=new osg::ShapeDrawable(sphere);
		
		osg::Vec4 color = osg::Vec4(1.0f,0.0f,1.0f,1.0f);		
		drawSphere->setColor(color);
		geode->addDrawable( drawSphere.get() );
	}
	//变换到地球坐标系  修改为平移至地球表面
	{
		mt->setMatrix(osg::Matrixd::translate(a,b,c));
		mt->addChild(geode); 
		group->addChild(mt);
	}
}