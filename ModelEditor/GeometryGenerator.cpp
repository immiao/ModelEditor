///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : modeleditor.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-8-3 15:00:00
// Comment  : Implementation of Geometry Generator
//
///////////////////////////////////////////////////////////////
#include "GeometryGenerator.h"

HRESULT GeometryGenerator::CreateGrid(int nRow, int nCol, MESH_DATA &meshData)
{
	int nVertexNum = nRow * nCol;
	int nGridNum = (nRow - 1) * (nCol - 1);

	meshData.vVertices.clear();
	meshData.vIndices.clear();

	meshData.vVertices.resize(nVertexNum);
	meshData.vIndices.resize(nGridNum * 6);

	for (int i = 0; i < nRow; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			int nIndex = i * nCol + j;
			meshData.vVertices[nIndex].xmf3Pos.x = (i - nRow / 2) * 5;
			meshData.vVertices[nIndex].xmf3Pos.y = 0;
			meshData.vVertices[nIndex].xmf3Pos.z = (j - nCol / 2) * 5;
			meshData.vVertices[nIndex].xmf4Color.x = 0.3f;
			meshData.vVertices[nIndex].xmf4Color.y = 0.3f;
			meshData.vVertices[nIndex].xmf4Color.z = 0.3f;
			meshData.vVertices[nIndex].xmf4Color.w = 1.0f;
		}
	}

	for (int i = 0; i < nGridNum; i++)
	{
		int nGridRow = i / (nCol - 1);
		int nGridCol = i % (nCol - 1);
		int nVertexIndex = nGridRow * nCol + nGridCol;
		int nOffset = i * 6;
		meshData.vIndices[nOffset] = nVertexIndex;
		meshData.vIndices[nOffset + 1] = nVertexIndex + 1;
		meshData.vIndices[nOffset + 2] = nVertexIndex + 1 + nCol;

		meshData.vIndices[nOffset + 3] = nVertexIndex + nCol + 1;
		meshData.vIndices[nOffset + 4] = nVertexIndex + nCol;
		meshData.vIndices[nOffset + 5] = nVertexIndex;
	}

	return S_OK;
}
