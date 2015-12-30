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
#include "MEProjCodeWidget.h"
#include <QLabel>
#include <QDebug>

MEProjTabWidget::MEProjTabWidget(QWidget* pParent):QTabWidget(pParent)
{
	m_pParent = pParent;
}

HRESULT MEProjTabWidget::Init(MEProjServer* pMEProjServer, QWidget* pInitialWidget, QString& qStrTabName)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	m_pMEProjServer = pMEProjServer;

	addTab(pInitialWidget, qStrTabName);
	//addTab(pInitialWidget, qStrTabName);
	setTabsClosable(true);

	connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(RemoveTab(int)));
	connect(m_pParent->ui.action_save, SIGNAL(triggered()), this, SLOT(SaveCurrentFile()));

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
	bool bFlag = false;
	QString qStrPath = pMEProjTreeWidgetItem->GetAbsolutePath();
	QFile *pqFile = new QFile(qStrPath);
	QString qStrFileName = qStrPath.section('/',-1,-1);
	
    // Read file if open successfully
	bFlag = pqFile->open(QIODevice::ReadWrite | QIODevice::Text);	
	if (bFlag)
	{
		QString qXmlData = QString(pqFile->readAll());
		MEProjCodeWidget *pEditor = new MEProjCodeWidget;
		pEditor->setPlainText(qXmlData);
		addTab(pEditor, qStrFileName);
		qDebug()<<"hhh";
	}
}

void MEProjTabWidget::SaveCurrentFile()
{
	qDebug()<<currentIndex()<<endl;
}