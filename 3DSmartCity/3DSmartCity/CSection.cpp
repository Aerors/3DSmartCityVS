#include "StdAfx.h"
#include "CSection.h"
#include <sstream>


CCSection::CCSection(MapNode* mapNode,osgViewer::Viewer* viewer,osg::Group * linesGroup,bool * isDrawLineStart)	
{
	clickTime=false;	//false �����һ����Ӧ, true����ڶ�����Ӧ,�����߽���
	this->mapNode=mapNode;
	this->mViewer=viewer;
	this->linesGroup=linesGroup;
	this->isDrawLineStart=isDrawLineStart;
	DBclass=new DBConnection();
	DBclass->ConnectToDB(this->conn,"localhost","5432","HRBPipe","postgres","123456");
}


CCSection::~CCSection(void)
{
}


bool CCSection::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
	if (*isDrawLineStart)
	{
		if (!clickTime && ea.getEventType() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON )
		{	
			clickTime=true;
			//if (clickTime++ ==1)
			{
				osg::Vec3d m_TempPoint1;
				const osgEarth::SpatialReference *m_pGeoSRS = mapNode->getTerrain()->getSRS();
				osgUtil::LineSegmentIntersector::Intersections inters1;
				if(mViewer->computeIntersections(ea.getX(),ea.getY(),inters1))
				{
					osgUtil::LineSegmentIntersector::Intersections:: iterator iter1 = inters1.begin();
					m_TempPoint1.set(iter1->getWorldIntersectPoint().x(),iter1->getWorldIntersectPoint().y(),iter1->getWorldIntersectPoint().z());
					startPoint.fromWorld(m_pGeoSRS,m_TempPoint1);				
				}
			}
			
		}
		else if (clickTime  && ea.getEventType() == osgGA::GUIEventAdapter::DOUBLECLICK )
		{
			clickTime=false;

			osg::Vec3d m_TempPoint1;
			const osgEarth::SpatialReference *m_pGeoSRS = mapNode->getTerrain()->getSRS();
			osgUtil::LineSegmentIntersector::Intersections inters1;
			if(mViewer->computeIntersections(ea.getX(),ea.getY(),inters1))
			{
				osgUtil::LineSegmentIntersector::Intersections:: iterator iter1 = inters1.begin();
				m_TempPoint1.set(iter1->getWorldIntersectPoint().x(),iter1->getWorldIntersectPoint().y(),iter1->getWorldIntersectPoint().z());
				endPoint.fromWorld(m_pGeoSRS,m_TempPoint1);				
			}

			//��startPoint��endPoint֮�仭��
			//TODO
			Geometry* path = new LineString();
			path->push_back(osg::Vec3d(startPoint.x(),startPoint.y(),0));   // 
			path->push_back(osg::Vec3d(endPoint.x(),endPoint.y(),0));	 // 

			Style pathStyle;
			pathStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::Red;
			pathStyle.getOrCreate<LineSymbol>()->stroke()->width() = 3.0f;
			pathStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
			pathStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;

			Feature* pathFeature = new Feature(path, m_pGeoSRS, pathStyle);
			pathFeature->geoInterp() = GEOINTERP_GREAT_CIRCLE;//GEOINTERP_RHUMB_LINE;
			

			FeatureNode* pathNode = new FeatureNode(mapNode, pathFeature);
			linesGroup->addChild( pathNode );
			*isDrawLineStart=false;
			

			findPipes(startPoint,endPoint);

			return true;
		}
	}
	return false;
}


string convertToString(double d) {		
		ostringstream out;
		out.precision(18);//����Ĭ�Ͼ���
		out << d;
		return out.str(); //������ȡ���ַ��� ��ֵ���ڴ洢��str�У��ȴ���ʽ����
}

//�����߶�����  �������ݿ������ֱ���ཻ�Ĺ���
void CCSection::findPipes(GeoPoint startPoint,GeoPoint endPoint)
{
	int *row_num=new int(0);
	string sql="select line.��ʶ��,line.�ܾ�,line.����,line.�������,line.�յ�����, \
				point1.����߳� as ���߳�,point2.����߳� as �յ�߳�,line.�������,line.̽������ \
				from ysgpoint_new as point1,ysgpoint_new as point2,(select * from ysgline_new \
				where st_intersects(geom,st_geomfromtext('linestring("+
				convertToString(startPoint.y())+" "+convertToString(startPoint.x())+
				"," +convertToString(endPoint.y())+" "+convertToString(endPoint.x())+
				")'))=true) as line \
				where line.�����=point1.��̽��� and line.�յ���=point2.��̽���";
	res=DBclass->ExecSQL(conn,const_cast<char*>(sql.c_str()),row_num);	
	for (int i=0;i<(*row_num);i++)
	{
		for (int j=1;j<8;j++)
		{
			string xx=PQgetvalue(res,i,0);
		}
	}
}
