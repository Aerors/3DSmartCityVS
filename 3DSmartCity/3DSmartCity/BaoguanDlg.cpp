// BaoguanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "BaoguanDlg.h"
#include "afxdialogex.h"


// CBaoguanDlg 对话框

IMPLEMENT_DYNAMIC(CBaoguanDlg, CDialogEx)

CBaoguanDlg::CBaoguanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaoguanDlg::IDD, pParent)
{
	bgAnalyze = new Analyze();
}

CBaoguanDlg::~CBaoguanDlg()
{
	delete bgAnalyze;
	bgAnalyze = NULL;
}

void CBaoguanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BAOGUAN, m_list);
}


BEGIN_MESSAGE_MAP(CBaoguanDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PICK_PIPE, &CBaoguanDlg::OnBnClickedButtonPickPipe)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_PIPE, &CBaoguanDlg::OnBnClickedButtonClearPipe)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CBaoguanDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


void CBaoguanDlg::initDlgToGetOSGParam(MapNode* mapNode,EarthManipulator * manip,osgViewer::Viewer* viewer,osg::Group *root)
{
	this->mapNode = mapNode;
	this->manip = manip;
	this->viewer = viewer;
	this->root = root;
}




// CBaoguanDlg 消息处理程序


void CBaoguanDlg::OnBnClickedButtonPickPipe()
{
	AfxMessageBox(_T("开始拾取管线，请双击管线！"));
	this->viewer->addEventHandler(new PickHandlerHighLight(this->mapNode,this->manip,this->viewer,this->root,bgAnalyze));
}


void CBaoguanDlg::OnBnClickedButtonClearPipe()
{
	bgAnalyze->addMarkers(this->mapNode,this->root,"ysgline_new","ysgpoint_new",bgAnalyze->objectIDOfPiecked);
	int row = 1;
	CString rowStr = "";
	for(std::set<std::string>::iterator it=bgAnalyze->objectIDsVector.begin();it!=bgAnalyze->objectIDsVector.end();it++)
	{
		/*std::string bzm("ysgline_new "+ *(it));
		osg::Node* root= this->viewer->getSceneData();
		HighLightVisitor hlv(bzm);
		root->accept(hlv);*/
		rowStr.Format("%d",row);
		int nRow = m_list.InsertItem(0, rowStr);//插入行
		m_list.SetItemText(nRow, 1, (*it).c_str());//设置数据
		row++;
	}
}


void CBaoguanDlg::OnBnClickedButtonCancel()
{
	bgAnalyze->bgMarkerLayer->setVisible(false);
	bgAnalyze->objectIDOfPiecked = "";
	bgAnalyze->objectIDsVector.erase(bgAnalyze->objectIDsVector.begin(),bgAnalyze->objectIDsVector.end());
	m_list.DeleteAllItems();
}


BOOL CBaoguanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_list.InsertColumn( 0, "ID", LVCFMT_LEFT, 80 );//插入列
	m_list.InsertColumn( 1, "标识码", LVCFMT_CENTER, 360 );
	return TRUE;  // return TRUE unless you set the focus to a control

}
