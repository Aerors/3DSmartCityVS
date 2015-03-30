#include "stdafx.h"
#include "AddFlagDlg.h"
#include "HeadFiles.h"

#pragma once

class CAddClick :
	public osgGA::GUIEventHandler
{
public:
	CAddClick(MapNode* mapNode,osgViewer::Viewer* viewer, CAddFlagDlg * * addlg,bool * isWindowClose);
	~CAddClick(void);
	virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );


public:
	CAddFlagDlg * * addlg;
	MapNode * mapNode;
	osgViewer::Viewer * mViewer;
	GeoPoint ConvertPoint;
	bool * isWindowClose;
};

