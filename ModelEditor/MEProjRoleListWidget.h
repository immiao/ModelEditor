///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjRoleListWidget.h
// Creator  : Miao Kaixiang
// Date     : 2015-12-31 11:00:00
// Comment  : Declaration of Role TreeWidget in MEProj
//
///////////////////////////////////////////////////////////////

#ifndef MEPROJROLELISTWIDGET_H
#define MEPROJROLELISTWIDGET_H

#include "KEPublic2.h"
// 这两个定义了E_FAIL和S_OK
#include <d3d11.h>
#include <d3dx11.h>
#include <QListWidget>

class MEProjRoleListWidget: public QListWidget
{
	Q_OBJECT
public:
	MEProjRoleListWidget(QWidget* pParent = NULL);
	~MEProjRoleListWidget();
	HRESULT Init();
	HRESULT UnInit();
};

#endif // MEPROJROLELISTWIDGET_H