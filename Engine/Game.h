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
#include "Ray.h"
#include "Vec3.h"


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();

	float DoesRayHitSphere(Vec3 &center, float radius, Ray &r)
	{
		Vec3 oc = r.Origin() - center;
		float a = r.Direction().Dot(r.Direction());
		float b = 2.0f * oc.Dot(r.Direction());
		float c = oc.Dot(oc) - radius * radius;
		float discriminant = b * b - 4 * a * c;

		if (discriminant < 0.0f)
		{
			return -1.0f;
		}
		else
		{
			return (-b - sqrt(discriminant)) / (2.0f * a);
		}

	}

	Vec3 ReturnColorFromRay(Ray& ray)
	{
		float t = (DoesRayHitSphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f, ray));
		if (t > 0.0f)
		{
			Vec3 n = (ray.PointOnRay(t) - Vec3(0.0f, 0.0f, -1.0f)).GetNormalized();
			return ((n + Vec3{ 1.0f, 1.0f, 1.0f }) * 0.5f);
		}

		Vec3 unitDirection = ray.Direction().GetNormalized();
		t = 0.5f * (unitDirection.y() + 1.0f);
		return Vec3{ 1.0f, 1.0f, 1.0f } * (1.0f - t) + Vec3{ 0.5f, 0.7f, 1.0f } * (t);
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

	Vec3 origin{ 0.0f, 0.0f, 0.0f };

};

