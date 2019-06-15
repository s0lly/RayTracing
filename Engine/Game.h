/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Camera.h"
#include "Hitable.h"
#include "Ray.h"
#include "Vec3.h"
#include "float.h"
#include "Material.h"
#include <thread>




class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();


private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/

	
	Camera cam;
	Camera camOld;

	Hitable *world;

	BVHNode *bhv;

	int numObjects;

	int ns = 200;

	int imageCounter = 0;

	bool automation = false;
};

static Vec3 ReturnColorFromRay(Ray& ray, Hitable *world, int depth)
{
	

	HitRecord rec;
	if (world->Hit(ray, 0.0001f, 10000000000000000.0f, rec))
	{
		depth++;
		Ray scattered;
		Vec3 attenutation;
		Vec3 emitted = rec.matPtr->Emitted(rec.u, rec.v, rec.p);
		
		if (depth == 1 && rec.matPtr->isLight == true)
		{
			return Vec3(0.0f, 0.0f, 0.0f);
		}

		if (depth < 50 && rec.matPtr->scatter(ray, rec, attenutation, scattered))
		{
			return emitted + ReturnColorFromRay(scattered, world, depth) * attenutation;
		}
		else
		{
			return emitted;// Vec3(0.0f, 0.0f, 0.0f);
		}

	}
	else
	{
		return Vec3(0.0f, 0.0f, 0.0f);
		//Vec3 unitDirection = ray.Direction().GetNormalized();
		//float t = 0.5f * (unitDirection.y() + 1.0f);
		//return Vec3{ 1.0f, 1.0f, 1.0f } *(1.0f - t) + Vec3{ 0.5f, 0.7f, 1.0f } *(t);
	}
}