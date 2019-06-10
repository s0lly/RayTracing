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


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();


	Vec3 ReturnColorFromRay(Ray& ray, Hitable *world)
	{
		HitRecord rec;
		if (world->Hit(ray, 0.0f, 10000000000000000.0f, rec))
		{
			return ((rec.normal + Vec3{ 1.0f, 1.0f, 1.0f }) * 0.5f);
		}
		else
		{
			Vec3 unitDirection = ray.Direction().GetNormalized();
			float t = 0.5f * (unitDirection.y() + 1.0f);
			return Vec3{ 1.0f, 1.0f, 1.0f } *(1.0f - t) + Vec3{ 0.5f, 0.7f, 1.0f } *(t);
		}
	}




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

	Hitable *list[2];
	Hitable *world = new HitableList(list, 2);

};

