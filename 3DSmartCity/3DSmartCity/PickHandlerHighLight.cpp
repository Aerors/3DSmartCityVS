#include "StdAfx.h"
#include "PickHandlerHighLight.h"


PickHandlerHighLight::PickHandlerHighLight(MapNode* mapNode,EarthManipulator * manip,osgViewer::Viewer* viewer,osg::Group *root,Analyze *bg)
{
	this->mapNode = mapNode;
	this->manip = manip;
	this->mViewer = viewer;
	this->root = root;
	lastSelect = 0;
	this->analyze = bg;
}


PickHandlerHighLight::~PickHandlerHighLight(void)
{
}


bool PickHandlerHighLight::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
	case (osgGA::GUIEventAdapter::DOUBLECLICK):
		{
			if (lastSelect)
			{
				osg::StateSet *state = lastSelect->getOrCreateStateSet();
				state->setMode(GL_BLEND,osg::StateAttribute::ON);
				osg::Material* mtrl = dynamic_cast<osg::Material*>(state->getAttribute(osg::StateAttribute::MATERIAL));
				mtrl->setAmbient(osg::Material::FRONT_AND_BACK,osg::Vec4f(1.0,1.0,1.0,1.0));
				mtrl->setDiffuse(osg::Material::FRONT_AND_BACK,osg::Vec4f(1.0,1.0,1.0,1.0));
				mtrl->setTransparency(osg::Material::FRONT_AND_BACK,0.0);
				state->setAttributeAndModes(mtrl,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
				state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
				lastSelect=0;
			}
			Pick(ea.getX(),ea.getY());
		}
		return true;
	}
	switch(ea.getKey())
	{
	case (osgGA::GUIEventAdapter::KEY_0):
		{
			manip->setViewpoint(osgEarth::Viewpoint(-123.7,35.5, 50, 45.261, 29.6, 285000.0), 6.0 );
			//std::cout<<"viewpoint1"<<std::endl;
		}
		break;
	case (osgGA::GUIEventAdapter::KEY_1):
		{
			manip->setViewpoint(osgEarth::Viewpoint(123.7,15.5, 50, 35.261, -29.6, 185000.0), 6.0 );
			//std::cout<<"viewpoint1"<<std::endl;
		}
		break;
	case (osgGA::GUIEventAdapter::KEY_2):
		{
			manip->setViewpoint(osgEarth::Viewpoint(126.65,45.74, 50, 35.261, -29.6, 2500.0), 5.0 );
			//std::cout<<"viewpoint2"<<std::endl;
		}
		break;
		return true;
	}
	return false;
}

void PickHandlerHighLight::Pick(float x,float y )
{
	osgUtil::LineSegmentIntersector::Intersections intersection;
	//x , y 坐标值，intersection存放与法线相交的节点以及相交的节点路径等相关信息的列表
	if (mViewer->computeIntersections(x,y,intersection))//使用computeIntersections计算当前场景中单击到了那些模型，结果存放在结果集内
	{
		
		//使用迭代器取出这些模型，取出的结果是一个NodePath类对象，遍历该NodePath对象可以找到是否单击到了目标节点
		for (osgUtil::LineSegmentIntersector::Intersections::iterator hiter=intersection.begin();hiter!=intersection.end();++hiter)
		{
			if (!hiter->nodePath.empty())
			{
				const osg::NodePath& np = hiter->nodePath;
				for (int i = np.size()-1;i>=0;--i)
				{
					osg::Node* nd = dynamic_cast<osg::Node*>(np[i]);
					if (nd)
					{
						CString name = nd->getName().c_str();//ysgline_new 1234
						int index = name.Find("ysgline_new");
						if (index == 0)
						{
							CString objectID = name.Right(name.GetLength()-12);//1234
							//添加marker
							//this->analyze->addMarkers(this->mapNode,this->root,"ysgline_new","ysgpoint_new",objectID);
							this->analyze->objectIDOfPiecked = objectID;

							HighLightVisitor hlv(nd->getName());
							nd->accept(hlv);
							/*osg::StateSet* state = nd->getOrCreateStateSet();
							state->setMode(GL_BLEND,osg::StateAttribute::ON);
							state->setMode(GL_LIGHTING,osg::StateAttribute::ON);
							osg::Material* mtrl  = dynamic_cast<osg::Material*>(state->getAttribute(osg::StateAttribute::MATERIAL));
							if (!mtrl)
							{
								mtrl = new osg::Material;
							}
							mtrl->setDiffuse(osg::Material::FRONT_AND_BACK,osg::Vec4(1.0,1.0,0.0,0.8));
							mtrl->setAmbient(osg::Material::FRONT_AND_BACK,osg::Vec4(1.0,1.0,0.0,0.8));
							mtrl->setTransparency(osg::Material::FRONT_AND_BACK,0.2);
							state->setAttributeAndModes(mtrl,osg::StateAttribute::OVERRIDE||osg::StateAttribute::ON);
							state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);*/
							lastSelect = nd;
							return;
						}
					}
				}
			}
		}
	}
}