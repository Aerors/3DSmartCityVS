#include "StdAfx.h"
#include "HeadFiles.h"
#include <string>
using namespace std;

class PipePoint
{
public:
	PipePoint(char * point ,char * elevation);
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

