#pragma once
#include <osg/NodeVisitor>
class HighLightVisitor :
	public osg::NodeVisitor
{
public:
	HighLightVisitor(void);
	~HighLightVisitor(void);

	void apply(Node& node);������//�麯�������ʸ��ֽڵ����ͣ���ִ�з������е��Զ������
����void apply(Group& node);
����void apply(Geode& node);
};

