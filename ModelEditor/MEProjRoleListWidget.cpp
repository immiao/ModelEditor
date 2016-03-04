///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjRoleListWidget.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-12-22 14:00:00
// Comment  : Implementation of Role TreeWidget in MEProj
//
///////////////////////////////////////////////////////////////

#include "MEProjRoleListWidget.h"
#include <QDebug>

MEProjRoleListWidget::MEProjRoleListWidget(QWidget* pParent):QListWidget(pParent)
{
	
}

HRESULT MEProjRoleListWidget::Init(MEProjServer* pMEProjServer)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	//setHeaderLabels(QStringList(QString::fromLocal8Bit("解决方案管理器")));
	m_pMEProjServer = pMEProjServer;
	//connect(this, SIGNAL(currentRowChanged(int)), this, SLOT(NotifyServerItemUpdateColor(int)));
	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT MEProjRoleListWidget::UnInit()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	hrResult = S_OK;
Exit0:
	return hrResult;
}

MEProjRoleListWidget::~MEProjRoleListWidget()
{

}

void MEProjRoleListWidget::AddWidgetItem(QString& qStrRoleFileName, QString& qStrRoleFileAbsolutePath, 
	QString& qStrXmlFileName, QString& qStrXmlFileAbsolutePath, XMFLOAT3& xmf3Pos)
{
	MEProjRoleListWidgetItem* pMEProjRoleListWidgetItem = new MEProjRoleListWidgetItem(qStrRoleFileName, qStrRoleFileAbsolutePath, 
		qStrXmlFileName, qStrXmlFileAbsolutePath, xmf3Pos, QIcon("Resources/role.jpg"));
	addItem(pMEProjRoleListWidgetItem);
	m_pMEProjServer->NotifyD3DWidgetUpdateRole();
}

void MEProjRoleListWidget::DeleteItem() // 必然触发NotifyServerItemIndex
{
	int nRow = currentRow();
	if (nRow < 0)
		return;
	//disconnect(this, SIGNAL(currentRowChanged(int)), NULL, NULL);
	QListWidgetItem* p = takeItem(nRow);
	if (!p)
		qDebug() << "ERROR";//触发后先换行, 因此立即执行NotifyServerItemIndex, count还没有得到更新, 要先disconnect
	m_pMEProjServer->NotifyD3DWidgetUpdateRole();
	m_pMEProjServer->NotifyTreeWidgetClearHighlight();
	//connect(this, SIGNAL(currentRowChanged(int)), this, SLOT(NotifyServerItemUpdateColor(int)));
}

void MEProjRoleListWidget::mousePressEvent(QMouseEvent* pEvent)
{
	//重载mousePressEvent需要调用父类方法, 否则currentRowChanged SIGNAL失效, 该函数是通过mousePressEvent来触发的
	QListWidget::mousePressEvent(pEvent); 
	if ((pEvent->button() & Qt::LeftButton) != 0)
	{
		//qDebug() << "mousePressEvent: Click Left Button";
		QListWidgetItem* p = itemAt(pEvent->pos());
		if (!p)
		{
			QListWidgetItem* pCurrent = currentItem();
			if (pCurrent)
			{
				currentItem()->setSelected(false);
				m_pMEProjServer->NotifyD3DWidgetClearItemColor();
				m_pMEProjServer->NotifyTreeWidgetClearHighlight();
			}
		}
		else
		{
			p->setSelected(true);
			qDebug() << "CURRENT:" << currentRow();
			m_pMEProjServer->NotifyD3DWidgetUpdateColor(currentRow());
			m_pMEProjServer->NotifyTreeWidgetClearHighlight();
			m_pMEProjServer->NotifyTreeWidgetHighlight(dynamic_cast<MEProjRoleListWidgetItem*>(p)->GetXmlFilePath());
		}
	}
}
