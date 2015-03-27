#pragma once
#include <sstream>
#include "string"
using namespace std;
class makeSql
{
public:
	makeSql(void);
	~makeSql(void);
	char* getPolySql(string sql);
public:
	string makePolySql(const double topleftlat,const double topleftlon,const double bottomrightlat,const double bottomrightlon);
	string makeLineSql(const double topleftlat,const double topleftlon,const double bottomrightlat,const double bottomrightlon);
};

