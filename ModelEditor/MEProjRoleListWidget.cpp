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

	//setHeaderLabels(QStringList(QString::fromLocal8Bit("�������������")));
	m_pMEProjServer = pMEProjServer;
	connect(this, SIGNAL(currentRowChanged(int)), this, SLOT(NotifyServerItemUpdateColor(int)));
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

void MEProjRoleListWidget::NotifyServerItemUpdateColor(int index)
{
	if (index < 0)
		return;
	qDebug() << "Who first1??? : " << count();
	m_pMEProjServer->NotifyD3DWidgetUpdateColor(index);
	qDebug() << "Who first2??? : " << count();
}

void MEProjRoleListWidget::DeleteItem() // ��Ȼ����NotifyServerItemIndex
{
	int nRow = currentRow();
	if (nRow < 0)
		return;
	disconnect(this, SIGNAL(currentRowChanged(int)), NULL, NULL);
	QListWidgetItem* p = item(nRow);
	SAFE_DELETE(p); //�������Ȼ���, �������ִ��NotifyServerItemIndex, count��û�еõ�����, Ҫ��disconnect
	m_pMEProjServer->NotifyD3DWidgetUpdateRole();
	NotifyServerItemUpdateColor(currentRow());
	connect(this, SIGNAL(currentRowChanged(int)), this, SLOT(NotifyServerItemUpdateColor(int)));
}
