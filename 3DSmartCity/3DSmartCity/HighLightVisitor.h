#pragma once
#include <osg/NodeVisitor>
class HighLightVisitor :
	public osg::NodeVisitor
{
public:
	HighLightVisitor(void);
	~HighLightVisitor(void);

	void apply(Node& node);　　　//虚函数，访问各种节点类型，并执行访问器中的自定义操作
　　void apply(Group& node);
　　void apply(Geode& node);
};

