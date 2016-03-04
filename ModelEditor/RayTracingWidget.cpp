///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : RayTracingWidget.cpp
// Creator  : Miao Kaixiang
// Date     : 2016-03-03 16:00
// Comment  : Implementation of Ray Tracing Demo
//
///////////////////////////////////////////////////////////////

#include "RayTracingWidget.h"

RayTracingWidget::RayTracingWidget(QWidget* pParent):QWidget(pParent)
{

}

HRESULT RayTracingWidget::Init()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	setAutoFillBackground(true);
	setFixedWidth(600);
	setFixedHeight(600);
	m_width = m_height = 600;

	QPalette qPalette = palette();
	QColor qColor(120, 120, 120);
	qPalette.setColor(QPalette::Window, qColor);
	setPalette(qPalette);

	hrResult = S_OK;
Exit0:
	return hrResult;
}

HRESULT RayTracingWidget::UnInit()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	hrResult = S_OK;
Exit0:
	return hrResult;
}

void RayTracingWidget::paintEvent(QPaintEvent* pEvent)
{
	//QPainter painter(this);
	//QColor color(255, 0, 0);
	//painter.setPen(color);
	//QPoint point(20, 20);
	//QPointF fPoint1(10, 10);
	//QPointF fPoint2(20, 20);
	//painter.drawLine(fPoint1, fPoint2);

	/*
	****** Scene ******
	Sphere1: 
		pos = (2, 2, 0);
		radius = 1;
	Sphere2:
		pos = (-1, 2, 0);
		radius = 1;
	Camera:
		pos = (0, 1, -5);
		front = (0, 0, 1);
		up = (0, 1, 0);[camera but not world]
		FOV = 90;
	*/
	XMVECTOR x1, x2, x3;
	x1.m128_f32[0] = 2.0; x1.m128_f32[1] = 2.0; x1.m128_f32[2] = 0.0; x1.m128_f32[3] = 1.0;
	Sphere sphere1(x1, 1);
	x1.m128_f32[0] = -1.0; x1.m128_f32[1] = 2.0; x1.m128_f32[2] = 0.0; x1.m128_f32[3] = 1.0;
	Sphere sphere2(x1, 1);
	x1.m128_f32[0] = 0.0; x1.m128_f32[1] = 1.0; x1.m128_f32[2] = -5.0; x1.m128_f32[3] = 1.0;
	x2.m128_f32[0] = 0.0; x2.m128_f32[1] = 0.0; x2.m128_f32[2] = 1.0; x2.m128_f32[3] = 1.0;
	x3.m128_f32[0] = 0.0; x3.m128_f32[1] = 1.0; x3.m128_f32[2] = 0.0; x3.m128_f32[3] = 1.0;
	Camera camera(x1, x2, x3, 60);

	for (int i = 0; i < m_width; i++)
	{
		float x = (i - 300) / 300.0;
		for (int j = 0; j < m_height; j++)
		{
			float y = (j - 300) / 300.0;
			
			float tanResult = tanf(camera.FOV * 0.5 / 180 * XM_PI);
			XMVECTOR right = camera.right * (x * tanResult); 
			XMVECTOR up = camera.up * (y * tanResult);
			Ray ray(camera.pos, camera.front + right + up);
			EmitRay(ray);
		}
	}
}

XMVECTOR RayTracingWidget::EmitRay(Ray& ray)
{
	XMVECTOR x1;
	x1.m128_f32[0] = 2.0; x1.m128_f32[1] = 2.0; x1.m128_f32[2] = 0.0; x1.m128_f32[3] = 1.0;
	return x1;
}
