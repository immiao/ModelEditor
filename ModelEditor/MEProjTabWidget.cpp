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
	m_mHashTabIndex.clear();
}

HRESULT MEProjTabWidget::Init(MEProjServer* pMEProjServer, QWidget* pInitialWidget, QString& qStrTabName)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	m_pMEProjServer = pMEProjServer;

	addTab(pInitialWidget, qStrTabName);
	//第一个Tab不关闭，不属于CodeWidget，为保持index一致，放入空TabInformation
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
	// 第一个tab强制不关闭
	if (index)
	{
		removeTab(index);

		m_mHash[m_vTabInfo[index].qStrFileAbsolutePath] = false;
		SAFE_DELETE(m_vTabInfo[index].pMEProjCodeWidget);
		m_vTabInfo.erase(m_vTabInfo.begin() + index);
		m_vHighlighter.erase(m_vHighlighter.begin() + index - 1);
	}
}

void MEProjTabWidget::AddXmlTabWidget(MEProjTreeWidgetItem* pMEProjTreeWidgetItem, int index)
{
	QString qStrPath = pMEProjTreeWidgetItem->GetAbsolutePath();
	if (m_mHash[qStrPath])
	{
		setCurrentIndex(m_mHashTabIndex[qStrPath]);
		return;
	}

	bool bFlag = false;
	QFile *pQFile = new QFile(qStrPath);
	QString qStrFileName = qStrPath.section('/',-1,-1);
	
    // Read file if open successfully
	bFlag = pQFile->open(QIODevice::ReadWrite | QIODevice::Text);	
	if (bFlag)
	{
		QFont qFont; // Set the editor font
		qFont.setFamily("Courier");
		qFont.setFixedPitch(true);
		qFont.setPointSize(10);

		QString qStrXmlData = QString(pQFile->readAll());
		MEProjCodeWidget *pEditor = new MEProjCodeWidget;
		pEditor->setFont(qFont);
		MEProjHighlighter *pHighlighter = new MEProjHighlighter(pEditor->document()); // Set the highlighter
		m_vHighlighter.push_back(pHighlighter);

		TabInformation tabInformation;
		tabInformation.pMEProjCodeWidget = pEditor;
		tabInformation.qStrFileAbsolutePath = qStrPath;

		qDebug()<<tabInformation.qStrFileAbsolutePath;
        m_vTabInfo.push_back(tabInformation);

		pEditor->setPlainText(qStrXmlData);
		addTab(pEditor, qStrFileName);
		
		m_mHash[qStrPath] = true;
		m_mHashTabIndex[qStrPath] = m_vTabInfo.size() - 1;
		setCurrentIndex(m_vTabInfo.size() - 1);
	}
	
	SAFE_DELETE(pQFile);
}

void MEProjTabWidget::SaveCurrentFile()
{
	FileSave(currentIndex());
}

void MEProjTabWidget::SaveAllFile()
{
	int nFileNum = m_vTabInfo.size();
	for (int i=1; i<nFileNum; i++)
	{
		FileSave(i);
	}
}

void MEProjTabWidget::FileSave(int nIndex)
{
	QFile *pQFile = new QFile(m_vTabInfo[nIndex].qStrFileAbsolutePath);			
	QString qStrContent = m_vTabInfo[nIndex].pMEProjCodeWidget->toPlainText();
	std::string strTempContent = qStrContent.toStdString();  //将Qstring转换成string，在转成char*写入文件
	const char* pcWriteContent = strTempContent.c_str();

	bool bFlag = false;
	bFlag = pQFile->open(QIODevice::WriteOnly | QIODevice::Text);
	if (bFlag)
	{
		pQFile->write(pcWriteContent);
	}
	SAFE_DELETE(pQFile);
}