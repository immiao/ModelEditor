///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : modeleditor.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-7-30 15:00:00
// Comment  : Implementation of DirectX 11 Widget
//
///////////////////////////////////////////////////////////////

#include "d3dwidget.h"

D3DWidget::D3DWidget(QWidget* pParent)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	m_pParent = pParent;
	m_pd3dDevice = NULL;
	m_pSwapChain = NULL;
	m_pDepthStencilView = NULL;
	
	m_pTechnique = NULL;
	m_pVertexLayout = NULL;
	m_pSkinnedVertexLayout = NULL;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	m_pSkinnedVertexBuffer = NULL;
	m_pSkinnedIndexBuffer = NULL;
	m_pGridVertexBuffer = NULL;
	m_pGridIndicesBuffer = NULL;
	m_pEffect = NULL;
	m_pTimer = NULL;

	m_pRenderTargetView = NULL;
	m_pDepthStencilBuffer = NULL;
	m_pDepthStencilView = NULL;
	m_xmmWorldViewProjVariable = NULL;
	m_xmmBoneTransformsVariable = NULL;
	m_pElapsedTime = NULL;
	m_xmvEye = XMVectorSet(5.0f, 5.0f, 5.0f, 1.0f);
	m_xmvAt = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	m_xmvUp = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	m_nButton = 0;
	m_nVerticesCounter = 0;
	m_nVertexNormalCounter = 0;
	m_nTexCoordCounter = 0;
	m_nIndicesCounter = 0;

	m_fDistance = 0;
	m_xmmRoleWorldViewProjVariable = NULL;

	m_dt = 5;
	m_fTime = 0.0f;
	m_bReadFinish = false;

	m_vTextureRV.clear();
}

HRESULT D3DWidget::Init()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	// added at 2015/9/1 to eliminate scaling which causes sawtooth
	setFixedWidth(1006);
	setFixedHeight(697);
	// added at 2015/9/1 to eliminate scaling which causes sawtooth

	hrRetCode = InitDevice();
	KE_COM_PROCESS_ERROR(hrRetCode);

	hrRetCode = GeometryGenerator::CreateGrid(210, 210, m_meshGrid);
	KE_COM_PROCESS_ERROR(hrRetCode);
	hrRetCode = BuildBuffer(m_meshGrid);
	KE_COM_PROCESS_ERROR(hrRetCode);

	m_pTimer = new QTimer(this);
	KE_PROCESS_ERROR(m_pTimer);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(update()));
	m_pTimer->start(m_dt);
	m_pElapsedTime->SetFloat(m_dt);

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT D3DWidget::BuildBuffer(const GeometryGenerator::MESH_DATA &meshData)
{
	HRESULT hrRetCode = E_FAIL;
	HRESULT hrResult = E_FAIL;

	D3D11_BUFFER_DESC bufferDesc;
    D3D11_SUBRESOURCE_DATA InitData;

	// set Grid Vertex Buffer
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(GeometryGenerator::SIMPLE_VERTEX) * meshData.vVertices.size();
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    InitData.pSysMem = &meshData.vVertices[0];
	hrRetCode = m_pd3dDevice->CreateBuffer(&bufferDesc, &InitData, &m_pGridVertexBuffer);
    KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_pGridVertexBuffer);

	// set Grid Indices Buffer
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(int) * meshData.vIndices.size();
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    InitData.pSysMem = &meshData.vIndices[0];
    hrRetCode = m_pd3dDevice->CreateBuffer(&bufferDesc, &InitData, &m_pGridIndicesBuffer);
    KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_pGridIndicesBuffer);

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT D3DWidget::UnInit()
{
	HRESULT hrResult = E_FAIL;

	SAFE_DELETE(m_pTimer);

	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pDepthStencilBuffer);

	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pSkinnedVertexLayout);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pSkinnedVertexBuffer);
	SAFE_RELEASE(m_pSkinnedIndexBuffer);
	SAFE_RELEASE(m_pGridVertexBuffer);
	SAFE_RELEASE(m_pGridIndicesBuffer);
	SAFE_RELEASE(m_rsWireFrame);
	SAFE_RELEASE(m_rsSolid);

	for (int i = 0; i < m_vTextureRV.size(); i++)
		SAFE_RELEASE(m_vTextureRV[i]);
	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT D3DWidget::InitDevice()
{
	HRESULT				hrResult = E_FAIL;
	HRESULT				hrRetCode = E_FAIL;
	IDXGIDevice*		pDxgiDevice = NULL;
	IDXGIAdapter*		pDxgiAdapter = NULL;
	IDXGIFactory*		pDxgiFactory = NULL;
	ID3D10Blob*			pCompiledShader = NULL;
	ID3D10Blob*			pCompilationMsgs = NULL;
	ID3D11Texture2D*	pBackBuffer = NULL; 
	bool				bMsaaEnabled = true;
	UINT				createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	hrRetCode = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, NULL, NULL,
		D3D11_SDK_VERSION, &m_pd3dDevice, &m_featureLevel, &m_pDeviceContext);
	KE_COM_PROCESS_ERROR(hrRetCode);

	UINT nM4xMsaaQuality;
	hrRetCode = m_pd3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &nM4xMsaaQuality);
	KE_COM_PROCESS_ERROR(hrRetCode);
	assert(nM4xMsaaQuality > 0);

	
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width     = width();
	depthStencilDesc.Height    = height();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (bMsaaEnabled)
	{
		depthStencilDesc.SampleDesc.Count   = 4;
		depthStencilDesc.SampleDesc.Quality = nM4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count   = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}
	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;

	hrRetCode = m_pd3dDevice->CreateTexture2D(&depthStencilDesc, 0, &m_pDepthStencilBuffer);
	KE_COM_PROCESS_ERROR(hrRetCode);
	hrRetCode = m_pd3dDevice->CreateDepthStencilView(m_pDepthStencilBuffer, 0, &m_pDepthStencilView);
	KE_COM_PROCESS_ERROR(hrRetCode);

	// set rasterization state
	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_NONE;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;
	wireframeDesc.AntialiasedLineEnable = true;
	wireframeDesc.MultisampleEnable = true;

	hrRetCode = m_pd3dDevice->CreateRasterizerState(&wireframeDesc, &m_rsWireFrame);
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_rsWireFrame);

	// set rasterization state
	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	solidDesc.FrontCounterClockwise = true;
	solidDesc.DepthClipEnable = true;
	solidDesc.AntialiasedLineEnable = true;
	solidDesc.MultisampleEnable = true;

	hrRetCode = m_pd3dDevice->CreateRasterizerState(&solidDesc, &m_rsSolid);
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_rsSolid);

	ZeroMemory(&m_swapChainDesc, sizeof(m_swapChainDesc));
    m_swapChainDesc.BufferCount = 1;
	m_swapChainDesc.BufferDesc.Width = width();
    m_swapChainDesc.BufferDesc.Height = height();	
    m_swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	m_swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    m_swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    m_swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    m_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    m_swapChainDesc.OutputWindow = (HWND)winId();

	if (bMsaaEnabled)
	{
		m_swapChainDesc.SampleDesc.Count = 4;
		m_swapChainDesc.SampleDesc.Quality = nM4xMsaaQuality - 1;
	}
	else
	{
		m_swapChainDesc.SampleDesc.Count = 1;
		m_swapChainDesc.SampleDesc.Quality = 0;
	}
	//qDebug() << "Quality Level:" << nM4xMsaaQuality;

    m_swapChainDesc.Windowed = TRUE;
	m_swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	m_swapChainDesc.Flags = 0;

	hrRetCode = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDxgiDevice);
	KE_COM_PROCESS_ERROR(hrRetCode);

	hrRetCode = pDxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pDxgiAdapter);
	KE_COM_PROCESS_ERROR(hrRetCode);
	
	hrRetCode = pDxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pDxgiFactory);
	KE_COM_PROCESS_ERROR(hrRetCode);

	hrRetCode = pDxgiFactory->CreateSwapChain(m_pd3dDevice, &m_swapChainDesc, &m_pSwapChain);
	KE_COM_PROCESS_ERROR(hrRetCode);

	hrRetCode = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(pBackBuffer);

	hrRetCode = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_pRenderTargetView);

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	m_viewPort.Width = width();
    m_viewPort.Height = height();
    m_viewPort.MinDepth = 0.0f;
    m_viewPort.MaxDepth = 1.0f;
    m_viewPort.TopLeftX = 0;
    m_viewPort.TopLeftY = 0;
    m_pDeviceContext->RSSetViewports(1, &m_viewPort);
	DWORD dwShaderFlags = 0; 
//D3D10_SHADER_ENABLE_STRICTNESS;
//#if defined(DEBUG) || defined(_DEBUG)
//	dwShaderFlags |= D3D10_SHADER_DEBUG;
//	dwShaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
//#endif
	hrRetCode = D3DX11CompileFromFile(L"modeleditor.fx", NULL, NULL, NULL, "fx_5_0", dwShaderFlags, 0, NULL, &pCompiledShader, &pCompilationMsgs, NULL);
	KE_COM_PROCESS_ERROR(hrRetCode);

	hrRetCode = D3DX11CreateEffectFromMemory(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), 0, m_pd3dDevice, &m_pEffect);
	KE_PROCESS_ERROR(m_pEffect);
	KE_COM_PROCESS_ERROR(hrRetCode);

	// get technique
	m_pTechnique = m_pEffect->GetTechniqueByName("Render");
	KE_PROCESS_ERROR(m_pTechnique);
	m_pSkinnedTechnique = m_pEffect->GetTechniqueByName("SkinnedRender");
	KE_PROCESS_ERROR(m_pSkinnedTechnique);

	m_xmmWorldViewProjVariable = m_pEffect->GetVariableByName("gWolrdViewProjMatrix")->AsMatrix();
	m_xmmRoleWorldViewProjVariable = m_pEffect->GetVariableByName("gRoleWolrdViewProjMatrix")->AsMatrix();
	m_xmmBoneTransformsVariable = m_pEffect->GetVariableByName("gBoneTransforms")->AsMatrix();
	m_pElapsedTime = m_pEffect->GetVariableByName("g_fElapsedTime")->AsScalar();
	//m_pWorldVariable = m_pEffect->GetVariableByName("WorldMatrix")->AsMatrix();
	//m_pViewVariable = m_pEffect->GetVariableByName("ViewMatrix")->AsMatrix();
	//m_pProjectionVariable = m_pEffect->GetVariableByName("ProjectionMatrix")->AsMatrix();

    //D3DXMatrixPerspectiveFovLH(&g_Projection, ( float )D3DX_PI * 0.5f, width / ( FLOAT )height, 0.1f, 100.0f);

	// Create the simple input layout(.obj && grid)
	D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT nNumElements = sizeof(layout) / sizeof(layout[0]);
    D3DX11_PASS_DESC passDesc;
    m_pTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
    hrRetCode = m_pd3dDevice->CreateInputLayout(layout, nNumElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_pVertexLayout);
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_pVertexLayout);

	// Create the skinned input layout(.m3d), added at 2015/09/23
	D3D11_INPUT_ELEMENT_DESC skinnedLayout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"WEIGHT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"BONEINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    nNumElements = sizeof(skinnedLayout) / sizeof(skinnedLayout[0]);
    m_pSkinnedTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
    hrRetCode = m_pd3dDevice->CreateInputLayout(skinnedLayout, nNumElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_pSkinnedVertexLayout);
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_pSkinnedVertexLayout);

	// Set primitive topology
    m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set something to test, added at 2015/08/07
	D3D11_DEPTH_STENCIL_DESC depthWriteOffDesc;
	ZeroMemory(&depthWriteOffDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthWriteOffDesc.DepthEnable = true;
	depthWriteOffDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthWriteOffDesc.DepthFunc = D3D11_COMPARISON_LESS;
	ID3D11DepthStencilState* DepthWriteOffDSS  = 0;
	m_pd3dDevice->CreateDepthStencilState(&depthWriteOffDesc, &DepthWriteOffDSS);
	m_pDeviceContext->OMSetDepthStencilState(DepthWriteOffDSS, 0);
	SAFE_RELEASE(DepthWriteOffDSS);
	// Set something to test, added at 2015/08/07

	hrResult = S_OK;
Exit0:
	SAFE_RELEASE(pBackBuffer);
	SAFE_RELEASE(pCompilationMsgs);
	SAFE_RELEASE(pCompiledShader);
	SAFE_RELEASE(pDxgiDevice);
	SAFE_RELEASE(pDxgiAdapter);
	SAFE_RELEASE(pDxgiFactory);
	return hrResult;
}

// Render the frame
HRESULT D3DWidget::Render()
{
	//qDebug() << "in Render: " << width();
	//qDebug() << height();
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;
	ID3DX11EffectPass* pEffectPass = NULL;
	//D3DX11_TECHNIQUE_DESC techDesc;
	UINT uStride = sizeof(GeometryGenerator::SIMPLE_VERTEX);
    UINT uOffset = 0;
    float farrayClearColor[4] = {0.8f, 0.8f, 0.8f, 1.0f};

	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, farrayClearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	// set the camera
	m_mWorld = XMMatrixIdentity();
	if (m_bReadFinish)
	{
		m_mRoleWorld = XMMatrixIdentity();
		//m_fDistance -= 0.1;
		XMMATRIX xmmRoleTranslate = XMMatrixTranslation(0, 0, m_fDistance);
		m_mRoleWorld = m_mRoleWorld * xmmRoleTranslate;
	}

    m_mView = XMMatrixLookAtLH(m_xmvEye, m_xmvAt, m_xmvUp);
	m_mProjection =XMMatrixPerspectiveFovLH((float)XM_PI * 0.5f, width() / (FLOAT)height(), 0.1f, 100000.0f);
	m_xmmWorldViewProj = m_mWorld * m_mView * m_mProjection;
	m_xmmRoleWorldViewProj = m_mRoleWorld * m_mView * m_mProjection;
	m_xmmWorldViewProjVariable->SetMatrix((float*)(&m_xmmWorldViewProj));
	m_xmmRoleWorldViewProjVariable->SetMatrix((float*)(&m_xmmRoleWorldViewProj));
	
	// removed at 2015/09/23
	//hrRetCode = m_pTechnique->GetDesc(&techDesc);
	//KE_COM_PROCESS_ERROR(hrRetCode);
	// removed at 2015/09/23

	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	pEffectPass = m_pTechnique->GetPassByIndex(0);
	KE_PROCESS_ERROR(pEffectPass);
	hrRetCode = pEffectPass->Apply(0, m_pDeviceContext);
	KE_COM_PROCESS_ERROR(hrRetCode);

	// draw grid
	m_pDeviceContext->RSSetState(m_rsWireFrame);
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pGridVertexBuffer, &uStride, &uOffset);
    m_pDeviceContext->IASetIndexBuffer(m_pGridIndicesBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_pDeviceContext->DrawIndexed(m_meshGrid.vIndices.size(), 0, 0);

	// draw .obj Object
	if (m_nIndicesCounter && m_nVerticesCounter)
	{
		qDebug() << "Draw .obj File";
		//m_pDeviceContext->RSSetState(m_rsWireFrame);
		m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &uStride, &uOffset);
		m_pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		m_pDeviceContext->DrawIndexed(m_nIndicesCounter, 0, 0);
	}
	// draw .m3d Object
	else if (m_bReadFinish && !m_vSkinnedIndices.empty() && !m_vSkinnedVertex.empty())
	{
		m_xmmBoneTransformsVariable->SetMatrixArray(reinterpret_cast<const float*>(&m_xmmFinalBoneTransforms[0]), 0, m_xmmFinalBoneTransforms.size());
		m_pDeviceContext->IASetInputLayout(m_pSkinnedVertexLayout);
		pEffectPass = m_pSkinnedTechnique->GetPassByIndex(0);
		KE_PROCESS_ERROR(pEffectPass);

		//qDebug() << "Draw .m3d File : " << m_vSkinnedIndices.size();

		UINT uSkinnedStride = sizeof(GeometryGenerator::SKINNED_VERTEX);
		m_pDeviceContext->RSSetState(m_rsSolid);
		m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pSkinnedVertexBuffer, &uSkinnedStride, &uOffset);
		m_pDeviceContext->IASetIndexBuffer(m_pSkinnedIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//m_pDeviceContext->DrawIndexed(m_vSkinnedIndices.size(), 0, 0);
		//m_pDiffuseVariable->SetResource(m_vTextureRV[0]);
		//m_pDeviceContext->DrawIndexed(m_vSubset[0].nFaceCount * 3, m_vSubset[0].nFaceStart * 3, 0);
		//m_pDiffuseVariable->SetResource(m_vTextureRV[1]);
		//m_pDeviceContext->DrawIndexed(m_vSubset[1].nFaceCount * 3, m_vSubset[1].nFaceStart * 3, 0);
		for (int i = 0; i < m_vSubset.size(); i++)
		{
			m_pDiffuseVariable->SetResource(m_vTextureRV[i]);
			hrRetCode = pEffectPass->Apply(0, m_pDeviceContext);
			KE_COM_PROCESS_ERROR(hrRetCode);
			m_pDeviceContext->DrawIndexed(m_vSubset[i].nFaceCount * 3, m_vSubset[i].nFaceStart * 3, 0);
		}
		
	}

    hrRetCode = m_pSwapChain->Present(0, 0);
	KE_COM_PROCESS_ERROR(hrRetCode);

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT D3DWidget::ResetVertexIndiceBuffer()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pSkinnedVertexBuffer);
	SAFE_RELEASE(m_pSkinnedIndexBuffer);

	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	D3D11_BUFFER_DESC bufferDesc;
    D3D11_SUBRESOURCE_DATA InitData;

	if (m_nVerticesCounter && m_nIndicesCounter)
	{
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(GeometryGenerator::SIMPLE_VERTEX) * m_nVerticesCounter;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		InitData.pSysMem = m_vertices;
		hrRetCode = m_pd3dDevice->CreateBuffer(&bufferDesc, &InitData, &m_pVertexBuffer);
		KE_COM_PROCESS_ERROR(hrRetCode);
		KE_PROCESS_ERROR(m_pVertexBuffer);
	
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(int) * m_nIndicesCounter;        // 36 vertices needed for 12 triangles in a triangle list
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		InitData.pSysMem = m_nVertexIndices;
		hrRetCode = m_pd3dDevice->CreateBuffer(&bufferDesc, &InitData, &m_pIndexBuffer);
		KE_COM_PROCESS_ERROR(hrRetCode);
		KE_PROCESS_ERROR(m_pIndexBuffer);
	}

	// .m3d buffer
	if (!m_vSkinnedVertex.empty() && !m_vSkinnedIndices.empty())
	{
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(GeometryGenerator::SKINNED_VERTEX) * m_vSkinnedVertex.size();
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		InitData.pSysMem = &m_vSkinnedVertex[0];
		hrRetCode = m_pd3dDevice->CreateBuffer(&bufferDesc, &InitData, &m_pSkinnedVertexBuffer);
		KE_COM_PROCESS_ERROR(hrRetCode);
		KE_PROCESS_ERROR(m_pSkinnedVertexBuffer);
	
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(int) * m_vSkinnedIndices.size();        // 36 vertices needed for 12 triangles in a triangle list
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		InitData.pSysMem = &m_vSkinnedIndices[0];
		hrRetCode = m_pd3dDevice->CreateBuffer(&bufferDesc, &InitData, &m_pSkinnedIndexBuffer);
		KE_COM_PROCESS_ERROR(hrRetCode);
		KE_PROCESS_ERROR(m_pSkinnedIndexBuffer);
	}

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT D3DWidget::ReadFromM3dFile(char* pcFileName)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	for (int i = 0; i < m_vTextureRV.size(); i++)
		SAFE_RELEASE(m_vTextureRV[i]);

	FILE* pFile = fopen(pcFileName, "r");
	char cStr[100];
	char ignore[100];
	KE_PROCESS_ERROR(pFile);
	int nNumSkinnedVertex;
	int nNumSkinnedIndices;
	int nNumMaterial;
	// header
	fscanf(pFile, "%s", ignore);
	fscanf(pFile, "%s %d", ignore, &nNumMaterial);
	fscanf(pFile, "%s %d", ignore, &nNumSkinnedVertex);
	fscanf(pFile, "%s %d", ignore, &nNumSkinnedIndices); // the number of triangles
	m_vSkinnedVertex.resize(nNumSkinnedVertex);
	m_vSkinnedIndices.resize(nNumSkinnedIndices * 3);

	fscanf(pFile, "%s %d", ignore, &m_nBones);
	fscanf(pFile, "%s %d", ignore, &m_nAnimationClips);

	// material
	fscanf(pFile, "%s", ignore);
	m_vSubset.resize(nNumMaterial);
	for (UINT i = 0; i < nNumMaterial; i++)
	{
		fscanf(pFile, "%s %s %s %s", ignore, ignore, ignore, ignore);
		fscanf(pFile, "%s %s %s %s", ignore, ignore, ignore, ignore);
		fscanf(pFile, "%s %s %s %s", ignore, ignore, ignore, ignore);
		fscanf(pFile, "%s %s", ignore, ignore);
		fscanf(pFile, "%s %s %s %s", ignore, ignore, ignore, ignore);
		fscanf(pFile, "%s %s", ignore, ignore);
		fscanf(pFile, "%s %s", ignore, ignore);
		fwscanf(pFile, L"%s %s", ignore, m_vSubset[i].cDiffuseTexPath);
		fscanf(pFile, "%s %s", ignore, ignore);
	}

	// subset
	fscanf(pFile, "%s", ignore);
	for (UINT i = 0; i < nNumMaterial; i++)
	{
		fscanf(pFile, "%s %s", ignore, ignore);
		fscanf(pFile, "%s %s", ignore, ignore);
		fscanf(pFile, "%s %s", ignore, ignore);
		fscanf(pFile, "%s %d", ignore, &m_vSubset[i].nFaceStart);
		fscanf(pFile, "%s %d", ignore, &m_vSubset[i].nFaceCount);
	}

	// vertex
	fscanf(pFile, "%s", ignore);
	for (UINT i = 0; i < nNumSkinnedVertex; i++)
	{
		fscanf(pFile, "%s %f %f %f", ignore, &m_vSkinnedVertex[i].xmf3Pos.x, &m_vSkinnedVertex[i].xmf3Pos.y, &m_vSkinnedVertex[i].xmf3Pos.z);
		//m_vSkinnedVertex[i].xmf3Pos.x += 50;
		//m_vSkinnedVertex[i].xmf3Pos.y += 50;
		//m_vSkinnedVertex[i].xmf3Pos.z += 50;
		fscanf(pFile, "%s %s %s %s %s", ignore, ignore, ignore, ignore, ignore);
		fscanf(pFile, "%s %s %s %s", ignore, ignore, ignore, ignore);
		fscanf(pFile, "%s %f %f", ignore, &m_vSkinnedVertex[i].xmf2Tex.x, &m_vSkinnedVertex[i].xmf2Tex.y);
		fscanf(pFile, "%s %f %f %f %s", ignore, &m_vSkinnedVertex[i].xmf3Weight.x, &m_vSkinnedVertex[i].xmf3Weight.y, &m_vSkinnedVertex[i].xmf3Weight.z, ignore);
		fscanf(pFile, "%s %d %d %d %d", ignore, &m_vSkinnedVertex[i].uaBoundIndices[0], &m_vSkinnedVertex[i].uaBoundIndices[1], 
			&m_vSkinnedVertex[i].uaBoundIndices[2], &m_vSkinnedVertex[i].uaBoundIndices[3]);
		// added at 2015/12/16 for role animation
		//m_vSkinnedVertex[i].xmf3Weight.z += 50;
		// added at 2015/12/16 for role animation
	}

	// indices
	fscanf(pFile, "%s", ignore);
	for (UINT i = 0; i < nNumSkinnedIndices; i++)
	{
		int offset = i * 3;
		fscanf(pFile, "%d %d %d", &m_vSkinnedIndices[offset], &m_vSkinnedIndices[offset + 1], &m_vSkinnedIndices[offset + 2]);
	}

	// bone offset
	m_vBoneOffsets.resize(m_nBones);
	fscanf(pFile, "%s", ignore);
	for (UINT i = 0; i < m_nBones; i++)
	{
		fscanf(pFile, "%s", ignore);
		fscanf(pFile, "%f %f %f %f", &m_vBoneOffsets[i](0,0), &m_vBoneOffsets[i](0,1), &m_vBoneOffsets[i](0,2), &m_vBoneOffsets[i](0,3));
		fscanf(pFile, "%f %f %f %f", &m_vBoneOffsets[i](1,0), &m_vBoneOffsets[i](1,1), &m_vBoneOffsets[i](1,2), &m_vBoneOffsets[i](1,3));
		fscanf(pFile, "%f %f %f %f", &m_vBoneOffsets[i](2,0), &m_vBoneOffsets[i](2,1), &m_vBoneOffsets[i](2,2), &m_vBoneOffsets[i](2,3));
		fscanf(pFile, "%f %f %f %f", &m_vBoneOffsets[i](3,0), &m_vBoneOffsets[i](3,1), &m_vBoneOffsets[i](3,2), &m_vBoneOffsets[i](3,3));
	}

	// bone hierarchy
	m_vBoneParentIndex.resize(m_nBones);
	fscanf(pFile, "%s", ignore);
	for (UINT i = 0; i < m_nBones; i++)
	{
		fscanf(pFile, "%s %d", ignore, &m_vBoneParentIndex[i]);
	}

	// animation clips
	fscanf(pFile, "%s", ignore);
	for (UINT i = 0; i < m_nAnimationClips; i++)
	{
		fscanf(pFile, "%s %s", ignore, ignore);
		fscanf(pFile, "%s", ignore);

		m_animationClip.BoneAnimations.resize(m_nBones);

		// read bone key frames
		for (UINT boneIndex = 0; boneIndex < m_nBones; boneIndex++)
		{
			UINT nKeyFrames = 0;
			fscanf(pFile, "%s %s %d", ignore, ignore, &nKeyFrames);
			fscanf(pFile, "%s", ignore); // {

			m_animationClip.BoneAnimations[boneIndex].Keyframes.resize(nKeyFrames);
			for (UINT j = 0; j < nKeyFrames; j++)
			{
				float t    = 0.0f;
				XMFLOAT3 p(0.0f, 0.0f, 0.0f);
				XMFLOAT3 s(1.0f, 1.0f, 1.0f);
				XMFLOAT4 q(0.0f, 0.0f, 0.0f, 1.0f);
				fscanf(pFile, "%s %f", ignore, &t);
				fscanf(pFile, "%s %f %f %f", ignore, &p.x, &p.y, &p.z);
				fscanf(pFile, "%s %f %f %f", ignore, &s.x, &s.y, &s.z);
				fscanf(pFile, "%s %f %f %f %f", ignore, &q.x, &q.y, &q.z, &q.w);

				m_animationClip.BoneAnimations[boneIndex].Keyframes[j].TimePos      = t;
				m_animationClip.BoneAnimations[boneIndex].Keyframes[j].Translation  = p;
				m_animationClip.BoneAnimations[boneIndex].Keyframes[j].Scale        = s;
				m_animationClip.BoneAnimations[boneIndex].Keyframes[j].RotationQuat = q;
			}

			fscanf(pFile, "%s", ignore); // }
		}
	}
	m_animationClip.GetEndTime();
	m_xmmBoneTransforms.resize(m_nBones);
	m_xmmFinalBoneTransforms.resize(m_nBones);
	hrRetCode = ResetVertexIndiceBuffer();
	KE_COM_PROCESS_ERROR(hrRetCode);

	m_bReadFinish = true;

	int size = m_vSubset.size();
	m_vTextureRV.resize(size);
	m_pDiffuseVariable = m_pEffect->GetVariableByName( "txDiffuse" )->AsShaderResource();
	for (int i = 0; i < size; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(m_pd3dDevice, m_vSubset[i].cDiffuseTexPath, NULL, NULL, &m_vTextureRV[i], NULL );
		//D3DX11CreateShaderResourceViewFromFile(m_pd3dDevice, "jacket_diff.dds", NULL, NULL, &m_vTextureRV[i], NULL );
	}

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT D3DWidget::ReadVertexIndiceFromObjFile(char* pcFileName)
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	FILE* pFile = fopen(pcFileName, "r");
	char cStr[100];
	KE_PROCESS_ERROR(pFile);

	while (fscanf(pFile, "%s", cStr) != EOF)
	{
		if (!strcmp(cStr, "#"))
		{
			fgets(cStr, sizeof(cStr), pFile);
			continue;
		}
		else if (!strcmp(cStr, "v"))
		{
			fscanf(pFile, "%f", &m_vertices[m_nVerticesCounter].xmf3Pos.x);
			fscanf(pFile, "%f", &m_vertices[m_nVerticesCounter].xmf3Pos.y);
			fscanf(pFile, "%f", &m_vertices[m_nVerticesCounter].xmf3Pos.z);
			m_vertices[m_nVerticesCounter].xmf4Color.x = 0.0f;
			m_vertices[m_nVerticesCounter].xmf4Color.y = 0.5f;
			m_vertices[m_nVerticesCounter].xmf4Color.z = 0.0f;
			m_vertices[m_nVerticesCounter].xmf4Color.w = 1.0f;
			m_nVerticesCounter++;
		}
		else if (!strcmp(cStr, "f"))
		{
			fscanf(pFile, "%d/%d/%d", &m_nVertexIndices[m_nIndicesCounter], &m_nTexCoordIndices[m_nIndicesCounter], &m_nTertexNormalIndices[m_nIndicesCounter]);
			fscanf(pFile, "%d/%d/%d", &m_nVertexIndices[m_nIndicesCounter + 1], &m_nTexCoordIndices[m_nIndicesCounter + 1], &m_nTertexNormalIndices[m_nIndicesCounter + 1]);
			fscanf(pFile, "%d/%d/%d", &m_nVertexIndices[m_nIndicesCounter + 2], &m_nTexCoordIndices[m_nIndicesCounter + 2], &m_nTertexNormalIndices[m_nIndicesCounter + 2]);

			m_nVertexIndices[m_nIndicesCounter]--;
			m_nVertexIndices[m_nIndicesCounter + 1]--;
			m_nVertexIndices[m_nIndicesCounter + 2]--;

			m_nTexCoordIndices[m_nIndicesCounter]--;
			m_nTexCoordIndices[m_nIndicesCounter + 1]--;
			m_nTexCoordIndices[m_nIndicesCounter + 2]--;

			m_nTertexNormalIndices[m_nIndicesCounter]--;
			m_nTertexNormalIndices[m_nIndicesCounter + 1]--;
			m_nTertexNormalIndices[m_nIndicesCounter + 2]--;

			m_nIndicesCounter += 3;
		}
		else if (!strcmp(cStr, "vn"))
		{
			fgets(cStr, sizeof(cStr), pFile);
			continue;
		}
		else if (!strcmp(cStr, "vt"))
		{
			fgets(cStr, sizeof(cStr), pFile);
			continue;
		}
		else
			continue;
	}
	hrRetCode = ResetVertexIndiceBuffer();
	KE_COM_PROCESS_ERROR(hrRetCode);

	hrResult = S_OK;
Exit0:
	fclose(pFile);
	return hrResult;
}

D3DWidget::~D3DWidget()
{
	qDebug() << "D3D Destruction";
	//CleanupDevice();
}

void D3DWidget::paintEvent(QPaintEvent* pEvent)
{
	//ReSetVertexIndiceBuffer();
	UpdateBoneTransformMatrix();
	Render();
}

void D3DWidget::resizeEvent(QResizeEvent* pEvent)
{
	//ReSetVertexIndiceBuffer();
	UpdateBoneTransformMatrix();
	Render();
}

void D3DWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
	if ((m_nButton & Qt::LeftButton) != 0)
	{
		FLOAT fDeltaY = pEvent->y() - m_preLeftMousePoint.y();
		FLOAT fDeltaX = pEvent->x() - m_preLeftMousePoint.x();
		XMVECTOR xmvEyeToAt = m_xmvAt - m_xmvEye;
		XMVECTOR xmvAxis = XMVector3Cross(xmvEyeToAt, m_xmvUp);

		FLOAT fMovingRatio = 0.01;
		FLOAT fMovingSpeedX = fDeltaX * fMovingRatio;
		FLOAT fMovingSpeedY = fDeltaY * fMovingRatio;

		XMMATRIX xmmRotateVertical = XMMatrixRotationAxis(xmvAxis, -fMovingSpeedY);
		XMMATRIX xmmRotateHorizon = XMMatrixRotationAxis(m_xmvUp, fMovingSpeedX);

		m_xmvEye = XMVector4Transform(m_xmvEye, xmmRotateHorizon * xmmRotateVertical);
	
		m_preLeftMousePoint = pEvent->pos();
		//qDebug() << "Doing Left Button";
	}

	if ((m_nButton & Qt::MiddleButton) != 0)
	{
		FLOAT fDeltaY = pEvent->y() - m_preMidMousePoint.y();
		FLOAT fDeltaX = pEvent->x() - m_preMidMousePoint.x();

		XMVECTOR xmvEyeToAt = m_xmvAt - m_xmvEye;
		XMVECTOR xmvTranslateX = XMVector3Cross(xmvEyeToAt, m_xmvUp);
		XMVECTOR xmvTranslateY = XMVector3Cross(xmvEyeToAt, xmvTranslateX);
		xmvTranslateX = XMVector3Normalize(xmvTranslateX);
		xmvTranslateY = XMVector3Normalize(xmvTranslateY);

		xmvEyeToAt = XMVector3Length(xmvEyeToAt);
		XMVECTOR xmvMovingVectorY = xmvEyeToAt * xmvTranslateY;
		XMVECTOR xmvMovingVectorX = xmvEyeToAt * xmvTranslateX;
		
		FLOAT fMovingRatio = 0.0005;
		FLOAT fMovingSpeedX = fDeltaX * fMovingRatio;
		FLOAT fMovingSpeedY = fDeltaY * fMovingRatio;

		XMMATRIX xmmTranslateHorizon = XMMatrixTranslation(xmvMovingVectorX.m128_f32[0] * fMovingSpeedX, 
			xmvMovingVectorX.m128_f32[1] * fMovingSpeedX, xmvMovingVectorX.m128_f32[2] * fMovingSpeedX);
		XMMATRIX xmmTranslateVertical = XMMatrixTranslation(xmvMovingVectorY.m128_f32[0] * fMovingSpeedY, 
			xmvMovingVectorY.m128_f32[1] * fMovingSpeedY, xmvMovingVectorY.m128_f32[2] * fMovingSpeedY);

		m_xmvEye = XMVector4Transform(m_xmvEye, xmmTranslateHorizon);
		m_xmvEye = XMVector4Transform(m_xmvEye, xmmTranslateVertical);

		m_xmvAt = XMVector4Transform(m_xmvAt, xmmTranslateHorizon);
		m_xmvAt = XMVector4Transform(m_xmvAt, xmmTranslateVertical);

		m_preMidMousePoint = pEvent->pos();
		//qDebug() << "Doing Middle Button";
	}
}	

void D3DWidget::mousePressEvent(QMouseEvent* pEvent)
{
	m_nButton = pEvent->button();
	//qDebug() << m_nButton;
	
	if ((pEvent->button() & Qt::LeftButton) != 0)
	{
		//qDebug() << "mousePressEvent: Click Left Button";
		m_preLeftMousePoint = pEvent->pos();
	}
	if ((pEvent->button() & Qt::MiddleButton) != 0)
	{
		//qDebug() << "mousePressEvent: Click Middle Button";
		m_preMidMousePoint = pEvent->pos();
	}
}

void D3DWidget::mouseReleaseEvent(QMouseEvent* pEvent)
{
	if ((pEvent->button() & Qt::LeftButton) != 0)
	{
		//qDebug() << "mouseReleaseEvent: Release Left Button";
		//m_preLeftMousePoint = pEvent->pos();
		m_nButton &= (~Qt::LeftButton);
	}
	if ((pEvent->button() & Qt::MiddleButton) != 0)
	{
		//qDebug() << "mouseReleaseEvent: Release Middle Button";
		//m_preMidMousePoint = pEvent->pos();
		m_nButton &= (~Qt::MiddleButton);
	}
}

void D3DWidget::wheelEvent(QWheelEvent* pEvent)
{
	//qDebug() << pEvent->angleDelta();
	if (pEvent->angleDelta().y() < 0)
	{
		FLOAT fRatio = 0.1f;
		XMVECTOR xmvTranslateVector = m_xmvAt - m_xmvEye;
		XMMATRIX xmmTranslateMatrix = XMMatrixTranslation(-xmvTranslateVector.m128_f32[0] * fRatio, -xmvTranslateVector.m128_f32[1] * fRatio, 
			-xmvTranslateVector.m128_f32[2] * fRatio);
		m_xmvEye = XMVector4Transform(m_xmvEye, xmmTranslateMatrix);
	}
	else if (pEvent->angleDelta().y() > 0)
	{
		FLOAT fRatio = 0.1f;
		XMVECTOR xmvTranslateVector = m_xmvAt - m_xmvEye;
		XMMATRIX xmmTranslateMatrix = XMMatrixTranslation(xmvTranslateVector.m128_f32[0] * fRatio, xmvTranslateVector.m128_f32[1] * fRatio, 
			xmvTranslateVector.m128_f32[2] * fRatio);
		m_xmvEye = XMVector4Transform(m_xmvEye, xmmTranslateMatrix);
	}
}

void D3DWidget::ClearVertexIndiceCounter()
{
	m_nVerticesCounter = 0;
	m_nIndicesCounter = 0;
	m_vSkinnedIndices.clear();
	m_vSkinnedVertex.clear();
}

void D3DWidget::UpdateBoneTransformMatrix()
{
	if (!m_bReadFinish)
		return;
	qDebug() << "Updating : " << m_fTime;
	m_fTime += m_dt / 1000.0;
	// Interpolate
	for (UINT i = 0; i < m_animationClip.BoneAnimations.size(); i++)
	{
		std::vector<Keyframe> &rKeyframes = m_animationClip.BoneAnimations[i].Keyframes;

		if( m_fTime <= rKeyframes.front().TimePos )
		{
			XMVECTOR S = XMLoadFloat3(&rKeyframes.front().Scale);
			XMVECTOR P = XMLoadFloat3(&rKeyframes.front().Translation);
			XMVECTOR Q = XMLoadFloat4(&rKeyframes.front().RotationQuat);

			XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
			//m_xmmBoneTransforms[i] = XMMatrixAffineTransformation(S, zero, Q, P);
			XMStoreFloat4x4(&m_xmmBoneTransforms[i], XMMatrixAffineTransformation(S, zero, Q, P));
		}
		else if( m_fTime >= rKeyframes.back().TimePos )
		{
			XMVECTOR S = XMLoadFloat3(&rKeyframes.back().Scale);
			XMVECTOR P = XMLoadFloat3(&rKeyframes.back().Translation);
			XMVECTOR Q = XMLoadFloat4(&rKeyframes.back().RotationQuat);

			XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
			//m_xmmBoneTransforms[i] = XMMatrixAffineTransformation(S, zero, Q, P);
			XMStoreFloat4x4(&m_xmmBoneTransforms[i], XMMatrixAffineTransformation(S, zero, Q, P));
		}
		else
		{
			// pos in .m3d files are the position relative to its parent
			for(UINT j = 0; j < rKeyframes.size() - 1; ++j)
			{
				if( m_fTime >= rKeyframes[j].TimePos && m_fTime <= rKeyframes[j+1].TimePos )
				{
					float lerpPercent = (m_fTime - rKeyframes[j].TimePos) / (rKeyframes[j+1].TimePos - rKeyframes[j].TimePos);

					XMVECTOR s0 = XMLoadFloat3(&rKeyframes[j].Scale);
					XMVECTOR s1 = XMLoadFloat3(&rKeyframes[j+1].Scale);

					XMVECTOR p0 = XMLoadFloat3(&rKeyframes[j].Translation);
					XMVECTOR p1 = XMLoadFloat3(&rKeyframes[j+1].Translation);

					XMVECTOR q0 = XMLoadFloat4(&rKeyframes[j].RotationQuat);
					XMVECTOR q1 = XMLoadFloat4(&rKeyframes[j+1].RotationQuat);

					XMVECTOR S = XMVectorLerp(s0, s1, lerpPercent);
					XMVECTOR P = XMVectorLerp(p0, p1, lerpPercent);
					XMVECTOR Q = XMQuaternionSlerp(q0, q1, lerpPercent);

					XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
					//m_xmmBoneTransforms[i] = XMMatrixAffineTransformation(S, zero, Q, P);
					
					XMStoreFloat4x4(&m_xmmBoneTransforms[i], XMMatrixAffineTransformation(S, zero, Q, P));
					break;
				}
			}
		}
	}
	
	// calculate final bone transformation
	std::vector<XMFLOAT4X4> toRootTransforms;
	toRootTransforms.resize(m_nBones);
	toRootTransforms[0] = m_xmmBoneTransforms[0];
	//XMMATRIX t = XMMatrixMultiply(m_xmmBoneTransforms[1], toRootTransforms[0]);
	for (UINT i = 1; i < m_nBones; i++)
	{
		int nParentIndex = m_vBoneParentIndex[i];
		//toRootTransforms[i] = XMMatrixMultiply(m_xmmBoneTransforms[i], toRootTransforms[nParentIndex]);
		//m_xmmFinalBoneTransforms[i] = XMMatrixMultiply(m_vBoneOffsets[i], toRootTransforms[i]);

		XMMATRIX toParent = XMLoadFloat4x4(&m_xmmBoneTransforms[i]);
		XMMATRIX parentToRoot = XMLoadFloat4x4(&toRootTransforms[nParentIndex]);

		XMMATRIX toRoot = XMMatrixMultiply(toParent, parentToRoot);

		XMStoreFloat4x4(&toRootTransforms[i], toRoot);
	}

	for(UINT i = 0; i < m_nBones; ++i)
	{
		XMMATRIX offset = XMLoadFloat4x4(&m_vBoneOffsets[i]);
		XMMATRIX toRoot = XMLoadFloat4x4(&toRootTransforms[i]);
		XMStoreFloat4x4(&m_xmmFinalBoneTransforms[i], XMMatrixMultiply(offset, toRoot));
	}

	if (m_fTime > m_animationClip.fEndTime)
		m_fTime = 0.0f;
}

void AnimationClip::GetEndTime()
{
	fEndTime = 0.0f;
	for (UINT i = 0; i < BoneAnimations.size(); i++)
	{
		float fFrameEndTime = BoneAnimations[i].Keyframes.back().TimePos;
		if (fFrameEndTime > fEndTime)
			fEndTime = fFrameEndTime;
	}
}

void D3DWidget::SetReadFinish(bool bFlag)
{
	m_bReadFinish = bFlag;
}