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

	virtual void apply(osg::Node& node);//�麯�������ʸ��ֽڵ����ͣ���ִ�з������е��Զ������
	virtual void apply(osg::Group& node);
	virtual void apply(osg::Geode& node);
};

