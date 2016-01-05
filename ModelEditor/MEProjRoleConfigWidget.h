///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjRoleListWidget.h
// Creator  : Miao Kaixiang
// Date     : 2016-01-01 20:00:00
// Comment  : Declaration of role configuration Widget in MEProj
//
///////////////////////////////////////////////////////////////

#ifndef MEPROJROLECONFIGWIDGET_H
#define MEPROJROLECONFIGWIDGET_H

#include "KEPublic2.h"
// 这两个定义了E_FAIL和S_OK
#include <d3d11.h>
#include <d3dx11.h>
#include <QWidget>
#include <QLayout>
#include <QComboBox>
#include <QInputDialog>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <QLineEdit>
#include <QValidator>
#include "MEProjServer.h"
#include <QDir>
#include <QFileInfo>

class MEProjRoleConfigWidget: public QWidget
{
	Q_OBJECT

	QVBoxLayout*	m_pVBoxLayout;
	QHBoxLayout*	m_pHBoxLayout;
	QHBoxLayout*	m_pHBoxLayout1;
	QHBoxLayout*	m_pHBoxLayout2;
	QHBoxLayout*	m_pHBoxLayout3;
	QComboBox*		m_pComboBoxRoleFileName;
	QComboBox*		m_pComboBoxXmlFileName;
	QLineEdit*		m_pLineEditX;
	QLineEdit*		m_pLineEditY;
	QLineEdit*		m_pLineEditZ;
	QLabel*			m_pLabelName;
	QLabel*			m_pLabelXml;
	QLabel*			m_pLabelX;
	QLabel*			m_pLabelY;
	QLabel*			m_pLabelZ;
	QPushButton*	m_pPushButtonOK;
	QPushButton*	m_pPushButtonCancel;
	QRegExpValidator*	m_pValidator;

	MEProjServer*	m_pMEProjServer;
	QStringList		m_qStrListXmlFilesName;
	QFileInfoList	m_qFileInfoListXml;
	QStringList		m_qStrListRoleFilesName;
	QFileInfoList	m_qFileInfoListRole;
public:
	MEProjRoleConfigWidget(MEProjServer* m_pMEProjServer, QWidget* pParent = NULL);
	~MEProjRoleConfigWidget();
	HRESULT Init();
	HRESULT UnInit();
private slots:
	void AddNewRole();
};

#endif // MEPROJROLECONFIGWIDGET_H