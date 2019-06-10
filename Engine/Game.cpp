/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	cam( gfx )
{
	list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);
	list[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed('W'))
	{
		cam.origin.z() -= 0.01f;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		cam.origin.z() += 0.01f;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam.origin.x() -= 0.01f;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam.origin.x() += 0.01f;
	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		cam.origin.y() += 0.01f;
	}
	if (wnd.kbd.KeyIsPressed('F'))
	{
		cam.origin.y() -= 0.01f;
	}
}




void Game::ComposeFrame()
{
	int ns = 100;

	for (int j = 0; j < gfx.ScreenHeight; j++)
	{
		for (int i = 0; i < gfx.ScreenWidth; i++)
		{
			Vec3 col{ 0.0f, 0.0f, 0.0f };

			for (int s = 0; s < ns; s++)
			{
				float u = (float)(i + ((float)(rand() % RAND_MAX) / (float)RAND_MAX)) / (float)gfx.ScreenWidth;
				float v = (float)(j + ((float)(rand() % RAND_MAX) / (float)RAND_MAX)) / (float)gfx.ScreenHeight;
				Ray r = cam.GetRay(u, v);
				Vec3 p = r.PointOnRay(2.0f);
				col += ReturnColorFromRay(r, world);
			}

			col /= (float)ns;
			

			int ir = (int)(255.9999f * col.r());
			int ig = (int)(255.9999f * col.g());
			int ib = (int)(255.9999f * col.b());

			gfx.PutPixel(i, gfx.ScreenHeight - j - 1, Color(ir, ig, ib));
		}
	}
	
}
