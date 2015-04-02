#pragma once
#include "HeadFiles.h"
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventHandler>
#include <osgEarthUtil/EarthManipulator>
#include "Analyze.h"
#include "HighLightVisitor.h"
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace std;

class PickHandlerHighLight : public osgGA::GUIEventHandler
{
public:
	MapNode* mapNode;
	EarthManipulator * manip;
	osg::Group *root;
	osgViewer::Viewer* mViewer;
	osg::Node* lastSelect;
	Analyze *analyze;
public:
	PickHandlerHighLight(MapNode* mapNode,EarthManipulator * manip,osgViewer::Viewer* viewer,osg::Group *root,Analyze *bg);
	~PickHandlerHighLight(void);
protected:

	void Pick(float x,float y );
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
};

