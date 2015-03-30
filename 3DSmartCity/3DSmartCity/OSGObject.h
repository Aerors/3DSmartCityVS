#pragma once

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgViewer\api\Win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgEarth/MapNode>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Sky>
#include <osgEarth/ImageLayer>
#include "3DSmartCity.h"
using namespace std;

#include "PipeStatisticHandler.h"


using namespace osgEarth;
class COSGObject
{
public:
	COSGObject(HWND hWnd);
	~COSGObject(void);
	void InitOSG();
	void InitSceneGraph();
	void InitCameraConfig();//��ʼ�����
	void PreFrameUpdate();//ǰ����
	void PostFrameUpdate();//����
	static void Render(void * ptr);//����̻߳��ⷽ��
	osg::ref_ptr<osgEarth::MapNode> mapNode;
	vector<string> layernames;
	osgEarth::ImageLayerVector imageLayerVec;

	osgViewer::Viewer *getViewer();
	void InitOsgEarth();
	void setChinaBoundariesOpacity(double opt);
	double getChinaBoundariesOpacity();
	void rmvChinaBounds();
	void addChinaBounds();


//dc--����ͳ��--------------------------------------------------------------------------
public:
	bool ifDoStatistic;
	StatisticDialog* pStatisticDlg;
	void initStatisticDlg();
	osg::Group* pRectNodeGroup;
//dc----------------------------------------------------------------------------

	//------wangsongwei  ����ģ�Ͳ����
	ModelLayerVector modelLayerVec;


private:
	HWND n_hWnd;//����һ�����
	osgViewer::Viewer * mViewer;
	osg::ref_ptr<osg::Group> mRoot;

	osg::ref_ptr<osgEarth::Util::EarthManipulator> em;
	osg::ref_ptr<osgEarth::ImageLayer> china_boundaries;
	//���� �ܵ�
private:
	map<string ,string> *pipes;
public:
	void pipeView(void);
	void buildingView(void);

};

