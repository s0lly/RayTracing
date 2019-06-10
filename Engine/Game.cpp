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
	gfx( wnd )
{
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
}

void Game::ComposeFrame()
{
	// Draw background

	Vec3 colorWhite{ 1.0f, 1.0f, 1.0f };
	Vec3 colorBlue{ 0.5f, 0.7f, 1.0f };

	for (int j = 0; j < gfx.ScreenHeight; j++)
	{
		float t = (float)j / (float)gfx.ScreenHeight;

		Vec3 color = colorWhite * (1 - t) + colorBlue * (t);

		int ir = (int)(255.9999f * color.r());
		int ig = (int)(255.9999f * color.g());
		int ib = (int)(255.9999f * color.b());

		for (int i = 0; i < gfx.ScreenWidth; i++)
		{
			gfx.PutPixel(i, gfx.ScreenHeight - j - 1, Color(ir, ig, ib));
		}
	}





	
}
