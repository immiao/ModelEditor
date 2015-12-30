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

	connect(ui.openObjFile, SIGNAL(triggered()),
		this, SLOT(openObjFileTriggered()));
	connect(ui.openM3dFile, SIGNAL(triggered()),
		this, SLOT(openM3dFileTriggered()));
	connect(ui.openMEProjFile, SIGNAL(triggered()),
		this, SLOT(openMEProjFileTriggered()));

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
		hrRetCode = m_pD3dWidget->UnInit();
		KE_COM_PROCESS_ERROR(hrRetCode);
		SAFE_DELETE(m_pD3dWidget);

		hrRetCode = m_pMEProjTreeWidget->UnInit();
		KE_COM_PROCESS_ERROR(hrRetCode);
		SAFE_DELETE(m_pMEProjTreeWidget);

		hrRetCode = m_pMEProjTabWidget->UnInit();
		KE_COM_PROCESS_ERROR(hrRetCode);
		SAFE_DELETE(m_pMEProjTabWidget);

		SAFE_DELETE(m_pLayout);
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

	m_pMEProjServer = new MEProjServer();
	KE_PROCESS_ERROR(m_pMEProjServer);

	m_pMEProjTreeWidget = new MEProjTreeWidget();
	KE_PROCESS_ERROR(m_pMEProjTreeWidget);
	hrRetCode = m_pMEProjTreeWidget->Init(m_pMEProjServer, qStrFileName);
	KE_COM_PROCESS_ERROR(hrRetCode);

	// 暂时用D3DWidget来初始化Tab1，2015/12/23
	m_pD3dWidget = new D3DWidget();
	KE_PROCESS_ERROR(m_pD3dWidget);
	hrRetCode = m_pD3dWidget->Init();
	KE_COM_PROCESS_ERROR(hrRetCode);
	// 暂时用D3DWidget来初始化Tab1，2015/12/23

	m_pMEProjTabWidget = new MEProjTabWidget();
	KE_PROCESS_ERROR(m_pMEProjTabWidget);
	hrRetCode = m_pMEProjTabWidget->Init(m_pMEProjServer, m_pD3dWidget, QFileInfo(qStrFileName).fileName());
	KE_COM_PROCESS_ERROR(hrRetCode);
	connect(ui.action_save,SIGNAL(triggered()),m_pMEProjTabWidget,)

	hrRetCode = m_pMEProjServer->Init(m_pMEProjTreeWidget, m_pMEProjTabWidget);
	KE_COM_PROCESS_ERROR(hrRetCode);

	m_pMEProjTreeWidget->setFixedWidth(200);
	//m_pMEProjTabWidget->setFixedHeight(500);
	m_pLayout->addWidget(m_pMEProjTreeWidget);
	m_pLayout->addWidget(m_pMEProjTabWidget);
	ui.centralWidget->setLayout(m_pLayout);

	hrResult = S_OK;
Exit0:
	return hrResult;
}

ModelEditor::~ModelEditor()
{

}

void ModelEditor::openObjFileTriggered()
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

void ModelEditor::openM3dFileTriggered()
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

void ModelEditor::openMEProjFileTriggered()
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