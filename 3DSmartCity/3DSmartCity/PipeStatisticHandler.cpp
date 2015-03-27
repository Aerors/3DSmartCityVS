#include "stdafx.h"
#include "windows.h"
#include "PipeStatisticHandler.h"
#include "DBConnection.h"

PipeStatisticHandler::PipeStatisticHandler(osgViewer::Viewer* viewer,osgEarth::MapNode* mapNode,StatisticDialog** ppStatisticDlg,osg::Group** pprect)
{
	this->mViewer = viewer;
	this->mapNode = mapNode;
	this->ppStatisticDlg = ppStatisticDlg;
	this->firstClickedFlag = false;
	this->ppRect = pprect;
}


PipeStatisticHandler::~PipeStatisticHandler(void)
{
}

void PipeStatisticHandler::drawRect()
{
	const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	osgEarth::Style rectStyle;
	rectStyle.getOrCreate<PolygonSymbol>()->fill()->color() = Color(Color::Yellow, 0.3);
	rectStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
	rectStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_DRAPE;

	rectNode = new RectangleNode(
		mapNode,
		GeoPoint(geoSRS, 126.64520201450800, 45.749879500494998),
		Distance(20, Units::KILOMETERS ),
		Distance(20, Units::KILOMETERS ),
		rectStyle);

	rectNode->setUpperLeft(GeoPoint(geoSRS, (*ppStatisticDlg)->m_leftlon,(*ppStatisticDlg)->m_leftlat));
	rectNode->setLowerRight(GeoPoint(geoSRS, (*ppStatisticDlg)->m_rightlon,(*ppStatisticDlg)->m_rightlat));

	(*ppRect)->addChild(rectNode);
}

//string PipeStatisticHandler::makePolySql(double topleftlat,double topleftlon,double bottomrightlat,double bottomrightlon)
//{
//	char* p = "POLYGON((126.652002305689 45.7528259108467, 126.653364042412 45.7528259108467, 126.653364042412 45.747337756813, 126.652002305689 45.747337756813, 126.652002305689 45.7528259108467))')";
//	string begin("select 标识码,gid from (select *,");
//	string end(" as queryresult where isContain=true");
//	string s;
//	ostringstream buf;
//	buf.precision(13);  
//    buf.setf(std::ios::fixed); // 将浮点数的位数限定为小数点之后的位数 
//	buf<<"st_contains(st_geomfromtext('polygon(("<<topleftlon<<' '<<topleftlat<<','<<bottomrightlon<<' '<<topleftlat<<','<<bottomrightlon<<' '<<bottomrightlat<<','<<topleftlon<<' '<<bottomrightlat<<','<<topleftlon<<' '<<topleftlat<<"))'),ysgline_new.geom) as isContain from ysgline_new )";
//	s = buf.str();
//	cout<<s<<endl;
//	string sql;
//	sql = begin.append(s);
//	sql = sql.append(end);
//	cout<<sql<<endl;
//	//p = const_cast<char*>(s.c_str());
//	return sql;
//}

bool PipeStatisticHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	if((*ppStatisticDlg)->IsWindowVisible())
	{
		switch(ea.getEventType())
		{
		case (osgGA::GUIEventAdapter::DOUBLECLICK):
			{
				osg::Vec3d m_TempPoint1;
				const osgEarth::SpatialReference* m_pGeoSRS = mapNode->getTerrain()->getSRS();
				osgUtil::LineSegmentIntersector::Intersections inters1;
				if(mViewer->computeIntersections(ea.getX(),ea.getY(),inters1))
				{
					osgUtil::LineSegmentIntersector::Intersections::iterator iter1 = inters1.begin();
					m_TempPoint1.set(iter1->getWorldIntersectPoint().x(),iter1->getWorldIntersectPoint().y(),iter1->getWorldIntersectPoint().z());
					ConvertPoint.fromWorld(m_pGeoSRS,m_TempPoint1);
				}

				if (firstClickedFlag)
				{//第二次双击
					//ASSERT(selectPts[0].x!=0 &&selectPts[0].y!=0);
					(*ppStatisticDlg)->m_rightlat=ConvertPoint.y();
					(*ppStatisticDlg)->m_rightlon=ConvertPoint.x();

					if((*ppStatisticDlg)->m_leftlat<(*ppStatisticDlg)->m_rightlat)
					{
						double t = (*ppStatisticDlg)->m_leftlat;
						(*ppStatisticDlg)->m_leftlat = (*ppStatisticDlg)->m_rightlat;
						(*ppStatisticDlg)->m_rightlat = t;
					}
					if((*ppStatisticDlg)->m_leftlon>(*ppStatisticDlg)->m_rightlon)
					{
						double t = (*ppStatisticDlg)->m_leftlon;
						(*ppStatisticDlg)->m_leftlon = (*ppStatisticDlg)->m_rightlon;
						(*ppStatisticDlg)->m_rightlon = t;
					}

					if((*ppRect)->containsNode(rectNode))
					{
						(*ppRect)->removeChild(0,1);
					}

					drawRect();

					//select 标识码 from (select *,st_contains(st_geomfromtext('POLYGON((126.652002305689 45.7528259108467, 
					//126.653364042412 45.7528259108467, 126.653364042412 45.747337756813, 126.652002305689 45.747337756813, 126.652002305689 45.7528259108467))'),ysgline_new.geom)
					//as isContain from ysgline_new ) as queryresult where isContain=true

					//char * sql="select gid as gid , st_astext(s.geom) as startPoint,s.地面高程 as startpointelevation ,st_astext(e.geom) as endPoint,e.地面高程 as endpointelevation  from ysgpoint84 as s , ysgpoint84 as e , ysgline84 as line where line.起点点号=s.物探点号 and line.终点点号=e.物探点号";
					(*ppStatisticDlg)->m_statisticResult.ResetContent();
					DBConnection reader;
					makeSql ms;
					reader.ConnectToDB("localhost","5432","HRBPipe","postgres","123456");
					string sql = ms.makePolySql((*ppStatisticDlg)->m_leftlat,(*ppStatisticDlg)->m_leftlon,(*ppStatisticDlg)->m_rightlat,(*ppStatisticDlg)->m_rightlon);
					PGresult* res = reader.ExecSQL(const_cast<char*>(sql.c_str()));
					int field_num=PQnfields(res);
					int tuple_num=PQntuples(res);
					for(int j=0;j<tuple_num;++j)
					{
						char* s = PQgetvalue(res,j,0);
						(*ppStatisticDlg)->m_statisticResult.AddString(s);  
						char* t = PQgetvalue(res,j,1);

					}

					firstClickedFlag = false;
				}
				else
				{//第一次双击
					(*ppStatisticDlg)->m_leftlat = ConvertPoint.y();
					(*ppStatisticDlg)->m_leftlon = ConvertPoint.x();
					//(*ppRect)->setLowerRight(GeoPoint(m_pGeoSRS, ConvertPoint.x(),ConvertPoint.y()));

					firstClickedFlag = true;
				}
				(*ppStatisticDlg)->SendMessage(WM_UPDATEDATA,FALSE);

			}
		}
		return true;
	}
	return false;
}

void PipeStatisticHandler::Pick(float x,float y )
{

}