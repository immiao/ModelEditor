///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : MEProjRoleListWidget.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-12-22 14:00:00
// Comment  : Implementation of Role TreeWidget in MEProj
//
///////////////////////////////////////////////////////////////

#include "MEProjRoleListWidget.h"
#include <QDebug>

MEProjRoleListWidget::MEProjRoleListWidget(QWidget* pParent):QListWidget(pParent)
{
	
}

HRESULT MEProjRoleListWidget::Init()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT MEProjRoleListWidget::UnInit()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	hrResult = S_OK;
Exit0:
	return hrResult;
}

MEProjRoleListWidget::~MEProjRoleListWidget()
{

}