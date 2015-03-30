#include "StdAfx.h"
#include "AddClick.h"
#include<stdlib.h>
#include <string>

CAddClick::CAddClick(MapNode* mapNode,osgViewer::Viewer* viewer,CAddFlagDlg ** addlg,bool *isWindowClose)
{
	this->mapNode=mapNode;	
	this->mViewer=viewer;
	this->addlg=addlg;
	this->isWindowClose=isWindowClose;
}


CAddClick::~CAddClick(void)
{
}

bool CAddClick::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{		
 	if (!(*isWindowClose)&&(*addlg)->IsWindowVisible())
	{
		if ( ea.getEventType() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON )
		{
			osgViewer::View* view = static_cast<osgViewer::View*>(aa.asView());

			osg::Vec3d m_TempPoint1;
			const osgEarth::SpatialReference *m_pGeoSRS = mapNode->getTerrain()->getSRS();
			osgUtil::LineSegmentIntersector::Intersections inters1;
			if(mViewer->computeIntersections(ea.getX(),ea.getY(),inters1))
			{
				osgUtil::LineSegmentIntersector::Intersections:: iterator iter1 = inters1.begin();
				m_TempPoint1.set(iter1->getWorldIntersectPoint().x(),iter1->getWorldIntersectPoint().y(),iter1->getWorldIntersectPoint().z());
				ConvertPoint.fromWorld(m_pGeoSRS,m_TempPoint1);
				(*addlg)->m_Lat=ConvertPoint.y();
				(*addlg)->m_Lon=ConvertPoint.x();
				(*addlg)->geoPoint=ConvertPoint;
				(*addlg)->SendMessage(WM_UPDATEDATA_ADDMARKER, false);
			}
		}
		return true;
	}
	return false;
}