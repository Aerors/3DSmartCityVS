// StatisticDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StatisticDialog.h"
#include "afxdialogex.h"


// StatisticDialog �Ի���

IMPLEMENT_DYNAMIC(StatisticDialog, CDialogEx)

StatisticDialog::StatisticDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(StatisticDialog::IDD, pParent)

{

	//  m_leftlat = 0.0f;
	m_leftlon = 0.0;
	m_rightlat = 0.0;
	m_rightlon = 0.0;
	m_leftlat = 0.0;
}

StatisticDialog::~StatisticDialog()
{
}

void StatisticDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATISTICLIST, m_statisticResult);
	//  DDX_Text(pDX, IDC_LEFTLAT, m_leftlat);
	//  DDV_MinMaxFloat(pDX, m_leftlat, -90, 90);
	DDX_Text(pDX, IDC_LEFTLON, m_leftlon);
	DDV_MinMaxDouble(pDX, m_leftlon, -180, 180);
	DDX_Text(pDX, IDC_RIGHTLAT, m_rightlat);
	DDV_MinMaxDouble(pDX, m_rightlat, -90, 90);
	DDX_Text(pDX, IDC_RIGHTLON, m_rightlon);
	DDV_MinMaxDouble(pDX, m_rightlon, -180, 180);
	DDX_Text(pDX, IDC_LEFTLAT, m_leftlat);
	DDV_MinMaxDouble(pDX, m_leftlat, -90, 90);
}


BEGIN_MESSAGE_MAP(StatisticDialog, CDialogEx)
//	ON_REGISTERED_MESSAGE(WM_UPDATEDATA, &StatisticDialog::OnUpdatedata)
	ON_MESSAGE(WM_UPDATEDATA, &StatisticDialog::OnUpdatedata)
END_MESSAGE_MAP()


// StatisticDialog ��Ϣ�������


//afx_msg LRESULT StatisticDialog::OnUpdatedata(WPARAM wParam, LPARAM lParam)
//{
//	UpdateData(wParam);
//	return 0;
//}


afx_msg LRESULT StatisticDialog::OnUpdatedata(WPARAM wParam, LPARAM lParam)
{
	UpdateData(wParam);
	return 0;
}
