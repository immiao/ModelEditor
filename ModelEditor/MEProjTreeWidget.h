///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjTreeWidget.h
// Creator  : Miao Kaixiang
// Date     : 2015-12-21 09:00:00
// Comment  : Declaration of TreeWidget of MEProj
//
///////////////////////////////////////////////////////////////

#ifndef MEPROJTREEWIDGET_H
#define MEPROJTREEWIDGET_H

#include <QTreeWidget>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <d3dx11.h>
#include <d3d11.h>
#include "KEPublic2.h"
#include "MEProjServer.h"
#include "MEProjTreeWidgetItem.h"

class MEProjServer;
class MEProjTreeWidget : public QTreeWidget
{
	Q_OBJECT

private:
	QTreeWidgetItem* m_pQRootTreeWidgetItem;
	QTreeWidgetItem* m_pQTreeWidgetItem;
	MEProjServer*	 m_pMEProjServer;
private slots:
	void NotifyServer(QTreeWidgetItem* pMEProjTreeWidgetItem, int index);
public:
	MEProjTreeWidget(QWidget* pParent = NULL);
	HRESULT Init(MEProjServer* pMEProjServer, const QString& qStrFileName);
	HRESULT UnInit();
};

#endif // MEPROJTREEWIDGET_H