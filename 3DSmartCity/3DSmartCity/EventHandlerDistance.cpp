#include "StdAfx.h"
#include "EventHandlerDistance.h"
#include "OSGObject.h"
#include "3DSmartCityView.h"

CEventHandlerDistance::CEventHandlerDistance(void)
{
	isPickWorld=false;//默认不点选
	isTestJu=false;
	jieduan=0;
	vertex=new osg::Vec3Array;
}


CEventHandlerDistance::~CEventHandlerDistance(void)
{

}
bool CEventHandlerDistance::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	osgViewer::Viewer *viewer=dynamic_cast<osgViewer::Viewer*>(&aa);

	if(isTestJu&&viewer)
	{
		if(ea.getEventType()==osgGA::GUIEventAdapter::DOUBLECLICK)
		{

		
		osg::Vec3d point=osg::Vec3(0,0,0);
		osgUtil::LineSegmentIntersector::Intersections intersections;
		if(viewer->computeIntersections(ea.getX(),ea.getY(),intersections))
		{
			point=intersections.begin()->getWorldIntersectPoint();
			

		}
		if(jieduan==0)
		{
			jieduan=1;
			vertex->push_back(point);//起点
			startPoint=point;


		}
		else if(jieduan==1)
		{
			endPoint=point;
			jieduan=2;
			osg::Vec3d startlla;
			osg::Vec3d endlla;
			CMainFrame*  pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		    CMy3DSmartCityView* pRightView = (CMy3DSmartCityView*)pFrame->m_wndSplitter.GetPane(0,1);
			pRightView->mOSG->mapNode->getMap()->getWorldSRS();
			
			


		}
		else if(jieduan=2)
		{
			jieduan=1;

		}
		}
	}
	return false;
}

void CEventHandlerDistance::isStartTest(bool isTest)
{
	isTestJu=isTest;

}