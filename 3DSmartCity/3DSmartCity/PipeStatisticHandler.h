#pragma once
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventHandler>
#include "StatisticDialog.h"
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/RectangleNode>
#include "3DSmartCity.h"
using namespace osgEarth::Annotation;

#include "makeSql.h"

class PipeStatisticHandler : public osgGA::GUIEventHandler
{
public:
	osgViewer::Viewer* mViewer;
	CPoint selectPts[2];
	bool firstClickedFlag;
	StatisticDialog** ppStatisticDlg;
	osgEarth::MapNode* mapNode;
	osgEarth::GeoPoint ConvertPoint;
	osg::Group** ppRect;
	osg::ref_ptr<RectangleNode> rectNode;
public:
	PipeStatisticHandler(osgViewer::Viewer* viewer,osgEarth::MapNode* mapNode,StatisticDialog** ppStatisticDlg,osg::Group** ppRect);
	~PipeStatisticHandler(void);
private:
	void drawRect();
	std::vector<std::string> bzms;//保存上次查询到的标识码
protected:

	void Pick(float x,float y );
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
};

