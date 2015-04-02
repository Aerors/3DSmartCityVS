// SmartCityTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSmartCity.h"
#include "SmartCityTreeCtrl.h"
#include "3DSmartCityView.h"
#include "SmartCityTreeView.h"
#include "MainFrm.h"

// SmartCityTreeCtrl

IMPLEMENT_DYNAMIC(SmartCityTreeCtrl, CTreeCtrl)
SmartCityTreeCtrl::SmartCityTreeCtrl(HWND hWnd)
{
   m_hWnd=hWnd;
}
SmartCityTreeCtrl::SmartCityTreeCtrl()
{

}

SmartCityTreeCtrl::~SmartCityTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(SmartCityTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &SmartCityTreeCtrl::OnNMClick)
END_MESSAGE_MAP()



// SmartCityTreeCtrl 消息处理程序




void SmartCityTreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame*  pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	SmartCityTreeView* leftView = (SmartCityTreeView*)pFrame->GetActiveFrame();
	SmartCityTreeView* leftView001=(SmartCityTreeView*)pFrame->m_wndSplitter.GetPane(0,0);
	CMy3DSmartCityView* pRightView = (CMy3DSmartCityView*)pFrame->m_wndSplitter.GetPane(0,1);
	CPoint pt = GetCurrentMessage()->pt;   //获取当前鼠标点击消息的坐标点
	this->ScreenToClient(&pt);
	UINT uFlags = 0;

	mainFrame = (CMainFrame*)GetActiveWindow();//将鼠标的屏幕坐标，转换成树形控件的客户区坐标

	HTREEITEM hItem = this->HitTest(pt, &uFlags);//然后做点击测试


	if ((hItem != NULL) && (TVHT_ONITEMSTATEICON & uFlags))//如果点击的位置是在节点位置上面
	{
		osgEarth::Map* map = dynamic_cast<osgEarth::Map*>(pRightView->mOSG->mapNode->getMap());


		BOOL checked =this->GetCheck(hItem);
		CString nData001 = this->GetItemText(hItem);
		string layerName001 = (CT2A)nData001.GetBuffer(0);

	/*	theApp.NeedModify = TRUE;
		while(!theApp.CanModify)
		Sleep(1);*/
		osg::ref_ptr<osgEarth::ImageLayer> layer;
		for(osgEarth::ImageLayerVector::iterator it = pRightView->mOSG->imageLayerVec.begin();it!=pRightView->mOSG->imageLayerVec.end();it++)
		{
			string s = (*it)->getName();
			if(0 ==s.compare(layerName001))
			{
				layer = *it;
				if(checked)
				{//此时由选中到未选中
					//map->removeImageLayer(layer);
					//------wangsongwei 更改为不可见
					layer->setVisible(false);
				}else
				{//此时由未选中到选中
					//map->addImageLayer(layer);
					//------wangsongwei
					layer->setVisible(true);
				}
				//theApp.NeedModify = FALSE;
			}
		}

		

		//-----wangsongwei  模型层
		osg::ref_ptr<osgEarth::ModelLayer> mlayer;
		for(osgEarth::ModelLayerVector::iterator it = pRightView->mOSG->modelLayerVec.begin();it!=pRightView->mOSG->modelLayerVec.end();it++)
		{
			string s = (*it)->getName();
			if(0 ==s.compare(layerName001))
			{
				mlayer = *it;
				if(checked)
				{//此时由选中到未选中
					//map->removeImageLayer(layer);
					//------wangsongwei 更改为不可见
					mlayer->setVisible(false);
				}else
				{//此时由未选中到选中
					//map->addImageLayer(layer);
					//------wangsongwei
					mlayer->setVisible(true);
				}
				//theApp.NeedModify = FALSE;
			}
		}
		
	}
	*pResult = 0;
}
