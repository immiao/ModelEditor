///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : dxwidget.h
// Creator  : Miao Kaixiang
// Date     : 2015-7-30 15:00:00
// Comment  : Declaration of DirectX Widget
//
///////////////////////////////////////////////////////////////

#ifndef D3DWIDGET_H
#define D3DWIDGET_H

#define MAX_VERTEX 10000
#define MAX_VERTEX_INDICE 100000
#define MAX_NORMAL 10000
#define MAX_NORMAL_INDICE 100000
#define MAX_TEXCOORD 10000
#define MAX_TEXCOORD_INDICE 100000

#include "ui_modeleditor.h"
#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include "KEPublic2.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx11effect.h>
//#include <xnamath.h>
#include "GeometryGenerator.h"
#include <stdlib.h>

struct Subset
{
	int nFaceStart;
	int nFaceCount;
	WCHAR cDiffuseTexPath[100];
};

struct Keyframe
{
    float TimePos;
	XMFLOAT3 Translation;
	XMFLOAT3 Scale;
	XMFLOAT4 RotationQuat;
};

struct BoneAnimation
{
	//float GetStartTime()const;
	//float GetEndTime()const;

 //   void Interpolate(float t, XMFLOAT4X4& M)const;

	std::vector<Keyframe> Keyframes; 	

};

struct AnimationClip
{
	//float GetClipStartTime()const;
	//float GetClipEndTime()const;

 //   void Interpolate(float t, std::vector<XMFLOAT4X4>& boneTransforms)const;
	float fEndTime;
    std::vector<BoneAnimation> BoneAnimations;
	void GetEndTime();
};

class TestQt;
class D3DWidget : public QWidget
{
	Q_OBJECT
	// Q_DISABLE_COPY(d3DRenderWidget)
public:
	XMFLOAT4X4 M;


	D3DWidget(QWidget* pParent = NULL);
	HRESULT Init();
	HRESULT UnInit();
	void ClearVertexIndiceCounter();
	void SetReadFinish(bool bFlag);
	HRESULT ReadVertexIndiceFromObjFile(char* pcFileName);
	HRESULT ReadFromM3dFile(char* pcFileName);
	~D3DWidget();

private:
	std::vector<Subset>						m_vSubset;
	std::vector<ID3D11ShaderResourceView*>	m_vTextureRV;
	ID3DX11EffectShaderResourceVariable*	m_pDiffuseVariable;

	virtual QPaintEngine* paintEngine() const {return NULL;}
	virtual void paintEvent(QPaintEvent* pEvent);
	virtual void resizeEvent(QResizeEvent* pEvent);
	void mouseMoveEvent(QMouseEvent* pEvent);
	void mousePressEvent(QMouseEvent* pEvent);
	void mouseReleaseEvent(QMouseEvent* pEvent);
	void wheelEvent(QWheelEvent* pEvent);
	void UpdateBoneTransformMatrix();
	HRESULT InitDevice();
	HRESULT Render();
	HRESULT BuildBuffer(const GeometryGenerator::MESH_DATA &meshData);
	HRESULT ResetVertexIndiceBuffer();

	QWidget*							m_pParent;
	QTimer*								m_pTimer;
	float								m_dt;
	float								m_fTime;

	// variables for moving the camera
	QPoint								m_preLeftMousePoint;
	QPoint								m_preMidMousePoint;
	XMVECTOR							m_xmvEye;
	XMVECTOR							m_xmvAt;
	XMVECTOR							m_xmvUp;
	int									m_nButton;

	// variables for grid
	GeometryGenerator::MESH_DATA		m_meshGrid;
	ID3D11Buffer*						m_pGridVertexBuffer;
	ID3D11Buffer*						m_pGridIndicesBuffer;

	//vertex and indices
	GeometryGenerator::SIMPLE_VERTEX	m_vertices[MAX_VERTEX];
	XMFLOAT3							m_xmf3VertexNormal[MAX_NORMAL];
	XMFLOAT3							m_xmf3TexCoord[MAX_TEXCOORD];

	int									m_nVertexIndices[MAX_VERTEX_INDICE];
	int									m_nTertexNormalIndices[MAX_NORMAL];
	int									m_nTexCoordIndices[MAX_TEXCOORD_INDICE];
	
	int									m_nVerticesCounter;
	int									m_nVertexNormalCounter;
	int									m_nTexCoordCounter;

	int									m_nIndicesCounter;

	// added at 2015/9/23 for animation
	std::vector<GeometryGenerator::SKINNED_VERTEX>  m_vSkinnedVertex;
	std::vector<int>								m_vSkinnedIndices;
	int												m_nBones;
	int												m_nAnimationClips;
	std::vector<XMFLOAT4X4>							m_vBoneOffsets;
	std::vector<int>								m_vBoneParentIndex;
	AnimationClip									m_animationClip; // the only animation clip
	bool											m_bReadFinish;
	// added at 2015/9/23 for animation

	// variables for DirectX configuration
	D3D11_VIEWPORT						m_viewPort;
	DXGI_SWAP_CHAIN_DESC				m_swapChainDesc;

	ID3D11Device*						m_pd3dDevice;
	D3D_FEATURE_LEVEL					m_featureLevel;
	ID3D11DeviceContext*				m_pDeviceContext;
	ID3D11DepthStencilView*				m_pDepthStencilView;

	IDXGISwapChain*						m_pSwapChain;

	ID3D11RenderTargetView*				m_pRenderTargetView;
	ID3D11Texture2D*					m_pDepthStencilBuffer;
	ID3DX11Effect*						m_pEffect;

	//ID3DX11EffectMatrixVariable*	m_pWorldVariable;
	//ID3DX11EffectMatrixVariable*	m_pViewVariable;
	//ID3DX11EffectMatrixVariable*	m_pProjectionVariable;
	ID3DX11EffectMatrixVariable*		m_xmmWorldViewProjVariable;
	ID3DX11EffectMatrixVariable*		m_xmmBoneTransformsVariable;
	XMMATRIX							m_mWorld;
	XMMATRIX							m_mView;
	XMMATRIX							m_mProjection;
	XMMATRIX							m_xmmWorldViewProj;
	std::vector<XMFLOAT4X4>				m_xmmBoneTransforms; // relative to parent bone
	std::vector<XMFLOAT4X4>				m_xmmFinalBoneTransforms; // translate to bone space then to root space
	ID3DX11EffectTechnique*				m_pTechnique;
	ID3DX11EffectTechnique*				m_pSkinnedTechnique; // .m3d render technique
	ID3D11InputLayout*					m_pVertexLayout;
	ID3D11InputLayout*					m_pSkinnedVertexLayout; // .m3d vertex layout
	ID3D11Buffer*						m_pVertexBuffer;
	ID3D11Buffer*						m_pIndexBuffer;
	ID3D11Buffer*						m_pSkinnedVertexBuffer; // .m3d vertex buffer
	ID3D11Buffer*						m_pSkinnedIndexBuffer; // .m3d indices buffer

	ID3D11RasterizerState*				m_rsWireFrame;
	ID3D11RasterizerState*				m_rsSolid;

	ID3DX11EffectScalarVariable*        m_pElapsedTime; // added at 2015/12/16 for moving
	ID3DX11EffectMatrixVariable*		m_xmmRoleWorldViewProjVariable;
	XMMATRIX							m_xmmRoleWorldViewProj;
	XMMATRIX							m_mRoleWorld;
	float								m_fDistance;
};

#endif // D3DWIDGET_H
