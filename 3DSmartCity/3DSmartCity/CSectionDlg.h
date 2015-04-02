#pragma once
#include "afxcmn.h"
#include "resource.h"
#include "ChartCtrl/ChartCtrl.h"
#include "ChartCtrl/ChartAxis.h"
#include "ChartCtrl/ChartLabel.h"
#include "ChartCtrl/ChartAxisLabel.h"
#include "ChartCtrl/ChartPointsSerie.h"
#include "ChartCtrl/ChartLineSerie.h"


#include<string>
#include <sstream>
#include "ChartCtrl\ChartCtrl.h"

#if defined _UNICODE ||defined UNICODE
typedef std::wstring TChartString;
typedef std::wstringstream TChartStringStream;
#else
typedef std::string TChartString;
typedef std::stringstream TChartStringStream;
#endif

// CCSectionDlg 对话框

class CCSectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCSectionDlg)

public:
	CCSectionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCSectionDlg();
	void clearData();


// 对话框数据
	enum { IDD = IDD_CSECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl listPro;
	CChartCtrl mChartCtrl;
};
