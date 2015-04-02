#pragma once
#include "MainFrm.h"
#include "3DSmartCityDoc.h"
#include "3DSmartCity.h"
#include "OSGObject.h"
#include <Windows.h>
#include "HighLightVisitor.h"
using namespace std;


// SmartCityTreeCtrl

class SmartCityTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(SmartCityTreeCtrl)

public:
	SmartCityTreeCtrl(HWND hWnd);
	SmartCityTreeCtrl();

	virtual ~SmartCityTreeCtrl();
private:
	HWND n_hWnd;//创建一个句柄
protected:
	DECLARE_MESSAGE_MAP()
	CMainFrame* mainFrame;
public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


