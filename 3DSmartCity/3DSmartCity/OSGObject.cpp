#include "StdAfx.h"
#include "OSGObject.h"


COSGObject::COSGObject(HWND hWnd)
{
	n_hWnd = hWnd;

	pStatisticDlg =  new StatisticDialog();
	pipes=new map<string ,string>;
	pipes->insert(pair<string,string>("ysgline_new","ysgpoint_new"));
}


COSGObject::~COSGObject(void)
{

}

void COSGObject::InitOSG()
{
	InitSceneGraph();
	InitCameraConfig();
	InitOsgEarth();
}
void COSGObject::InitSceneGraph()
{
	//初始化场景图
	mRoot=new osg::Group;
	osg::ref_ptr<osg::Node> mp=osgDB::readNodeFile("E:/HRB/china-simple2.earth");
	mRoot->addChild(mp);
	mapNode=dynamic_cast<osgEarth::MapNode*>(mp.get());
	//获取图层
	mapNode->getMap()->getImageLayers(imageLayerVec);
	for (osgEarth::ImageLayerVector::iterator it=imageLayerVec.begin();it!=imageLayerVec.end();it++)
	{
		layernames.push_back(it->get()->getName());
	}
	mapNode->getMap()->getModelLayers(modelLayerVec);
	for (ModelLayerVector::iterator it=modelLayerVec.begin();it!=modelLayerVec.end();it++)
	{
		layernames.push_back(it->get()->getName());
	}
}
void COSGObject::InitCameraConfig()//初始化相机
{
	CRect rect;
	//RECT rect;	
	mViewer = new osgViewer::Viewer;
	::GetWindowRect(n_hWnd,&rect);
	osg::ref_ptr<osg::GraphicsContext::Traits> traits=new osg::GraphicsContext::Traits;
	osg::ref_ptr<osg::Referenced> vindata=new osgViewer::GraphicsWindowWin32::WindowData(n_hWnd);
	rect.OffsetRect(1000,1000);
	traits->x=0;
	traits->y=0;
	traits->width=rect.right-rect.left;
	traits->height=rect.bottom-rect.top;
	traits->windowDecoration=false;
	traits->doubleBuffer=true;
	traits->sharedContext=0;
	traits->setInheritedWindowPixelFormat=true;
	traits->inheritedWindowData=vindata;
	osg::GraphicsContext *gc=osg::GraphicsContext::createGraphicsContext(traits);


	osg::ref_ptr<osg::Camera> camera=new osg::Camera;
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(traits->x,traits->y,traits->width,traits->height));
	camera->setProjectionMatrixAsPerspective(30.0f,static_cast<double> (traits->width)/static_cast<double>(traits->height),1.0,1000.0);

	//dc begin	管线统计---------------------------------------
	pStatisticDlg->Create(IDD_TONGJI);
	pRectNodeGroup = new osg::Group;
	mRoot->addChild(pRectNodeGroup);
	mViewer->addEventHandler(new PipeStatisticHandler(mViewer,mapNode.get(),&pStatisticDlg,&pRectNodeGroup));
	//dc end	管线统计---------------------------------------

	mViewer->setCamera(camera);
	//mViewer->setCameraManipulator(new osgGA::TrackballManipulator);
	mViewer->setSceneData(mRoot);
	mViewer->realize();
	mViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_USING_PRIMITIVES);
	mViewer->getCamera()->setNearFarRatio(0.000003f);

}
void COSGObject::PreFrameUpdate()
{
	while(theApp.NeedModify) Sleep(1);
	theApp.CanModify=FALSE;
}
void COSGObject::PostFrameUpdate()
{
	if (theApp.NeedModify)theApp.CanModify=true;
}
void COSGObject::Render(void * ptr)//规避线程互斥方法,渲染线程
{

	COSGObject *osg =(COSGObject *)ptr;
	osgViewer::Viewer *viewer = osg->getViewer();
	while(!viewer->done())
	{

		osg->PreFrameUpdate();
		viewer->frame();
		osg->PostFrameUpdate();
	}
	_endthread();
}

osgViewer::Viewer *COSGObject::getViewer()
{
	return mViewer;
}

void COSGObject::InitOsgEarth()
{
	//初始化操作器
	em=new osgEarth::Util::EarthManipulator;

	if(mapNode.valid())
	{
		em->setNode(mapNode);
	}
	em->getSettings()->setArcViewpointTransitions(true);
	mViewer->setCameraManipulator(em);

	//初始化天空
	osgEarth::Config skyConf;
	osgEarth::Util::SkyOptions options(skyConf);
	double hours=skyConf.value("hours",12.0);
	osgEarth::Util::SkyNode *skyNode = osgEarth::Util::SkyNode::create(options, mapNode);
	skyNode->setDateTime(osgEarth::DateTime(2015,02,13,hours));
	skyNode->attach(mViewer,3);
	mRoot->addChild(skyNode);
	//获取图层

	china_boundaries=mapNode->getMap()->getImageLayerByName("world_boundaries");

}
void COSGObject::setChinaBoundariesOpacity(double opt)
{
	if(china_boundaries)
	{
		china_boundaries->setOpacity(opt);
	}
}
double COSGObject::getChinaBoundariesOpacity()
{
	if(china_boundaries)
	{
		return china_boundaries->getOpacity();
	}
	else
	{
		return -1;
	}
}
void COSGObject::rmvChinaBounds()
{

	if(china_boundaries)
	{
		mapNode->getMap()->removeImageLayer(china_boundaries);

	}
}
void COSGObject::addChinaBounds()
{
	if(china_boundaries)
	{
		mapNode->getMap()->addImageLayer(china_boundaries);
	}
}


void COSGObject::initStatisticDlg()
{
	pStatisticDlg->ShowWindow(SW_NORMAL);
}
void COSGObject::pipeView(void)
{

	for (ImageLayerVector::iterator it=imageLayerVec.begin();it!=imageLayerVec.end();it++)
	{
		//mapNode->getMap()->removeImageLayer(it->get());
		it->get()->setVisible(false);
	}

	for (ModelLayerVector::iterator it=modelLayerVec.begin();it!=modelLayerVec.end();it++)
	{
		//mapNode->getMap()->removeModelLayer(it->get());
		if (pipes->find(it->get()->getName())==pipes->end())
		{
			it->get()->setVisible(false);
		}
		else
		{
			it->get()->setVisible(true);
		}
	}
}



void COSGObject::buildingView(void)
{
	for (ImageLayerVector::iterator it=imageLayerVec.begin();it!=imageLayerVec.end();it++)
	{
		//mapNode->getMap()->addImageLayer(it->get());
		it->get()->setVisible(true);
	}

	for (ModelLayerVector::iterator it=modelLayerVec.begin();it!=modelLayerVec.end();it++)
	{
		//mapNode->getMap()->addModelLayer(it->get());
		//it->get()->setVisible(true);
		if (pipes->find(it->get()->getName())==pipes->end())
		{
			it->get()->setVisible(true);
		}
		else
		{
			it->get()->setVisible(false);
		}
	}
}
