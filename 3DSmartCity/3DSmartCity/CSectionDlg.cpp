// CSectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSmartCity.h"
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
}


BEGIN_MESSAGE_MAP(CCSectionDlg, CDialogEx)
END_MESSAGE_MAP()


// CCSectionDlg 消息处理程序
