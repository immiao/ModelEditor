///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjRoleListWidgetItem.cpp
// Creator  : Miao Kaixiang
// Date     : 2016-01-02 18:00:00
// Comment  : Implementation of Role ListWidgetItem of MEProj of MEProj
//
///////////////////////////////////////////////////////////////

#include "MEProjRoleListWidgetItem.h"

MEProjRoleListWidgetItem::MEProjRoleListWidgetItem(QString& qStrRoleFileName, QString& qStrRoleFileAbsolutePath, QString& qStrXmlFileName,
		QString& qStrXmlFileAbsolutePath, XMFLOAT3& xmf3Pos, const QIcon& qIcon):QListWidgetItem(qIcon, qStrRoleFileName)
{
	m_qStrRoleFileName = qStrRoleFileName;
	m_qStrRoleFileAbsolutePath = qStrRoleFileAbsolutePath;
	m_qStrXmlFileName = qStrXmlFileName;
	m_qStrXmlFileAbsolutePath = qStrXmlFileAbsolutePath;
	m_xmf3Pos = xmf3Pos;
	m_qIcon = qIcon;
}
