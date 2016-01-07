///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjTreeWidget.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-12-21 10:00:00
// Comment  : Implementation of TreeWidget of MEProj
//
///////////////////////////////////////////////////////////////

#include "MEProjTreeWidget.h"

MEProjTreeWidget::MEProjTreeWidget(QWidget* pParent):QTreeWidget(pParent)
{
	m_pQRootTreeWidgetItem = NULL;
	m_pQTreeWidgetItem = NULL;
}

HRESULT MEProjTreeWidget::Init(MEProjServer* pMEProjServer, const QString& qStrFileName)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	m_pMEProjServer = pMEProjServer;

	QDir			qDir;
	QStringList		qStrListTreeFilters;
	QStringList		qStrListRootFileName(qStrFileName);
	QStringList		qStrListChildenFileName;
	QString			qStrChildFileName;
	QFileInfoList	qFileInfoList;

	m_pQRootTreeWidgetItem = new MEProjTreeWidgetItem(this, qStrListRootFileName);
	//m_pQRootTreeWidgetItem = new QTreeWidgetItem(this, qStrListRootFileName);
	KE_PROCESS_ERROR(m_pQRootTreeWidgetItem);
	m_pQRootTreeWidgetItem->setIcon(0, QIcon("Resources/Project.png"));
	qStrListTreeFilters << "*.xml";
	qDir.setNameFilters(qStrListTreeFilters);

	qStrListChildenFileName = qDir.entryList();
	qFileInfoList			= qDir.entryInfoList();
	
	int	nFileInfoListIndex = 0;

	foreach (qStrChildFileName, qStrListChildenFileName)
	{
		QStringList qStrListChildFileName(qStrChildFileName); // 只有一列的StringList
		m_pQTreeWidgetItem = new MEProjTreeWidgetItem(qStrListChildFileName, qFileInfoList.at(nFileInfoListIndex).absoluteFilePath());
		qDebug() << qFileInfoList.at(nFileInfoListIndex).absoluteFilePath();
		//m_pQTreeWidgetItem = new QTreeWidgetItem(qStrListChildFileName);
		
		KE_PROCESS_ERROR(m_pQTreeWidgetItem);
		m_pQTreeWidgetItem->setIcon(0, QIcon("Resources/File.png"));
		m_pQRootTreeWidgetItem->addChild(m_pQTreeWidgetItem);
		nFileInfoListIndex++;
	}
	
	setHeaderLabels(QStringList(QString::fromLocal8Bit("解决方案管理器")));
	addTopLevelItem(m_pQRootTreeWidgetItem);
	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(NotifyServer(QTreeWidgetItem*, int)));
	//connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(NotifyServer(QTreeWidgetItem*, int)));
	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT MEProjTreeWidget::UnInit()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	//SAFE_DELETE(m_pQTreeWidgetItem);
	SAFE_DELETE(m_pQRootTreeWidgetItem);

	hrResult = S_OK;
Exit0:
	return hrResult;
}

void MEProjTreeWidget::NotifyServer(QTreeWidgetItem* pQTreeWidgetItem, int index)
{
	m_pMEProjServer->TreeNotifyTab(dynamic_cast<MEProjTreeWidgetItem*>(pQTreeWidgetItem), index);
	qDebug() << "Item Double Clicked";
}

void MEProjTreeWidget::Highlight(const QString& qStrXmlPath)
{
	QTreeWidgetItem* root = topLevelItem(0);
	int nRootChildNum = root->childCount();
	qDebug() << "WOCAONIMA : " << nRootChildNum;
	for (int i = 0; i < nRootChildNum; i++)
	{
		MEProjTreeWidgetItem* p = dynamic_cast<MEProjTreeWidgetItem*>(root->child(i));
		qDebug() << "ONE:" << qStrXmlPath;
		qDebug() << "TWO:" << p->GetAbsolutePath();
		if (p->GetAbsolutePath() == qStrXmlPath)
		{
			p->setBackgroundColor(0, QColor(255, 0, 0));
			break;
		}
	}
}

void MEProjTreeWidget::ClearHighlight()
{
	QTreeWidgetItem* root = topLevelItem(0);
	int nRootChildNum = root->childCount();
	for (int i = 0; i < nRootChildNum; i++)
	{
		root->child(i)->setBackgroundColor(0, QColor(0, 0, 0, 0));
	}
}