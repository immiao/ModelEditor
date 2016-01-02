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

MEProjRoleListWidgetItem::MEProjRoleListWidgetItem(QString& qStrRoleName, QString& qStrXmlFileName, QString& qStrXmlFileAbsolutePath, 
												   XMFLOAT3& xmf3Pos, const QIcon& qIcon):QListWidgetItem(qIcon, qStrRoleName)
{
	m_qStrRoleName = qStrRoleName;
	m_qStrXmlFileName = qStrXmlFileName;
	m_qStrXmlFileAbsolutePath = qStrXmlFileAbsolutePath;
	m_xmf3Pos = xmf3Pos;
	m_qIcon = qIcon;
}
