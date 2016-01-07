///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjListWidget.h
// Creator  : Miao Kaixiang
// Date     : 2015-12-21 09:00:00
// Comment  : Declaration of TabWidget of MEProj
//
///////////////////////////////////////////////////////////////

#ifndef MEPROJTABWIDGET_H
#define MEPROJTABWIDGET_H

#include <QTabWidget>
#include <D3DX11.h>
#include <D3D11.h>
#include <list>
#include <map>
#include "KEPublic2.h"
#include "MEProjServer.h"
#include "MEProjTreeWidgetItem.h"
#include "MEProjCodeWidget.h"
#include "MEProjHighlighter.h"
#include <vector>

struct TabInformation
{
	MEProjCodeWidget*	pMEProjCodeWidget;
	QString				qStrFileAbsolutePath;
};

class MEProjServer;
class MEProjTabWidget : public QTabWidget
{
	Q_OBJECT
	
private:
	MEProjServer*				m_pMEProjServer;
	std::vector<TabInformation>	m_vTabInfo;
	std::vector<MEProjHighlighter*>	m_vHighlighter;
	std::map<QString, bool>		m_mHash;
	std::map<QString, int>		m_mHashTabIndex;
	
	QWidget*        m_pParent;	

private slots:
	void RemoveTab(int index);

public:
	MEProjTabWidget(QWidget* pParent = NULL);
	void AddXmlTabWidget(MEProjTreeWidgetItem* pMEProjTreeWidgetItem, int index);
	void FileSave(int nIndex);
	HRESULT Init(MEProjServer* pMEProjServer, QWidget* pInitialWidget, QString& qStrTabName);
	HRESULT UnInit();

public slots:
	void SaveCurrentFile();
	void SaveAllFile();
};

#endif // MEPROJTABWIDGET_H