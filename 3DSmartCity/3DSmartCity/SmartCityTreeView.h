#pragma once
#include "MainFrm.h"
#include "OSGObject.h"

using namespace std;
using namespace osgEarth;


// SmartCityTreeView 视图

class SmartCityTreeView : public CView
{
	DECLARE_DYNCREATE(SmartCityTreeView)

protected:
	SmartCityTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~SmartCityTreeView();
	CMainFrame* mainFrame;
public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	CButton m_button;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


