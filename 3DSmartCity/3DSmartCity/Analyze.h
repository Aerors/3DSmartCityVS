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
	vector<CString> Geoms; //�����ݿ��л�ȡ�ĸ�����λ���ŵ�����point     (CString ���ͣ���Ҫת��);
	ModelLayer* bgMarkerLayer;
	osg::ref_ptr<osg::Group> myRoot;
	std::set<std::string> objectIDsVector;
	CString objectIDOfPiecked;
public:
	vector<CString> getIDs(CString tableName,CString objectID,int type);
	vector<CString> getAllIDs(CString tableNameOfLine,CString objectID);
	void  addMarker(MapNode * mapNode,osg::Group * root,CString tableNameOfPoint,CString objectID);//����ѡ�й��� ��ѯ��ͨ���ߵ����йܵ�,�ڶ�Ӧ��point����,��ѯ�ܵ��������Ϣ���г����� ���� ����ֵ�Ĺܵ�;
	void addMarkers(MapNode * mapNode,osg::Group * root,CString tableNameOfLine,CString tableNameOfPoint,CString objectID);
	char *callBackValue(char *(*callfunct)(const PGresult * res,int tup_num,int field_num),const PGresult * res,int tup_num,int field_num);
	boolean clearMarkers(MapNode * mapNode);
};

