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
	cam( gfx, Vec3(0.0f, 2.0f, 2.0f), Vec3(0.0f, 0.0f, -1.0f).GetNormalized(), Vec3(0.0f, 1.0f, 0.0f), PI / 4.0f, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
		0.1f, (Vec3(0.0f, 2.0f, 2.0f) - Vec3(0.0f, 0.0f, -1.0f)).length())
{
	//list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(Vec3(0.1f, 0.2f, 0.5f)));
	//list[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(Vec3(0.8f, 0.8f, 0.0f)));
	//list[2] = new Sphere(Vec3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 1.0f));
	//list[3] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, new Dielectric(1.5f));
	//list[4] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), -0.45f, new Dielectric(1.5f));


	int n = 20;
	Hitable **list = new Hitable*[n+1];
	list[0] = new Sphere(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f, new Lambertian(Vec3(0.5f, 0.5f, 0.5f)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			if (i < n - 3)
			{
				float chooseMat = ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1));
				Vec3 center(a + 0.9f * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)), 0.2f, b + 0.9f * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)));
				if ((center - Vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f)
				{
					if (chooseMat < 0.8f)
					{
						list[i++] = new Sphere(center, 0.2f, new Lambertian(Vec3(((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)) * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)),
							((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)) * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)), ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)) * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)))));
					}
					else if (chooseMat < 0.95f)
					{
						list[i++] = new Sphere(center, 0.2f, new Metal(Vec3(0.5f * (1.0f + ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1))),
							0.5f * (1.0f + ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1))), 0.5f * (1.0f + ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)))), 0.5f * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1))));
					}
					else
					{
						list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
					}
				}
			}
		}
	}

	list[i++] = new Sphere(Vec3(0.0f, 1.0f, 0.0f), 1.0f, new Dielectric(1.5f));
	list[i++] = new Sphere(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, new Lambertian(Vec3(0.4f, 0.2f, 0.1f)));
	list[i++] = new Sphere(Vec3(4.0f, 1.0f, 0.0f), 1.0f, new Metal(Vec3(0.7f, 0.6f, 0.5f), 0.0f));


	world = new HitableList(list, i);

	numObjects = i;
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
		cam = Camera(gfx, cam.origin + Vec3(0.0f, 0.0f, -0.1f), cam.lookAt + Vec3(0.0f, 0.0f, -0.1f), cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		cam = Camera(gfx, cam.origin + Vec3(0.0f, 0.0f, 0.1f), cam.lookAt + Vec3(0.0f, 0.0f, 0.1f), cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam = Camera(gfx, cam.origin + Vec3(-0.1f, 0.0f, 0.0f), cam.lookAt + Vec3(-0.1f, 0.0f, 0.0f), cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam = Camera(gfx, cam.origin + Vec3(0.1f, 0.0f, 0.0f), cam.lookAt + Vec3(0.1f, 0.0f, 0.0f), cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		cam = Camera(gfx, cam.origin + Vec3(0.0f, 0.1f, 0.0f), cam.lookAt + Vec3(0.0f, 0.1f, 0.0f), cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('F'))
	{
		cam = Camera(gfx, cam.origin + Vec3(0.0f, -0.1f, 0.0f), cam.lookAt + Vec3(0.0f, -0.1f, 0.0f), cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}

	if (wnd.kbd.KeyIsPressed('J'))
	{
		cam = Camera(gfx, cam.origin, (cam.lookAt - cam.origin).RotateAroundArbitraryAxis(cam.v, 0.1f) + cam.origin, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('L'))
	{
		cam = Camera(gfx, cam.origin, (cam.lookAt - cam.origin).RotateAroundArbitraryAxis(cam.v, -0.1f) + cam.origin, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('I'))
	{
		cam = Camera(gfx, cam.origin, (cam.lookAt - cam.origin).RotateAroundArbitraryAxis(cam.u, 0.1f) + cam.origin, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('K'))
	{
		cam = Camera(gfx, cam.origin, (cam.lookAt - cam.origin).RotateAroundArbitraryAxis(cam.u, -0.1f) + cam.origin, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('U'))
	{
		cam = Camera(gfx, cam.origin, cam.lookAt, (cam.vUp).RotateAroundArbitraryAxis(cam.w, 0.1f), cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('O'))
	{
		cam = Camera(gfx, cam.origin, cam.lookAt, (cam.vUp).RotateAroundArbitraryAxis(cam.w, -0.1f), cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}

	if (wnd.kbd.KeyIsPressed('Z'))
	{
		cam = Camera(gfx, cam.origin, cam.lookAt, (cam.vUp), cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist * 1.1f);
	}
	if (wnd.kbd.KeyIsPressed('X'))
	{
		cam = Camera(gfx, cam.origin, cam.lookAt, (cam.vUp), cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist / 1.1f);
	}


	cam.lookAt.GetNormalized();

}




void Game::ComposeFrame()
{
	float firstHitSqrd = 100000000000000000.0f;
	float min_t = 999999999.9f;
	for (int i = 0; i < 1; i++)
	{
		float uCenter = 0.5f;
		float vCenter = 0.5f;
		Ray r = cam.GetRay(uCenter, vCenter);
		HitRecord rec;
		world->Hit(r, 0.0001f, 10000000000000000.0f, rec);
		//min_t = min_t < rec.t ? min_t : rec.t;
		firstHitSqrd = std::min(firstHitSqrd, (cam.origin - rec.p).lengthSqrd());
		
	}

	float distMultToMove = sqrt(firstHitSqrd) / cam.focusDist;

	//float distToMoveDir = 1.0f;
	//
	//if (distToMove < 0.0f)
	//{
	//	distToMoveDir = -1.0f;
	//}
	//
	//distToMove = (abs(distToMove) > 1.0f ? 1.0f : abs(distToMove)) * distToMoveDir;
	distMultToMove = distMultToMove > 1.5f ? 1.5f : distMultToMove;

	distMultToMove = distMultToMove * cam.focusDist;
	
	cam.focusDist = cam.focusDist * 0.6f + distMultToMove * 0.4f; //sqrt(firstHitSqrd);// 

	cam = Camera(gfx, cam.origin, cam.lookAt, (cam.vUp), cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
		cam.aperture, cam.focusDist);

	int ns = 2;

	auto *gfxPtr = &gfx;
	auto *worldPtr = &world;
	auto *camPtr = &cam;

	int numThreads = 20;
	int threadSize = gfx.ScreenHeight / numThreads + 1;

	std::vector<std::thread> threadList;
	for (int k = 0; k < numThreads; k++)
	{
		threadList.push_back(std::thread([k, ns, threadSize, gfxPtr, worldPtr, camPtr]()
		{
			for (int j = k * threadSize; (j < (k + 1) * threadSize) && (j < (gfxPtr->ScreenHeight)); j++)
			{

				for (int i = 0; i < gfxPtr->ScreenWidth; i++)
				{
					Vec3 col{ 0.0f, 0.0f, 0.0f };

					for (int s = 0; s < ns; s++)
					{
						float u = (float)(i + ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1))) / (float)gfxPtr->ScreenWidth;
						float v = (float)(j + ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1))) / (float)gfxPtr->ScreenHeight;
						Ray r = camPtr->GetRay(u, v);
						Vec3 p = r.PointOnRay(2.0f);
						col += ReturnColorFromRay(r, *worldPtr, 0);
					}

					col /= (float)ns;

					col = Vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));


					int ir = (int)(255.9999f * col.r());
					int ig = (int)(255.9999f * col.g());
					int ib = (int)(255.9999f * col.b());

					gfxPtr->PutPixel(i, gfxPtr->ScreenHeight - j - 1, Color(ir, ig, ib));
				}
			}
		}));
	}
	std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
	
}
