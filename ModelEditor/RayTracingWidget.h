///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : RayTracingWidget.h
// Creator  : Miao Kaixiang
// Date     : 2016-03-03 16:00
// Comment  : Declaration of Ray Tracing Demo
//
///////////////////////////////////////////////////////////////

#ifndef RAYTRACINGWIDGET_H
#define RAYTRACINGWIDGET_H

#include <QWidget>
#include "KEPublic2.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include <QPalette>
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <QColor>
#include <math.h>

class Camera
{
public:
	XMVECTOR pos;
	XMVECTOR front;
	XMVECTOR up;
	XMVECTOR right;
	float FOV;
	Camera(XMVECTOR tPos, XMVECTOR tFront, XMVECTOR tUp, float tFOV)
	{
		pos = tPos;
		front = tFront;
		up = tUp;
		FOV = tFOV;
		right = XMVector3Cross(front, up);
	}

};

class Color
{
public:
	float r, g, b;
};

class Ray
{
public:
	XMVECTOR pos;
	XMVECTOR dir;
	Ray(XMVECTOR tPos, XMVECTOR tDir)
	{
		pos = tPos;
		dir = tDir;
	}
};

class Sphere
{
public:
	XMVECTOR pos;
	int radius;
	Sphere(XMVECTOR tPos, int tRadius)
	{
		pos = tPos;
		radius = tRadius;
	}

};

class Plane
{
public:
	XMVECTOR pos;
	XMVECTOR normal;
	int distance;
	Plane(XMVECTOR tPos, XMVECTOR tNormal, int tDistance)
	{
		pos = tPos;
		normal = tNormal;
		distance = tDistance;
	}

};

class RayTracingWidget : public QWidget
{
	int m_width;
	int m_height;
	virtual void paintEvent(QPaintEvent* pEvent);
public:
	RayTracingWidget(QWidget* pParent = NULL);
	XMVECTOR EmitRay(Ray& ray);
	HRESULT Init();
	HRESULT UnInit();
};

#endif