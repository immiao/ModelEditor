///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjServer.h
// Creator  : Miao Kaixiang
// Date     : 2015-12-22 12:00:00
// Comment  : Declaration of the Server(Subject) of Widgets in MEProj
//
///////////////////////////////////////////////////////////////

#ifndef MEPROJSERVER_H
#define MEPROJSERVER_H

#include "KEPublic2.h"
#include "MEProjTreeWidget.h"
#include "MEProjTabWidget.h"
#include "MEProjRoleListWidget.h"
// 这两个定义了E_FAIL和S_OK
#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>

class MEProjTreeWidget;
class MEProjTabWidget;

class MEProjServer
{
	MEProjTreeWidget*		m_pMEProjTreeWidget;
	MEProjTabWidget*		m_pMEProjTabWidget;
	MEProjRoleListWidget*	m_pMEProjRoleListWidget;
public:
	MEProjServer();
	HRESULT Init(MEProjTreeWidget* pMEProjTreeWidget, MEProjTabWidget* pMEProjTabWidget, MEProjRoleListWidget* pMEProjRoleListWidget);
	HRESULT UnInit();
	HRESULT TreeNotifyTab(MEProjTreeWidgetItem* pMEProjTreeWidgetItem, int index);
	void ConfigNotifyRoleList(QString& qStrRoleFileName, QString& qStrRoleFileAbsolutePath, QString& qStrXmlFileName, 
		QString& qStrAbsolutePath, XMFLOAT3& xmf3Pos);
};

#endif // MEPROJSERVER_H