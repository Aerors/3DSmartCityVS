#pragma once
#include "stdafx.h"
#include "PipePoint.h"
#include "DBConnection.h"
#include <string>
#include "HeadFiles.h"
#define RADIUS (1.0f)

using namespace std;
using namespace osgEarth;

class AddPipe
{
public:
	AddPipe(void);
	~AddPipe(void);
	void InitAddPipe(string lineTableName,string pointTableName,string host="localhost",string port="5432",string database="HRBPipe",string userName="postgres",string pwd="123456");
	//void InitAddPipe(string lineTableName,string pointTableName,string host,string port,string database,string userName,string pwd);
	void Addpipes(MapNode * mapNode);
	osg::Group* Addpipes(MapNode * mapNode,osg::Group * mRoot);
	char *callBackValue(char *(*callfunct)(const PGresult * res,int tup_num,int field_num),const PGresult * res,int tup_num,int field_num);

	
private:
	string lineTableName;
	string pointTableName;
	char * host;
	char * port;
	char * database;
	char * userName;
	char * pwd;
	char * lineID;

private:
	void AddPipe::APipe(MapNode * mapNode,osg::Group * group,osg::ref_ptr<osgModeling::Curve> section,PipePoint *startPoint, PipePoint * endPoint,char * objectID);
	void AddPipe::ASphere(MapNode * mapNode,osg::Group * group,PipePoint *center, double radius);
};

