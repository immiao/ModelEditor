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
}

HRESULT MEProjServer::Init(MEProjTreeWidget* pMEProjTreeWidget, MEProjTabWidget* pMEProjTabWidget, MEProjRoleListWidget* pMEProjRoleListWidget)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;
	
	m_pMEProjTreeWidget = pMEProjTreeWidget;
	m_pMEProjTabWidget = pMEProjTabWidget;
	m_pMEProjRoleListWidget = pMEProjRoleListWidget;

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

HRESULT MEProjServer::SetXmlNameList(QStringList& qStrXmlNames)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;
	
	m_qStrXmlNames = qStrXmlNames;
	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT	MEProjServer::SetXmlInfoList(QFileInfoList& qStrListXmlInfo)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;
	
	m_qStrXmlInfo = qStrListXmlInfo;
	hrResult = S_OK;
Exit0:
	return hrResult;
}

QStringList MEProjServer::GetXmlNameList()
{
	return m_qStrXmlNames;
}

QFileInfoList MEProjServer::GetXmlInfoList()
{
	return m_qStrXmlInfo;
}

void MEProjServer::ConfigNotifyRoleList(QString& qStrRoleName, QString& qStrXmlFileName, QString& qStrAbsolutePath, XMFLOAT3& xmf3Pos)
{
	m_pMEProjRoleListWidget->AddWidgetItem(qStrRoleName, qStrXmlFileName, qStrAbsolutePath, xmf3Pos);
}
