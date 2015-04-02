#pragma once

#include "HeadFiles.h"
#include <iostream>
#include <set>
#include "PipePoint.h"
#include "DBConnection.h"


//using namespace std;
using namespace osgEarth;
using namespace osgEarth::Symbology;
using namespace osgEarth::Annotation;

class Analyze
{
public:
	Analyze(void);
	~Analyze(void);

	PGconn *conn;
	PGresult *res;
	DBConnection *DBclass;
	std::string gid;  //pipe line 's gid  
	vector<CString> Geoms; //从数据库中获取的附属物位阀门的所有point     (CString 类型，需要转换);
	ModelLayer* bgMarkerLayer;
	osg::ref_ptr<osg::Group> myRoot;
	std::set<std::string> objectIDsVector;
	CString objectIDOfPiecked;
public:
	vector<CString> getIDs(CString tableName,CString objectID,int type);
	vector<CString> getAllIDs(CString tableNameOfLine,CString objectID);
	void  addMarker(MapNode * mapNode,osg::Group * root,CString tableNameOfPoint,CString objectID);//根据选中管线 查询连通管线的所有管点,在对应的point表中,查询管点的属性信息，列出具有 阀门 属性值的管点;
	void addMarkers(MapNode * mapNode,osg::Group * root,CString tableNameOfLine,CString tableNameOfPoint,CString objectID);
	char *callBackValue(char *(*callfunct)(const PGresult * res,int tup_num,int field_num),const PGresult * res,int tup_num,int field_num);
	boolean clearMarkers(MapNode * mapNode);
};

