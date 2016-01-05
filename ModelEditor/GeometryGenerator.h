///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : dxwidget.h
// Creator  : Miao Kaixiang
// Date     : 2015-7-30 15:00:00
// Comment  : Declaration of Geometry Generator
//
///////////////////////////////////////////////////////////////

#ifndef GEOMETRYGENERATOR_H
#define GEOMETRYGENERATOR_H

#include <d3d11.h>
#include <vector>
#include "xnamath.h"

namespace GeometryGenerator
{
	struct SIMPLE_VERTEX
	{
		XMFLOAT3 xmf3Pos;
		XMFLOAT4 xmf4Color;
		SIMPLE_VERTEX()
		{
			xmf4Color.y = 0.6;
			//fvColor.x = rand()%100/100.0;
			//fvColor.y = rand()%100/100.0;
			//fvColor.z = rand()%100/100.0;
		}
	};

	struct SKINNED_VERTEX
	{
		XMFLOAT3 xmf3Pos;
		XMFLOAT4 xmf4Color;
		XMFLOAT3 xmf3Weight;
		UINT	 uaBoundIndices[4];
		SKINNED_VERTEX()
		{
			xmf4Color.x = 0.0f;
			xmf4Color.y = 0.6f;
			xmf4Color.z = 0.0f;
		}
	};

	struct MESH_DATA
	{
		std::vector<SIMPLE_VERTEX> vVertices;
		std::vector<int> vIndices;
	};

	HRESULT CreateGrid(int nRow, int nCol, MESH_DATA &meshData);
};

#endif // GEOMETRYGENERATOR_H