#pragma once
#include <string>
using namespace std;

class PipePoint
{
public:
	PipePoint();
	PipePoint(char * point ,char * elevation);
	PipePoint(double lan, double lon, double ele);
	~PipePoint(void);
private:
	double _lat;
	double _lon;
	double _ele;
public:
	double getLat(){return _lat;}
	double getLon(){return _lon;}
	double getEle(){return _ele;}

};

