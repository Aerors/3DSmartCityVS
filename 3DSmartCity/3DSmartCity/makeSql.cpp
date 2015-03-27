#include "StdAfx.h"
#include "makeSql.h"


makeSql::makeSql(void)
{
}


makeSql::~makeSql(void)
{
}

//画矩形
string makeSql::makePolySql(double topleftlat,double topleftlon,double bottomrightlat,double bottomrightlon)
{
	char* p = "POLYGON((126.652002305689 45.7528259108467, 126.653364042412 45.7528259108467, 126.653364042412 45.747337756813, 126.652002305689 45.747337756813, 126.652002305689 45.7528259108467))')";
	string begin("select 标识码,gid from (select *,");
	string end(" as queryresult where isContain=true");
	string s;
	ostringstream buf;
	buf.precision(13);  
    buf.setf(std::ios::fixed); // 将浮点数的位数限定为小数点之后的位数 
	buf<<"st_contains(st_geomfromtext('polygon(("<<topleftlon<<' '<<topleftlat<<','<<bottomrightlon<<' '<<topleftlat<<','<<bottomrightlon<<' '<<bottomrightlat<<','<<topleftlon<<' '<<bottomrightlat<<','<<topleftlon<<' '<<topleftlat<<"))'),ysgline_new.geom) as isContain from ysgline_new )";
	s = buf.str();
	string sql;
	sql = begin.append(s);
	sql = sql.append(end);
	//p = const_cast<char*>(s.c_str());
	return sql;
}