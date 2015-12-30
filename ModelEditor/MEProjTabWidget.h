///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjListWidget.h
// Creator  : Miao Kaixiang
// Date     : 2015-12-21 09:00:00
// Comment  : Declaration of TabWidget of MEProj
//
///////////////////////////////////////////////////////////////

#ifndef MEPROJTABWIDGET_H
#define MEPROJTABWIDGET_H

#include <QTabWidget>
#include <D3DX11.h>
#include <D3D11.h>
#include "KEPublic2.h"
#include "MEProjServer.h"
#include "MEProjTreeWidgetItem.h"

class MEProjServer;
class MEProjTabWidget : public QTabWidget
{
	Q_OBJECT
	
private:
	MEProjServer*	m_pMEProjServer;
	QWidget*        m_pParent;	

private slots:
	void RemoveTab(int index);

public:
	MEProjTabWidget(QWidget* pParent = NULL);
	void AddXmlTabWidget(MEProjTreeWidgetItem* pMEProjTreeWidgetItem, int index);
	HRESULT Init(MEProjServer* pMEProjServer, QWidget* pInitialWidget, QString& qStrTabName);
	HRESULT UnInit();

public slots:
	void SaveCurrentFile();
};

#endif // MEPROJTABWIDGET_H