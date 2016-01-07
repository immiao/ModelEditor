///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjServer.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-12-22 14:00:00
// Comment  : Implementation of the Server(Subject) of Widgets in MEProj
//
///////////////////////////////////////////////////////////////

#include "MEProjServer.h"
#include <QDebug>

MEProjServer::MEProjServer()
{
	m_pMEProjTreeWidget = NULL;
	m_pMEProjTabWidget = NULL;
	m_pMEProjRoleListWidget = NULL;
	m_pMEProjD3DWidget = NULL;
}

HRESULT MEProjServer::Init(MEProjTreeWidget* pMEProjTreeWidget, MEProjTabWidget* pMEProjTabWidget, 
						   MEProjRoleListWidget* pMEProjRoleListWidget, MEProjD3DWidget* pMEProjD3DWidget)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;
	
	m_pMEProjTreeWidget = pMEProjTreeWidget;
	m_pMEProjTabWidget = pMEProjTabWidget;
	m_pMEProjRoleListWidget = pMEProjRoleListWidget;
	m_pMEProjD3DWidget = pMEProjD3DWidget;

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT MEProjServer::UnInit()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;
	
	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT MEProjServer::TreeNotifyTab(MEProjTreeWidgetItem* pMEProjTreeWidgetItem, int index)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;
	
	m_pMEProjTabWidget->AddXmlTabWidget(pMEProjTreeWidgetItem, index);
	hrResult = S_OK;
Exit0:
	return hrResult;
}

void MEProjServer::ConfigNotifyRoleList(QString& qStrRoleFileName, QString& qStrRoleFileAbsolutePath, QString& qStrXmlFileName, 
	QString& qStrXmlFileAbsolutePath, XMFLOAT3& xmf3Pos)
{
	m_pMEProjRoleListWidget->AddWidgetItem(qStrRoleFileName, qStrRoleFileAbsolutePath, qStrXmlFileName, qStrXmlFileAbsolutePath, xmf3Pos);
}

QList<MEProjRoleListWidgetItem*> MEProjServer::GetItemList()
{
	int nRow = m_pMEProjRoleListWidget->count();
	QList<MEProjRoleListWidgetItem*> qItemList;
	for (int i = 0; i < nRow; i++)
	{
		qItemList.append(dynamic_cast<MEProjRoleListWidgetItem*>(m_pMEProjRoleListWidget->item(i)));
	}
	return qItemList;
}

void MEProjServer::NotifyD3DWidgetUpdateRole()
{
	m_pMEProjD3DWidget->UpdateRole();
}

void MEProjServer::NotifyD3DWidgetUpdateColor(int index)
{
	m_pMEProjD3DWidget->SetSelectedItemColor(index);
}
