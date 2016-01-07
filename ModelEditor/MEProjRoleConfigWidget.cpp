///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjRoleListWidget.cpp
// Creator  : Miao Kaixiang
// Date     : 2016-01-01 20:00:00
// Comment  : Implementation of Role Configuration Widget in MEProj
//
///////////////////////////////////////////////////////////////

#include "MEProjRoleConfigWidget.h"
#include <QDebug>

MEProjRoleConfigWidget::MEProjRoleConfigWidget(MEProjServer* pMEProjServer, QWidget* pParent):QWidget(pParent)
{
	m_pVBoxLayout = NULL;
	m_pHBoxLayout = NULL;
	m_pHBoxLayout1 = NULL;
	m_pHBoxLayout2 = NULL;
	m_pHBoxLayout3 = NULL;
	m_pComboBoxRoleFileName = NULL;
	m_pComboBoxXmlFileName = NULL;
	m_pLineEditX = NULL;
	m_pLineEditY = NULL;
	m_pLineEditZ = NULL;
	m_pLabelName = NULL;
	m_pLabelXml = NULL;
	m_pLabelX = NULL;
	m_pLabelY = NULL;
	m_pLabelZ = NULL;
	m_pPushButtonOK = NULL;
	m_pPushButtonCancel = NULL;

	m_pMEProjServer = pMEProjServer;
	setWindowTitle(QString::fromLocal8Bit("添加新角色"));
}

HRESULT MEProjRoleConfigWidget::Init()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;
	QDir			qDir;
	QStringList		qStrListM3dFilters;
	QStringList		qStrListXmlFilters;
	QRegExp regExp("^-?\\d+$"); 

	qStrListM3dFilters << "*.m3d";
	qStrListXmlFilters << "*.xml";

	m_pVBoxLayout = new QVBoxLayout;
	KE_PROCESS_ERROR(m_pVBoxLayout);
	m_pHBoxLayout = new QHBoxLayout;
	KE_PROCESS_ERROR(m_pHBoxLayout);	
	m_pHBoxLayout1 = new QHBoxLayout;
	KE_PROCESS_ERROR(m_pHBoxLayout1);	
	m_pHBoxLayout2 = new QHBoxLayout;
	KE_PROCESS_ERROR(m_pHBoxLayout2);
	m_pHBoxLayout3 = new QHBoxLayout;
	KE_PROCESS_ERROR(m_pHBoxLayout3);

	m_pComboBoxRoleFileName = new QComboBox();
	KE_PROCESS_ERROR(m_pComboBoxRoleFileName);
	qDir.setNameFilters(qStrListM3dFilters);
	m_qStrListRoleFilesName = qDir.entryList();
	m_qFileInfoListRole = qDir.entryInfoList();
	m_pComboBoxRoleFileName->addItems(m_qStrListRoleFilesName);

	m_pComboBoxXmlFileName = new QComboBox();
	KE_PROCESS_ERROR(m_pComboBoxXmlFileName);
	qDir.setNameFilters(qStrListXmlFilters);
	m_qStrListXmlFilesName = qDir.entryList();
	m_qFileInfoListXml = qDir.entryInfoList();
	m_pComboBoxXmlFileName->addItems(m_qStrListXmlFilesName);

	m_pLineEditX = new QLineEdit();
	KE_PROCESS_ERROR(m_pLineEditX);
	m_pLineEditY = new QLineEdit();
	KE_PROCESS_ERROR(m_pLineEditY);
	m_pLineEditZ = new QLineEdit();
	KE_PROCESS_ERROR(m_pLineEditZ);
	m_pLabelName = new QLabel(QString::fromLocal8Bit("角色"));
	KE_PROCESS_ERROR(m_pLabelName);
	m_pLabelXml = new QLabel(QString::fromLocal8Bit("Xml动画文件"));
	KE_PROCESS_ERROR(m_pLabelXml);
	m_pLabelX = new QLabel(QString::fromLocal8Bit("X："));
	KE_PROCESS_ERROR(m_pLabelX);
	m_pLabelY = new QLabel(QString::fromLocal8Bit("Y："));
	KE_PROCESS_ERROR(m_pLabelY);
	m_pLabelZ = new QLabel(QString::fromLocal8Bit("Z："));
	KE_PROCESS_ERROR(m_pLabelZ);
	m_pPushButtonOK = new QPushButton(QString::fromLocal8Bit("确定"));
	KE_PROCESS_ERROR(m_pPushButtonOK);
	m_pPushButtonCancel = new QPushButton(QString::fromLocal8Bit("取消"));
	KE_PROCESS_ERROR(m_pPushButtonCancel);

	m_pValidator = new QRegExpValidator(regExp, this);
	KE_PROCESS_ERROR(m_pValidator);
	
	m_pHBoxLayout->addWidget(m_pLabelName);
	m_pHBoxLayout->addWidget(m_pComboBoxRoleFileName);
	m_pHBoxLayout1->addWidget(m_pLabelXml);
	m_pHBoxLayout1->addWidget(m_pComboBoxXmlFileName);
	m_pHBoxLayout2->addWidget(m_pLabelX);
	m_pHBoxLayout2->addWidget(m_pLineEditX);
	m_pHBoxLayout2->addWidget(m_pLabelY);
	m_pHBoxLayout2->addWidget(m_pLineEditY);
	m_pHBoxLayout2->addWidget(m_pLabelZ);
	m_pHBoxLayout2->addWidget(m_pLineEditZ);
	m_pHBoxLayout3->addWidget(m_pPushButtonOK);
	m_pHBoxLayout3->addWidget(m_pPushButtonCancel);

	m_pVBoxLayout->addLayout(m_pHBoxLayout);
	m_pVBoxLayout->addLayout(m_pHBoxLayout1);
	m_pVBoxLayout->addLayout(m_pHBoxLayout2);
	m_pVBoxLayout->addLayout(m_pHBoxLayout3);

	setLayout(m_pVBoxLayout);
	m_pLineEditX->setValidator(m_pValidator);
	m_pLineEditY->setValidator(m_pValidator);
	m_pLineEditZ->setValidator(m_pValidator);
	connect(m_pPushButtonOK, SIGNAL(clicked()), this, SLOT(AddNewRole()));
	connect(m_pPushButtonOK, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(this, SIGNAL(currentRowChanged(int)), this, SLOT(NotifyServerItemIndex(int)));
	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT MEProjRoleConfigWidget::UnInit()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	//SAFE_DELETE(m_pComboBoxRoleFileName);
	//SAFE_DELETE(m_pComboBoxXmlFileName);
	//SAFE_DELETE(m_pLineEditX);
	//SAFE_DELETE(m_pLineEditY);
	//SAFE_DELETE(m_pLineEditZ);
	//SAFE_DELETE(m_pLabelName);
	//SAFE_DELETE(m_pLabelXml);
	//SAFE_DELETE(m_pLabelX);
	//SAFE_DELETE(m_pLabelY);
	//SAFE_DELETE(m_pLabelZ);
	//SAFE_DELETE(m_pPushButtonOK);
	//SAFE_DELETE(m_pPushButtonCancel);
	//SAFE_DELETE(m_pValidator);

	hrResult = S_OK;
Exit0:
	return hrResult;
}

MEProjRoleConfigWidget::~MEProjRoleConfigWidget()
{

}

void MEProjRoleConfigWidget::AddNewRole()
{
	XMFLOAT3 xmf3Pos;
	xmf3Pos.x = m_pLineEditX->text().toInt();
	xmf3Pos.y = m_pLineEditY->text().toInt();
	xmf3Pos.z = m_pLineEditZ->text().toInt();

	qDebug() << m_pComboBoxXmlFileName->currentText();
	qDebug() << m_qFileInfoListXml.at(m_pComboBoxXmlFileName->currentIndex()).absoluteFilePath();

	m_pMEProjServer->ConfigNotifyRoleList(m_pComboBoxRoleFileName->currentText(),
		m_qFileInfoListRole.at(m_pComboBoxRoleFileName->currentIndex()).absoluteFilePath(),
		m_pComboBoxXmlFileName->currentText(),
		m_qFileInfoListXml.at(m_pComboBoxXmlFileName->currentIndex()).absoluteFilePath(),
		xmf3Pos);
}

void MEProjRoleConfigWidget::NotifyServerItemIndex(int index)
{
	m_pMEProjServer->NotifyD3DWidgetUpdateColor(index);
}
