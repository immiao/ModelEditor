///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjRoleListWidget.h
// Creator  : Miao Kaixiang
// Date     : 2015-12-31 11:00:00
// Comment  : Declaration of Role TreeWidget in MEProj
//
///////////////////////////////////////////////////////////////

#ifndef MEPROJROLELISTWIDGET_H
#define MEPROJROLELISTWIDGET_H

#include "KEPublic2.h"
// 这两个定义了E_FAIL和S_OK
#include <d3d11.h>
#include <d3dx11.h>
#include <QListWidget>
#include <QLayout>
#include <xnamath.h>
#include "MEProjRoleListWidgetItem.h"
#include "MEProjServer.h"
#include <QWidget>
#include <QMouseEvent>

class MEProjRoleListWidget: public QListWidget
{
	Q_OBJECT

	MEProjServer*	m_pMEProjServer;
	void mousePressEvent(QMouseEvent* pEvent);
public:
	MEProjRoleListWidget(QWidget* pParent = NULL);
	~MEProjRoleListWidget();
	HRESULT Init(MEProjServer* pMEProjServer);
	HRESULT UnInit();
	void AddWidgetItem(QString& qStrRoleName, QString& qStrRoleFileAbsolutePath, QString& qStrXmlFileName, 
		QString& qStrXmlFileAbsolutePath, XMFLOAT3& xmf3Pos);
private slots:
	//void NotifyServerItemUpdateColor(int index);
	void DeleteItem();
};

#endif // MEPROJROLELISTWIDGET_H