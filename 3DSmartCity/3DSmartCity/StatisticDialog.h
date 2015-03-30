#pragma once
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"

#define WM_UPDATEDATA WM_USER+116
// StatisticDialog 对话框

class StatisticDialog : public CDialogEx
{
	DECLARE_DYNAMIC(StatisticDialog)

public:
	StatisticDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~StatisticDialog();

// 对话框数据
	enum { IDD = IDD_TONGJI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	float m_leftLat;
//	float m_leftLon;
//	float m_rightLat;
//	float m_rightLon;
	CListBox m_statisticResult;
//	float m_leftlat;
	double m_leftlon;
	double m_rightlat;
	double m_rightlon;
	double m_leftlat;
protected:
//	afx_msg LRESULT OnUpdatedata(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdatedata(WPARAM wParam, LPARAM lParam);
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
};
