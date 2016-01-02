///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjRoleListWidgetItem.h
// Creator  : Miao Kaixiang
// Date     : 2016-01-02 16:00:00
// Comment  : Declaration of Role ListWidgetItem of MEProj
//
///////////////////////////////////////////////////////////////

#ifndef MEPROJROLELISTWIDGETITEM_H
#define MEPROJROLELISTWIDGETITEM_H

#include <D3DX11.h>
#include <D3D11.h>
#include <xnamath.h>
#include "KEPublic2.h"
#include <QListWidgetItem>
#include <QString>

class MEProjRoleListWidgetItem : public QListWidgetItem
{
private:
	QString		m_qStrRoleName;
	QString		m_qStrXmlFileName;
	QString		m_qStrXmlFileAbsolutePath;
	QIcon		m_qIcon;
	XMFLOAT3	m_xmf3Pos;
public:
	MEProjRoleListWidgetItem(QString& qStrRoleName, QString& qStrXmlFileName, QString& qStrXmlFileAbsolutePath, XMFLOAT3& xmf3Pos,
		const QIcon& qIcon);
};

#endif // MEPROJROLELISTWIDGETITEM_H