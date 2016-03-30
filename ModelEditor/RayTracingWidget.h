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
#include <stdlib.h>
#include <time.h>

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
		right = XMVector3Cross(up, front);
	}

};

class Ray
{
public:
	XMVECTOR pos;
	XMVECTOR dir;
	Ray(){}
	Ray(XMVECTOR tPos, XMVECTOR tDir)
	{
		pos = tPos;
		dir = tDir;
	}
	void SetRay(XMVECTOR tPos, XMVECTOR tDir)
	{
		pos = tPos;
		dir = tDir;
	}
};

class Color
{
public:
	XMVECTOR color;
	Color()
	{
		color.m128_f32[0] = 0.0f;
		color.m128_f32[1] = 0.0f;
		color.m128_f32[2] = 0.0f;
		color.m128_f32[3] = 0.0f;
	}
	Color operator*(float t)
	{
		Color result;
		result.color = color * t;
		return result;
	}
	Color operator+(Color& c)
	{
		Color result;
		result.color = color + c.color;
		return result;
	}
	Color operator/(float divider)
	{
		Color result;
		result.color = color / divider;
		return result;
	}
	void SetValid()
	{
		if (color.m128_f32[0] > 1) color.m128_f32[0] = 1; else if (color.m128_f32[0] < 0) color.m128_f32[0] = 0;
		if (color.m128_f32[1] > 1) color.m128_f32[1] = 1; else if (color.m128_f32[1] < 0) color.m128_f32[1] = 0;
		if (color.m128_f32[2] > 1) color.m128_f32[2] = 1; else if (color.m128_f32[2] < 0) color.m128_f32[2] = 0;
	}


};

class Light
{
public:
	XMVECTOR dir;
	Color lightColor;
};

class Material
{
public:
	float reflectiveness;
	Material(float tReflectiveness)
	{
		reflectiveness = tReflectiveness;
	}

	virtual Color sample(Ray& ray, XMVECTOR& pos, XMVECTOR& normal) = 0;
};

class CheckerMaterial : public Material
{
	float scale;
public:
	CheckerMaterial(float tScale, float tReflectiveness) : Material(tReflectiveness)
	{
		scale = tScale;
	}

	Color sample(Ray& ray, XMVECTOR& pos, XMVECTOR& normal)
	{
		Color black, white;
		black.color.m128_f32[0] = black.color.m128_f32[1] = black.color.m128_f32[2] = 0.0f;
		white.color.m128_f32[0] = white.color.m128_f32[1] = white.color.m128_f32[2] = 1.0f;
		return abs((int)floor(pos.m128_f32[0] * scale + 0.5) + (int)floor(pos.m128_f32[2] * scale + 0.5)) % 2 == 0 ? black : white;
	}

};

class PhongMaterial : public Material
{
	XMVECTOR diffuse;
	XMVECTOR specular;
	float shininess;
	float reflectiveness;
	Light light;
public:
	PhongMaterial(XMVECTOR& tDiffuse, XMVECTOR& tSpecular, float tShininess, float tReflectiveness) : Material(tReflectiveness)
	{
		diffuse = tDiffuse;
		specular = tSpecular;
		shininess = tShininess;

		light.dir.m128_f32[0] = 1.0f;
		light.dir.m128_f32[1] = 1.0f;
		light.dir.m128_f32[2] = -1.0f;
		light.dir.m128_f32[3] = 1.0f;
		light.dir = XMVector3Normalize(light.dir);
		light.lightColor.color.m128_f32[0] = 1.0f;
		light.lightColor.color.m128_f32[1] = 1.0f;
		light.lightColor.color.m128_f32[2] = 1.0f;
	}
	Color sample(Ray& ray, XMVECTOR& pos, XMVECTOR& normal)
	{
		float NdotL = XMVector3Dot(normal, light.dir).m128_f32[0];
		XMVECTOR H = XMVector3Normalize(light.dir - ray.dir);
		float NdotH = XMVector3Dot(normal, H).m128_f32[0];
		XMVECTOR diffuseTerm = diffuse * max(NdotL, 0);
		XMVECTOR specularTerm = specular * pow(max(NdotH, 0), shininess);
		Color color;
		color.color = light.lightColor.color * (diffuseTerm + specularTerm);
		return color;
	}

};

class IntersectResult;
class Geometry
{
public:
	XMVECTOR pos;
	Material* pMaterial;
	Geometry(XMVECTOR tPos, Material* tpMaterial)
	{
		pos = tPos;
		pMaterial = tpMaterial;
	}
	virtual bool IntersectPoint(Ray& ray, IntersectResult& result) = 0;
};

class IntersectResult
{
public:
	bool isHit;
	Geometry* geometry;
	XMVECTOR pos;
	XMVECTOR normal;
	float distance;
};

class Sphere : public Geometry
{
	// |VectorX - VectorOrigin| = r
public:
	float radius;
	Sphere(XMVECTOR tPos, float tRadius, Material* tpMaterial) : Geometry(tPos, tpMaterial)
	{
		radius = tRadius;
	}
	bool IntersectPoint(Ray& ray, IntersectResult& result)
	{
		XMVECTOR v = ray.pos - pos;
		float a0 =  XMVector3LengthSq(v).m128_f32[0] - radius * radius;
		float DdotV = XMVector3Dot(ray.dir, v).m128_f32[0];

		if (DdotV <= 0)
		{
			float discr = DdotV * DdotV - a0;
			if (discr >= 0)
			{
				result.geometry = this;
				result.distance = -DdotV - sqrt(discr);
				result.pos = ray.pos + (ray.dir * result.distance);
				result.normal = XMVector3Normalize(result.pos - pos);
				return true;
			}

		}
		return false;
	}

};

class Plane : public Geometry
{
	// VectorX * VectorNormal = d
public:
	XMVECTOR normal;
	int distance;
	Plane(XMVECTOR tPos, XMVECTOR tNormal, int tDistance, Material* tpMaterial) : Geometry(tPos, tpMaterial)
	{
		normal = tNormal;
		distance = tDistance;
	}
	bool IntersectPoint(Ray& ray, IntersectResult& result)
	{
		float distance = XMVector3Dot(normal, ray.pos - pos).m128_f32[0];
		float cos = XMVector3Dot(normal, ray.dir).m128_f32[0];
		if (cos >= 0)
			return false;

		float t = - distance / cos;
		XMVECTOR pos = ray.pos + (ray.dir * t);

		result.pos = pos;
		result.normal = normal;
		result.geometry = this;

		return true;
	}

};

class RayTracingWidget : public QWidget
{
	int m_width;
	int m_height;
	Sphere* sphere1;
	Sphere* sphere2;
	Plane* plane;
	Camera* camera;
	PhongMaterial* phongMaterial1;
	PhongMaterial* phongMaterial2;
	CheckerMaterial* checkerMaterial;
	Geometry* geometry[3];
	int maxDepth;
	Sphere* test;
	Camera* testCamera;
	Color BLACK;
	Color WHITE;
	virtual void paintEvent(QPaintEvent* pEvent);
public:
	RayTracingWidget(QWidget* pParent = NULL);
	Color EmitRay(Ray& ray, int depth);
	Color TestEmitRay(Ray& ray);
	XMVECTOR RandomDirOnHemisphere(XMVECTOR& normal);
	HRESULT Init();
	HRESULT UnInit();
};

#endif