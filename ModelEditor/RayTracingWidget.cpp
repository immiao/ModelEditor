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
	maxDepth = 2;
	XMVECTOR x1;
	x1.m128_f32[0] = 0.0f; x1.m128_f32[1] = 0.0f; x1.m128_f32[2] = 0.0f; x1.m128_f32[3] = 1.0;
	BLACK.color = x1;
	x1.m128_f32[0] = 1.0f; x1.m128_f32[1] = 1.0f; x1.m128_f32[2] = 1.0f; x1.m128_f32[3] = 1.0;
	WHITE.color = x1;
	srand(time(NULL));
}

HRESULT RayTracingWidget::Init()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	XMVECTOR x1, x2, x3;
	checkerMaterial = new CheckerMaterial(0.1, 0.5);
	x1.m128_f32[0] = 1; x1.m128_f32[1] = 0; x1.m128_f32[2] = 0.4; x1.m128_f32[3] = 1.0;
	x2.m128_f32[0] = 1; x2.m128_f32[1] = 1; x2.m128_f32[2] = 1; x2.m128_f32[3] = 1.0;
	phongMaterial1 = new PhongMaterial(x1, x2, 16, 0.25);
	x1.m128_f32[0] = 0; x1.m128_f32[1] = 0; x1.m128_f32[2] = 1; x1.m128_f32[3] = 1.0;
	x2.m128_f32[0] = 1; x2.m128_f32[1] = 1; x2.m128_f32[2] = 1; x2.m128_f32[3] = 1.0;
	phongMaterial2 = new PhongMaterial(x1, x2, 16, 0.25);
	x1.m128_f32[0] = -10; x1.m128_f32[1] = 10; x1.m128_f32[2] = 10; x1.m128_f32[3] = 1.0;
	sphere1 = new Sphere(x1, 10, phongMaterial2);
	x1.m128_f32[0] = 10; x1.m128_f32[1] = 10; x1.m128_f32[2] = 10; x1.m128_f32[3] = 1.0;
	sphere2 = new Sphere(x1, 10, phongMaterial1);
	x1.m128_f32[0] = 0; x1.m128_f32[1] = 5; x1.m128_f32[2] = -15; x1.m128_f32[3] = 1.0;
	//x1.m128_f32[0] = 3.0; x1.m128_f32[1] = 2.0; x1.m128_f32[2] = -0.5; x1.m128_f32[3] = 1.0;
	x2.m128_f32[0] = 0.0; x2.m128_f32[1] = 0.0; x2.m128_f32[2] = 1.0; x2.m128_f32[3] = 1.0;
	x3.m128_f32[0] = 0.0; x3.m128_f32[1] = 1.0; x3.m128_f32[2] = 0.0; x3.m128_f32[3] = 1.0;
	camera = new Camera(x1, x2, x3, 90);
	x1.m128_f32[0] = 0.0; x1.m128_f32[1] = 0.0; x1.m128_f32[2] = 0.0; x1.m128_f32[3] = 1.0;
	x2.m128_f32[0] = 0.0; x2.m128_f32[1] = 1.0; x2.m128_f32[2] = 0.0; x2.m128_f32[3] = 1.0;
	plane = new Plane(x1, x2, 0, checkerMaterial);

	// for debug
	x1.m128_f32[0] = 0.0; x1.m128_f32[1] = 0.0; x1.m128_f32[2] = 0.0; x1.m128_f32[3] = 1.0;
	test = new Sphere(x1, 1, phongMaterial1);
	x1.m128_f32[0] = 0.0; x1.m128_f32[1] = 1.0; x1.m128_f32[2] = -5.0; x1.m128_f32[3] = 1.0;
	x2.m128_f32[0] = 0.0; x2.m128_f32[1] = 0.0; x2.m128_f32[2] = 1.0; x2.m128_f32[3] = 1.0;
	x3.m128_f32[0] = 0.0; x3.m128_f32[1] = 1.0; x3.m128_f32[2] = 0.0; x3.m128_f32[3] = 1.0;
	testCamera = new Camera(x1, x2, x3, 60);

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
	qDebug() << "In Paint Event";
	
	for (int i = 0; i < m_width; i++)
	{
		float x = (i - 300) / 300.0;
		for (int j = 0; j < m_height; j++)
		{
			float y = -(j - 300) / 300.0;
			
			float tanResult = tanf(camera->FOV * 0.5 / 180 * XM_PI); // half of the width/height, s
			XMVECTOR right = camera->right * (x * tanResult); 
			XMVECTOR up = camera->up * (y * tanResult);
			Ray ray(camera->pos, XMVector3Normalize(camera->front + right + up));

			Color color = EmitRay(ray, 0);
			color.SetValid();
			QPainter painter(this);
			QColor qColor(color.color.m128_f32[0] * 255, color.color.m128_f32[1] * 255, color.color.m128_f32[2] * 255);
			painter.setPen(qColor);
			QPoint point(i, j);
			painter.drawPoint(point);
		}
	}
	//for (int i = 0; i < m_width; i++)
	//{
	//	float x = (i - 300) / 300.0;
	//	for (int j = 0; j < m_height; j++)
	//	{
	//		float y = -(j - 300) / 300.0;
	//		
	//		float tanResult = tanf(testCamera->FOV * 0.5 / 180 * XM_PI); // half of the width/height, s
	//		XMVECTOR right = testCamera->right * (x * tanResult); 
	//		XMVECTOR up = testCamera->up * (y * tanResult);
	//		Ray ray(testCamera->pos, XMVector3Normalize(testCamera->front + right + up));

	//		Color color = TestEmitRay(ray);
	//		QPainter painter(this);
	//		QColor qColor(color.color.m128_f32[0] * 255, color.color.m128_f32[1] * 255, color.color.m128_f32[2] * 255);
	//		painter.setPen(qColor);
	//		QPoint point(i, j);
	//		painter.drawPoint(point);
	//	}
	//}
}

Color RayTracingWidget::TestEmitRay(Ray& ray)
{
	IntersectResult result;
	if (plane->IntersectPoint(ray, result))
	{
		//qDebug() << "WHITE";
		return WHITE;
	}
	else
	{
		//qDebug() << "BLACK";
		return BLACK;
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
			
			int randomNum = rand() % 100;
			//Ray reflectRay;
			//if (randomNum < 0)
			//	reflectRay.SetRay(result.pos, randomDir);
			//else
			//	reflectRay.SetRay(result.pos, ray.dir - result.normal * 2 * (XMVector3Dot(ray.dir, result.normal).m128_f32[0]));

			Color total;
			for (int j = 0; j < 20; j++)
			{
				Ray reflectRay;
				XMVECTOR randomDir = RandomDirOnHemisphere(result.normal);
				if (randomNum < 90)
					reflectRay.SetRay(result.pos, randomDir);
				else
					reflectRay.SetRay(result.pos, ray.dir - result.normal * 2 * (XMVector3Dot(ray.dir, result.normal).m128_f32[0]));
				if (depth + 1 <= maxDepth)
					total = total + color * (1 - reflectiveness) + EmitRay(reflectRay, depth + 1) * reflectiveness;
			}
			total = total / 20.0;
			return total;
				
			//if (depth + 1 <= maxDepth)
			//	return color * (1 - reflectiveness) + EmitRay(reflectRay, depth + 1) * reflectiveness;
			//else
			//	return color;
		}
	}
	return BLACK;
}

XMVECTOR RayTracingWidget::RandomDirOnHemisphere(XMVECTOR& normal)
{
	//qDebug() << time(NULL);
	//
	float x = rand() % 101;
	float y = rand() % 101;
	float z = sqrt(10000 - x * x - y * y);
	x /= 100.0;
	y /= 100.0;
	z /= 100.0;

	XMVECTOR dir;
	dir.m128_f32[0] = x;
	dir.m128_f32[1] = y;
	dir.m128_f32[2] = z;

	float distance = XMVector3Dot(dir, normal).m128_f32[0]; // possible to be negative
	if (distance < 0)
	{
		dir = dir - normal * (2 * distance);
	}
	//XMVector3Normalize(dir);
	//qDebug() << dir.m128_f32[0] << " " << dir.m128_f32[1] << " " << dir.m128_f32[2];
	return dir;
}
