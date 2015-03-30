#include "stdafx.h"
#include "resource.h"
#include "HeadFiles.h"

#define  WM_UPDATEDATA_ADDMARKER WM_USER+111

using namespace osg;
using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Util;

#pragma once


// CAddFlagDlg 对话框

class CAddFlagDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddFlagDlg)

public:
	CAddFlagDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddFlagDlg();

	void initDlg(osg::ref_ptr<osg::Group> mLabels,	osg::ref_ptr<osgEarth::MapNode> mapNode);

// 对话框数据
	enum { IDD = IDD_ADD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	double m_Lat;
	double m_Lon;
	CString m_Note;

public:
	osg::ref_ptr<osg::Group> mLabels;
	osg::ref_ptr<osgEarth::MapNode> mapNode;
	GeoPoint geoPoint;
protected:
//	afx_msg LRESULT OnUpdatedata(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdatedata(WPARAM wParam, LPARAM lParam);
};
