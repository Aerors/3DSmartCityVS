#pragma once
#include <osg/NodeVisitor>
#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
class HighLightVisitor :
	public osg::NodeVisitor
{
public:
	HighLightVisitor(std::string str);
	~HighLightVisitor(void);

	virtual void apply(osg::Geode& node);

private:
	std::string m_bzm;//±êÊ¶Âë

};

