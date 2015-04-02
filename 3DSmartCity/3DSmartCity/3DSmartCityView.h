// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// 3DSmartCityView.h : CMy3DSmartCityView 类的接口
//

#pragma once
#include "3DSmartCityDoc.h"
#include "MainFrm.h"
#include "OSGObject.h"
#include "SmartCityTreeCtrl.h"
#include "SmartCityTreeView.h"
#include "3DSmartCity.h"

class CMy3DSmartCityView : public CView
{
protected: // 仅从序列化创建
	CMy3DSmartCityView();
	DECLARE_DYNCREATE(CMy3DSmartCityView)
	CString layerName;
	SmartCityTreeCtrl tree;

// 特性
public:
	CMy3DSmartCityDoc* GetDocument() const;

// 操作地图
public:
	COSGObject* mOSG;
	HANDLE mThreadHandle;
//wangsongwei  场景控制标识符
public:
	bool isPipe;
	bool isFirst;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy3DSmartCityView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnGuanxiantongjion();
	afx_msg void OnPipeOn();
	afx_msg void OnBuildingOn();
	afx_msg void OnBiaohuion();
	afx_msg void OnHengduanfenxion();
	afx_msg void OnBaoguanfenxion();
};

#ifndef _DEBUG  // 3DSmartCityView.cpp 中的调试版本
inline CMy3DSmartCityDoc* CMy3DSmartCityView::GetDocument() const
   { return reinterpret_cast<CMy3DSmartCityDoc*>(m_pDocument); }
#endif

