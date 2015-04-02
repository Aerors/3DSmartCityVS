#include "StdAfx.h"
#include "PipePoint.h"

PipePoint::PipePoint()
{
}

PipePoint::PipePoint(char * point ,char * elevation)
{
	_ele=atof(elevation)-0;

	string pointStr=string(point);
	int m,n,l;
	string str1,str2;
	n = pointStr.find('(');
	m = pointStr.find(')');
	l = pointStr.find(' ');
	str1 = pointStr.substr(n+1,l-n-1);
	str2 = pointStr.substr(l+1,m-l-1);
	_lon=atof(str1.c_str());
	_lat=atof(str2.c_str());	
}

PipePoint::PipePoint(double lat, double lon, double ele)
{
	_lat = lat;
	_lon = lon;
	_ele = ele;
}


PipePoint::~PipePoint(void)
{
}
