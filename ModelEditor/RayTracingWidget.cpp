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
	maxDepth = 1;
}

HRESULT RayTracingWidget::Init()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	XMVECTOR x1, x2, x3;
	x1.m128_f32[0] = 0.0314; x1.m128_f32[1] = 0.4314; x1.m128_f32[2] = 0.5294; x1.m128_f32[3] = 1.0;
	x2.m128_f32[0] = 0.0314; x2.m128_f32[1] = 0.4314; x2.m128_f32[2] = 0.5294; x2.m128_f32[3] = 1.0;
	checkerMaterial = new CheckerMaterial(0.25);
	phongMaterial = new PhongMaterial(x1, x2, 0.35, 0.25);
	x1.m128_f32[0] = 2.0; x1.m128_f32[1] = 2.0; x1.m128_f32[2] = 0.0; x1.m128_f32[3] = 1.0;
	sphere1 = new Sphere(x1, 1, phongMaterial);
	x1.m128_f32[0] = -1.0; x1.m128_f32[1] = 2.0; x1.m128_f32[2] = 0.0; x1.m128_f32[3] = 1.0;
	sphere2 = new Sphere(x1, 1, phongMaterial);
	x1.m128_f32[0] = 0.0; x1.m128_f32[1] = 1.0; x1.m128_f32[2] = -5.0; x1.m128_f32[3] = 1.0;
	x2.m128_f32[0] = 0.0; x2.m128_f32[1] = 0.0; x2.m128_f32[2] = 1.0; x2.m128_f32[3] = 1.0;
	x3.m128_f32[0] = 0.0; x3.m128_f32[1] = 1.0; x3.m128_f32[2] = 0.0; x3.m128_f32[3] = 1.0;
	camera = new Camera(x1, x2, x3, 60);
	x1.m128_f32[0] = 0.0; x1.m128_f32[1] = 0.0; x1.m128_f32[2] = 0.0; x1.m128_f32[3] = 1.0;
	x2.m128_f32[0] = 0.0; x2.m128_f32[1] = 1.0; x2.m128_f32[2] = 0.0; x2.m128_f32[3] = 1.0;
	plane = new Plane(x1, x2, 0, checkerMaterial);

	geometry[0] = sphere1;
	geometry[1] = sphere2;
	geometry[2] = plane;

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


	for (int i = 0; i < m_width; i++)
	{
		float x = (i - 300) / 300.0;
		for (int j = 0; j < m_height; j++)
		{
			float y = (j - 300) / 300.0;
			
			float tanResult = tanf(camera->FOV * 0.5 / 180 * XM_PI);
			XMVECTOR right = camera->right * (x * tanResult); 
			XMVECTOR up = camera->up * (y * tanResult);
			Ray ray(camera->pos, camera->front + right + up);

			Color color = EmitRay(ray, 0);
			//for (int k = 0; k < 3; k++)
			//{
			//	IntersectResult result;
			//	if (geometry[k]->IntersectPoint(ray, result))
			//	{
			//		Ray reflectRay(result.pos, ray.dir - result.normal * 2 * (XMVector3Dot(ray.dir, result.normal).m128_f32[0]));
			//		color = EmitRay(ray);
			//	}
			//	else
			//		color.color.m128_f32[0] = color.color.m128_f32[1] = color.color.m128_f32[2] = 0.0f;
			//}
			QPainter painter(this);
			QColor qColor(color.color.m128_f32[0] * 255, color.color.m128_f32[1] * 255, color.color.m128_f32[2] * 255);
			painter.setPen(qColor);
			QPoint point(i, j);
			painter.drawPoint(point);
		}
	}
	
}

Color RayTracingWidget::EmitRay(Ray& ray, int depth)
{
	for (int i = 0; i < 3; i++)
	{
		IntersectResult result;
		
		if (geometry[i]->IntersectPoint(ray, result))
		{
			Color color = geometry[i]->pMaterial->sample(ray, result.pos, result.normal);
			float reflectiveness = geometry[i]->pMaterial->reflectiveness;
			Ray reflectRay(result.pos, ray.dir - result.normal * 2 * (XMVector3Dot(ray.dir, result.normal).m128_f32[0]));
			if (depth + 1 <= maxDepth)
				return color * (1 - reflectiveness) + EmitRay(reflectRay, depth + 1) * reflectiveness;
			else
				return color;
		}
		else
		{
			Color black;
			black.color.m128_f32[0] = black.color.m128_f32[1] = black.color.m128_f32[2] = 0.0f;
			return black;
		}

	}
}
