///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjTabWidget.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-12-28 10:00:00
// Comment  : Implementation of TreeWidgetItem of MEProj
//
///////////////////////////////////////////////////////////////

#include "MEProjTreeWidgetItem.h"

MEProjTreeWidgetItem::MEProjTreeWidgetItem(const QStringList& strings, const QString& qStrAbsolutePath):QTreeWidgetItem(strings)
{
	m_qStrAbsolutePath = qStrAbsolutePath;
	m_qStrFileName = strings.at(0);
}

MEProjTreeWidgetItem::MEProjTreeWidgetItem(QTreeWidget* parent, const QStringList& strings):QTreeWidgetItem(parent, strings)
{

}

QString MEProjTreeWidgetItem::GetAbsolutePath()
{
	return m_qStrAbsolutePath;
}
