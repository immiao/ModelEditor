///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjTreeWidgetItem.h
// Creator  : Miao Kaixiang
// Date     : 2015-12-28 09:00:00
// Comment  : Declaration of TreeWidgetItem of MEProj
//
///////////////////////////////////////////////////////////////

#ifndef MEPROJTREEWIDGETITEM_H
#define MEPROJTREEWIDGETITEM_H

#include <QTabWidget>
#include <D3DX11.h>
#include <D3D11.h>
#include "KEPublic2.h"
#include <QTreeWidget>

class MEProjTreeWidgetItem : public QTreeWidgetItem
{
private:
	QString m_qStrAbsolutePath;
	QString m_qStrFileName;
public:
	MEProjTreeWidgetItem(const QStringList& strings, const QString& qStrAbsolutePath);
	MEProjTreeWidgetItem(QTreeWidget* parent, const QStringList& strings);
	QString GetAbsolutePath();
};

#endif // MEPROJTREEWIDGETITEM_H