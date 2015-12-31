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
m_vTabInfo.clear();
	m_mHash.clear();}

HRESULT MEProjTabWidget::Init(MEProjServer* pMEProjServer, QWidget* pInitialWidget, QString& qStrTabName)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	m_pMEProjServer = pMEProjServer;

	addTab(pInitialWidget, qStrTabName);
	//��һ��Tab���رգ�������CodeWidget��Ϊ����indexһ�£������TabInformation
	TabInformation emptyTabInformation;
	m_vTabInfo.push_back(emptyTabInformation);

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
	// ��һ��tabǿ�Ʋ��ر�
	if (index)
	{
		removeTab(index);

		m_mHash[m_vTabInfo[index].qStrFileAbsolutePath] = false;
		SAFE_DELETE(m_vTabInfo[index].pMEProjCodeWidget);
		m_vTabInfo.erase(m_vTabInfo.begin() + index);
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

		qDebug()<<tabInformation.qStrFileAbsolutePath;
        m_vTabInfo.push_back(tabInformation);

		pEditor->setPlainText(qStrXmlData);
		addTab(pEditor, qStrFileName);
		
	}
	
	SAFE_DELETE(pQFile);
}

void MEProjTabWidget::SaveCurrentFile()
{
	qDebug()<<"00000";
	QFile *pQFile = new QFile(m_vTabInfo[currentIndex()].qStrFileAbsolutePath);			
	QString qStrContent = m_vTabInfo[currentIndex()].pMEProjCodeWidget->toPlainText();
	//qDebug()<<qStrContent;
	std::string strTempContent = qStrContent.toStdString();  //��Qstringת����string����ת��char*д���ļ�
	qDebug()<<"22222";
	const char* pcWriteContent = strTempContent.c_str();
	bool bFlag = false;
	qDebug()<<"33333";

	bFlag = pQFile->open(QIODevice::WriteOnly | QIODevice::Text);
	qDebug()<<"44444";
	if (bFlag)
	{
		pQFile->write(pcWriteContent);
	}
	SAFE_DELETE(pQFile);
	qDebug()<<"55555";

	qDebug()<<currentIndex()<<endl;
	qDebug()<<"Test";
}