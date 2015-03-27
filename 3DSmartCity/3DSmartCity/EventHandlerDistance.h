#pragma once
#include <osgUtil/LineSegmentIntersector>
#include <osgEarth/MapNode>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgEarth/Map>

class CEventHandlerDistance :
	public osgGA::GUIEventHandler
{
public:
	
	BOOL isPickWorld;//是否点击世界地图
	
	void isStartTest(bool isTest);

public:
	CEventHandlerDistance(void);
	~CEventHandlerDistance(void);
	bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
	bool isTestJu;
	//状态机
	//0用户没用双击
	//1设置了起点
	//2设置了终点
	int jieduan;

	osg::ref_ptr<osg::Geode> lineStrip;//线

	osg::Vec3 startPoint;
	osg::Vec3 endPoint;
	osg::ref_ptr<osg::Vec3Array> vertex;//顶点
};

