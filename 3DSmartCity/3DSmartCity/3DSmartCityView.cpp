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

// 3DSmartCityView.cpp : CMy3DSmartCityView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "3DSmartCity.h"
#endif


#include "3DSmartCityView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DSmartCityView

IMPLEMENT_DYNCREATE(CMy3DSmartCityView, CView)

BEGIN_MESSAGE_MAP(CMy3DSmartCityView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy3DSmartCityView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_COMMAND(ID_GUANXIANTONGJION, &CMy3DSmartCityView::OnGuanxiantongjion)
	ON_COMMAND(ID_CHANGJINGON, &CMy3DSmartCityView::OnPipeOn)
	ON_COMMAND(32791, &CMy3DSmartCityView::OnBuildingOn)
	ON_COMMAND(ID_BIAOHUION, &CMy3DSmartCityView::OnBiaohuion)
	ON_COMMAND(ID_HENGDUANFENXION, &CMy3DSmartCityView::OnHengduanfenxion)
END_MESSAGE_MAP()

// CMy3DSmartCityView 构造/析构

CMy3DSmartCityView::CMy3DSmartCityView()
{
	//初始化
	mOSG=0;
	mThreadHandle=0;
	isPipe=false;
	isFirst=true;

}

CMy3DSmartCityView::~CMy3DSmartCityView()
{
}

BOOL CMy3DSmartCityView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy3DSmartCityView 绘制

void CMy3DSmartCityView::OnDraw(CDC* /*pDC*/)
{
	CMy3DSmartCityDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	
}


// CMy3DSmartCityView 打印


void CMy3DSmartCityView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy3DSmartCityView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy3DSmartCityView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy3DSmartCityView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy3DSmartCityView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy3DSmartCityView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy3DSmartCityView 诊断

#ifdef _DEBUG
void CMy3DSmartCityView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DSmartCityView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DSmartCityDoc* CMy3DSmartCityView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DSmartCityDoc)));
	return (CMy3DSmartCityDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DSmartCityView 消息处理程序

int CMy3DSmartCityView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	mOSG = new COSGObject(m_hWnd);
	return 0;
}



BOOL CMy3DSmartCityView::OnEraseBkgnd(CDC* pDC)
{
	if(0==mOSG)
	{
		return CView::OnEraseBkgnd(pDC);
	}
	else
	{
		return FALSE;
	}


	return CView::OnEraseBkgnd(pDC);
}



void CMy3DSmartCityView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	mOSG->InitOSG();
	mThreadHandle=(HANDLE)_beginthread(&COSGObject::Render,0,mOSG);
	// TODO: 在此添加专用代码和/或调用基类

	CMainFrame*  pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	SmartCityTreeView* leftView = (SmartCityTreeView*)pFrame->GetActiveFrame();
	SmartCityTreeView* leftView001=(SmartCityTreeView*)pFrame->m_wndSplitter.GetPane(0,0);
	CMy3DSmartCityView* pRightView = (CMy3DSmartCityView*)pFrame->m_wndSplitter.GetPane(0,1);

	tree.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES
		| TVS_DISABLEDRAGDROP | TVS_NOTOOLTIPS | TVS_EDITLABELS,
		CRect(0, 30, 250, 1000), leftView001, 1200);
	tree.ShowWindow(SW_SHOW);
	tree.ModifyStyle( TVS_CHECKBOXES, 0 );
	tree.ModifyStyle( 0, TVS_CHECKBOXES );
	HTREEITEM hRoot;	
	CString str="图层名称";
	hRoot=tree.InsertItem(str);
	tree.SetCheck(hRoot);
	HTREEITEM hChild ;
	for(vector<string>::iterator it=pRightView->mOSG->layernames.begin();it!=pRightView->mOSG->layernames.end();it++)
	{
		layerName = it->c_str();
		hChild=tree.InsertItem(layerName,hRoot);
		tree.SetCheck(hChild);
	}
}

void CMy3DSmartCityView::OnDestroy()
{
	CView::OnDestroy();
	if(mOSG!=0) delete mOSG;
	WaitForSingleObject(mThreadHandle,1000);

	// TODO: 在此处添加消息处理程序代码
}


void CMy3DSmartCityView::OnGuanxiantongjion()
{
	// TODO: 在此添加命令处理程序代码
	mOSG->initStatisticDlg();
}


void CMy3DSmartCityView::OnPipeOn()
{
	// TODO: 在此添加命令处理程序代码
	theApp.NeedModify=TRUE;
	while(!theApp.CanModify)Sleep(1);
	if (isFirst||!isPipe)
	{
		mOSG->pipeView();
		isPipe=true;
		isFirst=false;
	}
	theApp.NeedModify=FALSE;
}


void CMy3DSmartCityView::OnBuildingOn()
{
	// TODO: 在此添加命令处理程序代码
	theApp.NeedModify=TRUE;
	while(!theApp.CanModify)Sleep(1);
	if (isFirst||isPipe)
	{
		mOSG->buildingView();
		isPipe=false;
		isFirst=false;
	}
	theApp.NeedModify=FALSE;
}


void CMy3DSmartCityView::OnBiaohuion()
{
	mOSG->addFlag();
}


void CMy3DSmartCityView::OnHengduanfenxion()
{

	if(IDYES==MessageBoxA(_T("是否画线选取管线?"),_T("管线选取"),MB_ICONQUESTION+MB_YESNO))  
	{  
		mOSG->isDrawLineStart=true;
	}  
	else
	{
		mOSG->isDrawLineStart=false;
	}

}
