#pragma once


// CCSectionDlg 对话框

class CCSectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCSectionDlg)

public:
	CCSectionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCSectionDlg();
	void InitDlg();

// 对话框数据
	enum { IDD = IDD_CSECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
