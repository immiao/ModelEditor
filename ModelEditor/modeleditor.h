///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : dxwidget.h
// Creator  : Miao Kaixiang
// Date     : 2015-7-30 15:00:00
// Comment  : Declaration of Qt Main Window
//
///////////////////////////////////////////////////////////////

#ifndef MODELEDITOR_H
#define MODELEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_modeleditor.h"
#include "KEPublic2.h"
#include "qlayout.h"
#include "d3dwidget.h"
#include "qfiledialog.h"
#include "MEProjTreeWidget.h"
#include "MEProjTabWidget.h"
#include "MEProjServer.h"
#include "MEProjD3DWidget.h"
#include "MEProjRoleListWidget.h"
#include "MEProjRoleConfigWidget.h"
#include <qpushbutton.h>

class ModelEditor : public QMainWindow
{
	Q_OBJECT

public:
	ModelEditor(QWidget *pParent = NULL);
	HRESULT Init();
	HRESULT UnInit();
	~ModelEditor();

private:
	Ui::ModelEditorClass	ui;
	D3DWidget*				m_pD3dWidget;
	MEProjD3DWidget*		m_pMEProjD3DWidget;
	MEProjRoleListWidget*	m_pMEProjRoleListWidget;
	MEProjRoleConfigWidget* m_pMEProjRoleConfigWidget;
	MEProjTreeWidget*		m_pMEProjTreeWidget;
	MEProjTabWidget*		m_pMEProjTabWidget;
	MEProjServer*			m_pMEProjServer;
	QHBoxLayout*			m_pLayout;
	QVBoxLayout*			m_pVBoxLayout;
	QHBoxLayout*			m_pHBoxLayout;
	QPushButton*			m_pQPushButtonAddRole;
	QPushButton*			m_pQPushButtonDeleteRole;
	int						m_nState;	
	HRESULT					InitBasicWidget();
	HRESULT					InitMEProjWidget(const QString& qStrFileName);
	HRESULT					RemoveWidget();

private slots:
	void OpenObjFileTriggered();
	void OpenM3dFileTriggered();
	void OpenMEProjFileTriggered();
	void OpenConfigWidget();
};

#endif // MODELEDITOR_H
