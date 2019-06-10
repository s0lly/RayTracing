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

	Camera(Graphics &gfx)
	{
		origin = { 0.0f, 0.0f, 0.0f };
		botLeft = { -(float)gfx.ScreenWidth / (float)gfx.ScreenHeight, -1.0f, -1.0f };
		horizontal = { 2.0f * (float)gfx.ScreenWidth / (float)gfx.ScreenHeight, 0.0f, 0.0f };
		vertical = { 0.0f, 2.0f, 0.0f };
	}

	Ray GetRay(float u, float v)
	{
		return Ray(origin, botLeft + horizontal * u + vertical * v); //- origin
	}


};