#pragma once

#include "Graphics.h"
#include "Ray.h"


static Vec3 RandomInUnitDisk()
{
	Vec3 p;

	do
	{
		p = Vec3(((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)), ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)), 0.0f) * 2.0f - Vec3(1.0f, 1.0f, 0.0f);

	} while (p.Dot(p) >= 1.0f);

	return p;
}

struct Camera
{
	// Data

	Vec3 origin;
	Vec3 botLeft;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 u, v, w;
	Vec3 lookAt;
	Vec3 vUp;
	float fov;
	float lensRadius;
	float aperture;
	float focusDist;

	// Functions

	Camera(Graphics &gfx, Vec3 lookFrom, Vec3 in_lookAt, Vec3 in_vUp, float in_fov, float aspect, float in_aperture, float in_focusDist)
	{
		fov = in_fov;
		aperture = in_aperture;
		focusDist = in_focusDist;
		lookAt = in_lookAt;
		vUp = in_vUp;
		lensRadius = aperture / 2.0f;
		float theta = fov;
		float halfHeight = tan(theta / 2.0f);
		float halfWidth = aspect * halfHeight;
		origin = lookFrom;
		w = (lookFrom - lookAt).GetNormalized();
		u = (vUp.Cross(w)).GetNormalized();
		v = w.Cross(u);
		botLeft = origin - u * halfWidth * focusDist - v * halfHeight * focusDist - w * focusDist;
		horizontal = u * 2.0f * halfWidth * focusDist;
		vertical = v * 2.0f * halfHeight * focusDist;
	}

	Ray GetRay(float s, float t)
	{
		Vec3 rd = RandomInUnitDisk() * lensRadius;
		Vec3 offset = u * rd.x() + v * rd.y();
		return Ray(origin + offset, botLeft + horizontal * s + vertical * t - origin - offset);
	}


};