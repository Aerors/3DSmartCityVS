#pragma once


// CCSectionDlg �Ի���

class CCSectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCSectionDlg)

public:
	CCSectionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCSectionDlg();
	void InitDlg();

// �Ի�������
	enum { IDD = IDD_CSECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
