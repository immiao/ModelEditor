///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : M3dModel.h
// Creator  : Miao Kaixiang
// Date     : 2015-09-23 15:00:00
// Comment  : Declaration of M3d Model
//
///////////////////////////////////////////////////////////////

#ifndef M3DMODEL_H
#define M3DMODEL_H

#include "GeometryGenerator.h"

#define MAX_VERTEX 20000

class M3DModel
{
public:
	GeometryGenerator::SKINNED_VERTEX m_sVertex[MAX_VERTEX];
};

#endif // M3DMODEL_H