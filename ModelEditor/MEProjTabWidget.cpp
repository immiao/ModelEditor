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
#include <iterator>

MEProjTabWidget::MEProjTabWidget(QWidget* pParent):QTabWidget(pParent)
{
	m_pMEProjServer = NULL;
	m_lpQWidget.clear();
	m_mHash.clear();
}

HRESULT MEProjTabWidget::Init(MEProjServer* pMEProjServer, QWidget* pInitialWidget, QString& qStrTabName)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	m_pMEProjServer = pMEProjServer;

	addTab(pInitialWidget, qStrTabName);
	//第一个Tab不关闭，不属于CodeWidget，为保持index一致，放入空TabInformation
	TabInformation emptyTabInformation;
	m_lpQWidget.push_back(emptyTabInformation);

	//addTab(pInitialWidget, qStrTabName);
	setTabsClosable(true);

	connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(RemoveTab(int)));
	//connect(m_pParent->ui.action_save, SIGNAL(triggered()), this, SLOT(SaveCurrentFile()));

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
	{
		removeTab(index);
		std::list<TabInformation>::iterator iter = m_lpQWidget.begin();
		std::advance(iter, index);
		m_mHash[(*iter).qStrFileAbsolutePath] = false;
		SAFE_DELETE((*iter).pMEProjCodeWidget);
		m_lpQWidget.erase(iter);
	}
}

void MEProjTabWidget::AddXmlTabWidget(MEProjTreeWidgetItem* pMEProjTreeWidgetItem, int index)
{
	QString qStrPath = pMEProjTreeWidgetItem->GetAbsolutePath();
	if (m_mHash[qStrPath])
		return;
	m_mHash[qStrPath] = true;

	bool bFlag = false;
	QFile *pQFile = new QFile(qStrPath);
	QString qStrFileName = qStrPath.section('/',-1,-1);
	
    // Read file if open successfully
	bFlag = pQFile->open(QIODevice::ReadWrite | QIODevice::Text);	
	if (bFlag)
	{
		QString qStrXmlData = QString(pQFile->readAll());
		MEProjCodeWidget *pEditor = new MEProjCodeWidget;

		TabInformation tabInformation;
		tabInformation.pMEProjCodeWidget = pEditor;
		tabInformation.qStrFileAbsolutePath = qStrPath;
		tabInformation.nIndex = count();

		m_lpQWidget.push_back(tabInformation);

		pEditor->setPlainText(qStrXmlData);

		addTab(pEditor, qStrFileName);
		
	}
	
	SAFE_DELETE(pQFile);
}

void MEProjTabWidget::SaveCurrentFile()
{
	
	qDebug()<<currentIndex()<<endl;
	qDebug()<<"Test";
}