#pragma once

#include "Graphics.h"
#include "Ray.h"


struct Camera
{
	// Data

	Vec3 origin;
	Vec3 botLeft;
	Vec3 horizontal;
	Vec3 vertical;



	// Functions

	Camera(Graphics &gfx, Vec3 lookFrom, Vec3 lookAt, Vec3 vUp, float fov, float aspect)
	{
		Vec3 u, v, w;
		float theta = fov;
		float halfHeight = tan(theta / 2.0f);
		float halfWidth = aspect * halfHeight;
		origin = lookFrom;
		w = (lookFrom - lookAt).GetNormalized();
		u = (vUp.Cross(w)).GetNormalized();
		v = w.Cross(u);
		botLeft = origin - u * halfWidth - v * halfHeight - w;
		horizontal = u * 2.0f * halfWidth;
		vertical = v * 2.0f * halfHeight;	
	}

	Ray GetRay(float s, float t)
	{
		return Ray(origin, botLeft + horizontal * s + vertical * t - origin);
	}


};