#pragma once

#include "Vec3.h"

struct Texture
{
	virtual Vec3 Value(float u, float v, Vec3 &p) = 0;
};

struct ConstantTexture : public Texture
{
	Vec3 color;

	ConstantTexture() {}
	ConstantTexture(Vec3 c) : color(c) {}

	virtual Vec3 Value(float u, float v, Vec3 &p)
	{
		return color;
	}
};

struct TextureChecker : public Texture
{
	Texture *odd;
	Texture *even;

	TextureChecker() {}
	TextureChecker(Texture *t0, Texture *t1) : odd(t0), even(t1) {}

	virtual Vec3 Value(float u, float v, Vec3 &p)
	{
		float sines = ((sin(10.0f * p.x()) + 1.0f) / 2.0f + (sin(10.0f * p.y()) + 1.0f) / 2.0f + (sin(10.0f * p.z()) + 1.0f) / 2.0f) / 3.0f;
		if (sines < 0.5f)
		{
			return odd->Value(u, v, p);
		}
		else
		{
			return even->Value(u, v, p);
		}
	}
};

struct ImageTexture : public Texture
{
	unsigned char *data;
	int nx, ny, nn;


	ImageTexture() {}
	ImageTexture(unsigned char *pixels, int a, int b, int c) : nx(a), ny(b), nn(c)
	{
		data = (unsigned char*)malloc(nx*ny*nn);
		memcpy(data, pixels, nx*ny * sizeof(unsigned char)*nn);
	}

	virtual Vec3 Value(float u, float v, Vec3 &p)
	{
		int i = (int)((u)*(float)nx);
		int j = (int)((1.0f - v) * (float)ny - 0.001f);
		if (i < 0) i = 0;
		if (j < 0) j = 0;
		if (i > nx - 1) i = nx - 1;
		if (j > ny - 1) j = ny - 1;
		float r = (float)(data[3 * i + 3 * nx*j]) / 255.0f;
		float g = (float)(data[3 * i + 3 * nx*j + 1]) / 255.0f;
		float b = (float)(data[3 * i + 3 * nx*j + 2]) / 255.0f;
		return Vec3(r, g, b);
	}
};