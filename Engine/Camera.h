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
	float time0, time1;
	float halfHeight;
	float halfWidth;

	// Functions

	Camera(Graphics &gfx, Vec3 lookFrom, Vec3 in_lookAt, Vec3 in_vUp, float in_fov, float aspect, float in_aperture, float in_focusDist, float t0 = 0.0f, float t1 = 1.0f)
	{
		time0 = t0;
		time1 = t1;
		fov = in_fov;
		aperture = in_aperture;
		focusDist = in_focusDist;
		lookAt = in_lookAt;
		vUp = in_vUp;
		lensRadius = aperture / 2.0f;
		float theta = fov;
		halfHeight = tan(theta / 2.0f);
		halfWidth = aspect * halfHeight;
		origin = lookFrom;
		w = (lookFrom - lookAt).GetNormalized();
		u = (vUp.Cross(w)).GetNormalized();
		v = w.Cross(u);
		botLeft = origin - u * halfWidth * focusDist - v * halfHeight * focusDist - w * focusDist;
		horizontal = u * 2.0f * halfWidth * focusDist;
		vertical = v * 2.0f * halfHeight * focusDist;
	}

	Ray GetRay(float s, float t, Camera &camOld)
	{
		Vec3 rd = RandomInUnitDisk() * lensRadius;
		float time = time0 + ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)) * (time1 - time0);

		Vec3 newU = (u * time + camOld.u * (1 - time));
		Vec3 newV = (v * time + camOld.v * (1 - time));
		Vec3 newW = (w * time + camOld.w * (1 - time));

		Vec3 offset = newU * rd.x() + newV * rd.y();

		Vec3 newOrigin = (origin * time + camOld.origin * (1 - time));

		float newFocusDist = (focusDist * time + camOld.focusDist * (1 - time));
		
		Vec3 newBotLeft = newOrigin - newU * halfWidth * newFocusDist - newV * halfHeight * newFocusDist - newW * newFocusDist;

		Vec3 newHorizontal = newU * 2.0f * halfWidth * newFocusDist;
		Vec3 newVertical = newV * 2.0f * halfHeight * newFocusDist;

		return Ray(newOrigin + offset, newBotLeft + newHorizontal * s + newVertical * t - newOrigin - offset, time);
	}


};