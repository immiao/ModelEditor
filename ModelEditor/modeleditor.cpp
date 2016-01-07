///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : modeleditor.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-7-30 15:00:00
// Comment  : Implementation of Qt Main Window
//
///////////////////////////////////////////////////////////////

#include "modeleditor.h"
#include <QDebug>

// try pull
ModelEditor::ModelEditor(QWidget *pParent)
	: QMainWindow(pParent)
{
	ui.setupUi(this);
	m_nState = -1; // -1代表尚未建立widget
	m_pD3dWidget = NULL;
	m_pMEProjD3DWidget = NULL;
	m_pQPushButtonAddRole = NULL;
	m_pHBoxLayout = NULL;
	m_pVBoxLayout = NULL;
	m_pLayout = NULL;

	connect(ui.openObjFile, SIGNAL(triggered()),
		this, SLOT(OpenObjFileTriggered()));
	connect(ui.openM3dFile, SIGNAL(triggered()),
		this, SLOT(OpenM3dFileTriggered()));
	connect(ui.openMEProjFile, SIGNAL(triggered()),
		this, SLOT(OpenMEProjFileTriggered()));

}

HRESULT ModelEditor::Init()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;
	
	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT ModelEditor::UnInit()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	switch (m_nState)
	{
	case 0:
	case 1:
		hrRetCode = m_pD3dWidget->UnInit();
		KE_COM_PROCESS_ERROR(hrRetCode);
		SAFE_DELETE(m_pD3dWidget);
		SAFE_DELETE(m_pLayout);
		break;
	case 2:
		hrRetCode = m_pMEProjD3DWidget->UnInit();
		KE_COM_PROCESS_ERROR(hrRetCode);
		SAFE_DELETE(m_pMEProjD3DWidget);

		hrRetCode = m_pMEProjTreeWidget->UnInit();
		KE_COM_PROCESS_ERROR(hrRetCode);
		SAFE_DELETE(m_pMEProjTreeWidget);

		hrRetCode = m_pMEProjRoleListWidget->UnInit();
		KE_COM_PROCESS_ERROR(hrRetCode);
		SAFE_DELETE(m_pMEProjTabWidget);

		hrRetCode = m_pMEProjTabWidget->UnInit();
		KE_COM_PROCESS_ERROR(hrRetCode);
		SAFE_DELETE(m_pMEProjTabWidget);

		SAFE_DELETE(m_pLayout); // 此处会把子Layout也Delete，包括m_pHBoxLayout和m_pVBoxLayout
		SAFE_DELETE(m_pQPushButtonAddRole);
		SAFE_DELETE(m_pQPushButtonDeleteRole);

		break;
	default:
		break;
	}

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT ModelEditor::InitBasicWidget()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	m_pD3dWidget = new D3DWidget();
	KE_PROCESS_ERROR(m_pD3dWidget);
	hrRetCode = m_pD3dWidget->Init();
	KE_COM_PROCESS_ERROR(hrRetCode);
	//dxWidget->show();
	m_pLayout = new QHBoxLayout;
	KE_PROCESS_ERROR(m_pLayout);
	m_pLayout->addWidget(m_pD3dWidget);
	ui.centralWidget->setLayout(m_pLayout);

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT ModelEditor::InitMEProjWidget(const QString& qStrFileName)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	m_pLayout = new QHBoxLayout;
	KE_PROCESS_ERROR(m_pLayout);
	m_pVBoxLayout = new QVBoxLayout;
	KE_PROCESS_ERROR(m_pVBoxLayout);
	m_pHBoxLayout = new QHBoxLayout;
	KE_PROCESS_ERROR(m_pHBoxLayout);

	m_pMEProjServer = new MEProjServer();
	KE_PROCESS_ERROR(m_pMEProjServer);

	m_pMEProjTreeWidget = new MEProjTreeWidget();
	KE_PROCESS_ERROR(m_pMEProjTreeWidget);
	hrRetCode = m_pMEProjTreeWidget->Init(m_pMEProjServer, qStrFileName);
	KE_COM_PROCESS_ERROR(hrRetCode);

	m_pMEProjRoleListWidget = new MEProjRoleListWidget();
	KE_PROCESS_ERROR(m_pMEProjRoleListWidget);
	hrRetCode = m_pMEProjRoleListWidget->Init(m_pMEProjServer);
	KE_COM_PROCESS_ERROR(hrRetCode);

	m_pQPushButtonAddRole = new QPushButton(QIcon("Resources/add.png"), QString(QString::fromLocal8Bit("添加新角色")));
	KE_PROCESS_ERROR(m_pQPushButtonAddRole);
	m_pQPushButtonDeleteRole = new QPushButton(QString(QString::fromLocal8Bit("删除角色")));
	KE_PROCESS_ERROR(m_pQPushButtonDeleteRole);

	// 暂时用D3DWidget来初始化Tab1，2015/12/23
	//m_pD3dWidget = new D3DWidget();
	//KE_PROCESS_ERROR(m_pD3dWidget);
	//hrRetCode = m_pD3dWidget->Init();
	//KE_COM_PROCESS_ERROR(hrRetCode);
	// 暂时用D3DWidget来初始化Tab1，2015/12/23

	m_pMEProjD3DWidget = new MEProjD3DWidget(m_pMEProjServer);
	KE_PROCESS_ERROR(m_pMEProjD3DWidget);
	hrRetCode = m_pMEProjD3DWidget->Init();
	KE_COM_PROCESS_ERROR(hrRetCode);

	m_pMEProjTabWidget = new MEProjTabWidget();
	KE_PROCESS_ERROR(m_pMEProjTabWidget);
	hrRetCode = m_pMEProjTabWidget->Init(m_pMEProjServer, m_pMEProjD3DWidget, QFileInfo(qStrFileName).fileName());
	KE_COM_PROCESS_ERROR(hrRetCode);

	connect(ui.action_save, SIGNAL(triggered()), m_pMEProjTabWidget, SLOT(SaveCurrentFile()));
	connect(ui.action_save, SIGNAL(triggered()), m_pMEProjD3DWidget, SLOT(BuildUpTimeLine()));
	connect(ui.action_play, SIGNAL(triggered()), m_pMEProjD3DWidget, SLOT(Play()));
	connect(ui.action_stop, SIGNAL(triggered()), m_pMEProjD3DWidget, SLOT(Stop()));
	connect(m_pQPushButtonAddRole, SIGNAL(clicked()), this, SLOT(OpenConfigWidget()));

	hrRetCode = m_pMEProjServer->Init(m_pMEProjTreeWidget, m_pMEProjTabWidget, m_pMEProjRoleListWidget, m_pMEProjD3DWidget);
	KE_COM_PROCESS_ERROR(hrRetCode);

	m_pMEProjTreeWidget->setFixedWidth(200);
	m_pMEProjTreeWidget->setFixedHeight(400);
	m_pVBoxLayout->addWidget(m_pMEProjTreeWidget);
	m_pHBoxLayout->addWidget(m_pQPushButtonAddRole);
	m_pHBoxLayout->addWidget(m_pQPushButtonDeleteRole);
	m_pVBoxLayout->addLayout(m_pHBoxLayout);
	m_pVBoxLayout->addWidget(m_pMEProjRoleListWidget);

	m_pLayout->addLayout(m_pVBoxLayout);
	m_pLayout->addWidget(m_pMEProjTabWidget);
	ui.centralWidget->setLayout(m_pLayout);

	hrResult = S_OK;
Exit0:
	return hrResult;
}

ModelEditor::~ModelEditor()
{

}

void ModelEditor::OpenObjFileTriggered()
{
	QString qstrFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "", 0);
	if (!qstrFileName.isNull())
    {
		RemoveWidget(); // 这里没办法处理HRESULT
		m_nState = 0;
		InitBasicWidget(); // 这里没办法处理HRESULT
		m_pD3dWidget->ClearVertexIndiceCounter();
        qDebug() << "FileName:" << qstrFileName;
		QByteArray qByteArray = qstrFileName.toLatin1();
		m_pD3dWidget->ReadVertexIndiceFromObjFile(qByteArray.data());
    }
	else
	{

	}
}

void ModelEditor::OpenM3dFileTriggered()
{
	QString qstrFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "", 0);
	if (!qstrFileName.isNull())
    {
		RemoveWidget(); // 这里没办法处理HRESULT
		m_nState = 1;
		InitBasicWidget(); // 这里没办法处理HRESULT
		m_pD3dWidget->SetReadFinish(false);
		m_pD3dWidget->ClearVertexIndiceCounter();
        qDebug() << "FileName:" << qstrFileName;
		QByteArray qByteArray = qstrFileName.toLatin1();
		m_pD3dWidget->ReadFromM3dFile(qByteArray.data());
    }
	else
	{

	}
}

void ModelEditor::OpenMEProjFileTriggered()
{
	QFileDialog qFileDialog;
	qFileDialog.setNameFilter("*.meproj");
	if (qFileDialog.exec())
    {
		RemoveWidget(); // 这里没办法处理HRESULT
		m_nState = 2;
		QFileInfo qFileInfo(qFileDialog.selectedFiles().at(0));
		InitMEProjWidget(qFileInfo.fileName());
    }
	else
	{

	}
}



HRESULT ModelEditor::RemoveWidget()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	if (m_nState != -1)
	{
		hrRetCode = UnInit();
		KE_COM_PROCESS_ERROR(hrRetCode);
	}

	hrResult = S_OK;
Exit0:
	return hrResult;
}

void ModelEditor::OpenConfigWidget()
{
	m_pMEProjRoleConfigWidget = new MEProjRoleConfigWidget(m_pMEProjServer);
	qDebug() << "OK-1";
	m_pMEProjRoleConfigWidget->Init();
	m_pMEProjRoleConfigWidget->show();
}