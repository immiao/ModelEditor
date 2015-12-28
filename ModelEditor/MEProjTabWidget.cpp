///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjTabWidget.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-12-21 10:00:00
// Comment  : Implementation of TabWidget of MEProj
//
///////////////////////////////////////////////////////////////

#include "MEProjTabWidget.h"
#include <QLabel>
#include <QDebug>

MEProjTabWidget::MEProjTabWidget(QWidget* pParent):QTabWidget(pParent)
{

}

HRESULT MEProjTabWidget::Init(MEProjServer* pMEProjServer, QWidget* pInitialWidget, QString& qStrTabName)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	m_pMEProjServer = pMEProjServer;

	addTab(pInitialWidget, qStrTabName);
	QLabel *label = new QLabel("Hello Qt");
	addTab(label, qStrTabName);
	//addTab(pInitialWidget, qStrTabName);
	setTabsClosable(true);

	connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(RemoveTab(int)));

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT MEProjTabWidget::UnInit()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	hrResult = S_OK;
Exit0:
	return hrResult;
}

void MEProjTabWidget::RemoveTab(int index)
{
	// 第一个tab强制不关闭
	if (index)
		removeTab(index);
}

void MEProjTabWidget::AddXmlTabWidget(MEProjTreeWidgetItem* pMEProjTreeWidgetItem, int index)
{
	qDebug() << pMEProjTreeWidgetItem->GetAbsolutePath();
}
