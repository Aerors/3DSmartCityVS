// CSectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CSectionDlg.h"
#include "afxdialogex.h"


// CCSectionDlg 对话框

IMPLEMENT_DYNAMIC(CCSectionDlg, CDialogEx)

CCSectionDlg::CCSectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCSectionDlg::IDD, pParent)
{

}

CCSectionDlg::~CCSectionDlg()
{
}

void CCSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, listPro);
	DDX_Control(pDX, IDC_CHARTCTRL, mChartCtrl);
}


void CCSectionDlg::clearData()
{

}

BEGIN_MESSAGE_MAP(CCSectionDlg, CDialogEx)
END_MESSAGE_MAP()


// CCSectionDlg 消息处理程序


BOOL CCSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	listPro.DeleteAllItems();//清空  
	listPro.InsertColumn(0,"标识码",LVCFMT_LEFT,95);//添加列  
	listPro.InsertColumn(1,"管径",LVCFMT_LEFT,95);  
	listPro.InsertColumn(2,"材质",LVCFMT_LEFT,95);  
	listPro.InsertColumn(3,"起点埋深",LVCFMT_LEFT,95);  
	listPro.InsertColumn(4,"终点埋深",LVCFMT_LEFT,95);  
	listPro.InsertColumn(5,"起点高程",LVCFMT_LEFT,95);  
	listPro.InsertColumn(6,"终点高程",LVCFMT_LEFT,95);  
	listPro.InsertColumn(7,"建设年代",LVCFMT_LEFT,95);  
	listPro.InsertColumn(8,"探测日期",LVCFMT_LEFT,95);  

	CChartAxis *pAxis= NULL; 
	pAxis = mChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = mChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	mChartCtrl.GetTitle()->AddString("横断面分析");
	pAxis->GetLabel()->SetText("地面高程(m)");

	return TRUE; 
}

