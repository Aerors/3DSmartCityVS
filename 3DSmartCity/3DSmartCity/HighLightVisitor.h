#pragma once
#include <osg/NodeVisitor>
#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
class HighLightVisitor :
	public osg::NodeVisitor
{
public:
	HighLightVisitor(void);
	~HighLightVisitor(void);

	virtual void apply(osg::Node& node);//虚函数，访问各种节点类型，并执行访问器中的自定义操作
	virtual void apply(osg::Group& node);
	virtual void apply(osg::Geode& node);
};

