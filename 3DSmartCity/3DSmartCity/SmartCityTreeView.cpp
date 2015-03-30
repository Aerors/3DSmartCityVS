// SmartCityTreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "SmartCityTreeView.h"


// SmartCityTreeView

IMPLEMENT_DYNCREATE(SmartCityTreeView, CView)

SmartCityTreeView::SmartCityTreeView()
{

}

SmartCityTreeView::~SmartCityTreeView()
{
}

BEGIN_MESSAGE_MAP(SmartCityTreeView, CView)
	
END_MESSAGE_MAP()


// SmartCityTreeView 绘图

void SmartCityTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// SmartCityTreeView 诊断

#ifdef _DEBUG
void SmartCityTreeView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void SmartCityTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// SmartCityTreeView 消息处理程序


void SmartCityTreeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CRect rect(0,0,250,30);
	m_button.Create(_T("图层控制"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,rect,this,1689);
	m_button.ShowWindow(SW_SHOW);
}