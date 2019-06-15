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
#include <string>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	cam( gfx, Vec3(0.0f, 1.5f, -5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), PI / 4.0f, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
		0.1f, (Vec3(0.0f, 2.0f, 2.0f) - Vec3(0.0f, 0.0f, -1.0f)).length()),
	camOld(gfx, Vec3(0.0f, 1.5f, -5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), PI / 4.0f, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
		0.1f, (Vec3(0.0f, 2.0f, 2.0f) - Vec3(0.0f, 0.0f, -1.0f)).length())
{
	//list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(Vec3(0.1f, 0.2f, 0.5f)));
	//list[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(Vec3(0.8f, 0.8f, 0.0f)));
	//list[2] = new Sphere(Vec3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 1.0f));
	//list[3] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, new Dielectric(1.5f));
	//list[4] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), -0.45f, new Dielectric(1.5f));

	int nx, ny, nn;

	unsigned char *texDataVenus = stbi_load("8k_venus_atmosphere.jpg", &nx, &ny, &nn, 0);
	Material *matImageVenus = new Lambertian(new ImageTexture(texDataVenus, nx, ny, nn));

	unsigned char *texDataEarth = stbi_load("8k_earth_daymap.jpg", &nx, &ny, &nn, 0);
	Material *matImageEarth = new Lambertian(new ImageTexture(texDataEarth, nx, ny, nn));

	unsigned char *texDataMars = stbi_load("8k_mars.jpg", &nx, &ny, &nn, 0);
	Material *matImageMars = new Lambertian(new ImageTexture(texDataMars, nx, ny, nn));

	unsigned char *texDataMoon = stbi_load("8k_moon.jpg", &nx, &ny, &nn, 0);
	Material *matImageMoon = new Lambertian(new ImageTexture(texDataMoon, nx, ny, nn));

	


	int n = 5;
	Hitable **list = new Hitable*[n+1];
	Texture *checker = new TextureChecker(new ConstantTexture(Vec3(0.2f, 0.3f, 0.1f)), new ConstantTexture(Vec3(0.9f, 0.9f, 0.9f)));
	list[0] = new Sphere(Vec3(0.0f, 40.0f, 100.0f), 50.0f, new DiffuseLight(new ConstantTexture(Vec3(1.0f, 1.0f, 1.0f))));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			if (i < n - 4)
			{
				float chooseMat = ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1));
				Vec3 center(a + 0.9f * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)), 0.2f, b + 0.9f * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)));
				if ((center - Vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f)
				{
					if (chooseMat < 0.8f)
					{
						list[i++] = new Sphere(center, 0.2f, new Lambertian(new ConstantTexture(Vec3(((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)) * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)),
							((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)) * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)), ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)) * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1))))));
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

	//list[i++] = new Sphere(Vec3(-1.5f, 0.0f, 0.0f), 0.94888f, new Dielectric(1.5f));
	list[i++] = new Sphere(Vec3(-2.5f, 0.0f, 0.0f), 0.94888f, matImageVenus);
	list[i++] = new Sphere(Vec3(0.0f, 0.0f, 0.0f), 1.0f, matImageEarth);//ConstantTexture(Vec3(0.4f, 0.2f, 0.1f)) //matImageTest
	//list[i++] = new Sphere(Vec3(1.5f, 0.0f, 0.0f), 0.532f, new Metal(Vec3(0.7f, 0.6f, 0.5f), 0.0f));
	list[i++] = new Sphere(Vec3(2.5f, 0.0f, 0.0f), 0.532f, matImageMars);
	list[i++] = new Sphere(Vec3(1.414f, 0.17935f, 1.414f), 0.2726f, matImageMoon);


	world = new HitableList(list, i);

	//bhv = new BHVNode(list, i, 0.0f, 1.0f);

	numObjects = i;

	//SetCursorPos(560 + gfx.ScreenWidth / 2, 315 + gfx.ScreenHeight / 2);
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
	camOld = cam;

	cam = Camera(gfx, cam.origin + cam.u / 50.0f, Vec3(0.0f, 0.0f, 0.0f), cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
		cam.aperture, cam.focusDist);

	if (wnd.kbd.KeyIsPressed('W'))
	{
		cam = Camera(gfx, cam.origin - cam.w / 10.0f, cam.lookAt - cam.w / 10.0f, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		cam = Camera(gfx, cam.origin + cam.w / 10.0f, cam.lookAt + cam.w / 10.0f, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam = Camera(gfx, cam.origin - cam.u / 10.0f, cam.lookAt - cam.u / 10.0f, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam = Camera(gfx, cam.origin + cam.u / 10.0f, cam.lookAt + cam.u / 10.0f, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		cam = Camera(gfx, cam.origin + cam.v / 10.0f, cam.lookAt + cam.v / 10.0f, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('F'))
	{
		cam = Camera(gfx, cam.origin - cam.v / 10.0f, cam.lookAt - cam.v / 10.0f, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
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
		cam = Camera(gfx, cam.origin, cam.lookAt, (cam.vUp), cam.fov * 1.1f, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}
	if (wnd.kbd.KeyIsPressed('X'))
	{
		cam = Camera(gfx, cam.origin, cam.lookAt, (cam.vUp), cam.fov / 1.1f, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
			cam.aperture, cam.focusDist);
	}

	if (wnd.kbd.KeyIsPressed(VK_CONTROL))
	{
		ns--;
	}
	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		ns++;
	}

	ns = ns < 1 ? 1 : ns;

	int check = wnd.mouse.GetPosY();
	//float moveUp = (float)((gfx.ScreenHeight / 2) - wnd.mouse.GetPosY()) / 2000.0f;
	//float moveSide = (float)((gfx.ScreenWidth / 2) - wnd.mouse.GetPosX()) / 2000.0f;
	//cam = Camera(gfx, cam.origin, (cam.lookAt - cam.origin).RotateAroundArbitraryAxis(cam.u, moveUp) + cam.origin, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
	//	cam.aperture, cam.focusDist);
	//cam = Camera(gfx, cam.origin, (cam.lookAt - cam.origin).RotateAroundArbitraryAxis(cam.v, moveSide) + cam.origin, cam.vUp, cam.fov, (float)gfx.ScreenWidth / (float)gfx.ScreenHeight,
	//	cam.aperture, cam.focusDist);

	cam.lookAt.GetNormalized();


	//SetCursorPos(560 + gfx.ScreenWidth / 2, 315 + gfx.ScreenHeight / 2);
	//SetCursor(NULL);

	world->Update(1.0f);



}




void Game::ComposeFrame()
{
	if (automation == false)
	{


		float firstHitSqrd = 100000000000000000.0f;
		float min_t = 999999999.9f;
		for (int i = 0; i < 1; i++)
		{
			float uCenter = 0.5f;
			float vCenter = 0.5f;
			Ray r = cam.GetRay(uCenter, vCenter, camOld);
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



		auto *gfxPtr = &gfx;
		auto *worldPtr = &world;
		auto *camPtr = &cam;
		auto *camOldPtr = &camOld;
		auto *nsPtr = &ns;

		int numThreads = 8;
		int threadSize = gfx.ScreenHeight / numThreads + 1;

		std::vector<std::thread> threadList;
		for (int k = 0; k < numThreads; k++)
		{
			threadList.push_back(std::thread([k, nsPtr, threadSize, gfxPtr, worldPtr, camPtr, camOldPtr]()
			{
				for (int j = k * threadSize; (j < (k + 1) * threadSize) && (j < (gfxPtr->ScreenHeight)); j++)
				{

					for (int i = 0; i < gfxPtr->ScreenWidth; i++)
					{
						Vec3 col{ 0.0f, 0.0f, 0.0f };

						for (int s = 0; s < *nsPtr; s++)
						{
							if (i == gfxPtr->ScreenWidth / 2)
							{
								int check = 0;
							}
							float u = (float)(i + ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1))) / (float)gfxPtr->ScreenWidth;
							//float u = uBase;
							//u = (2.0f * (u - 0.5f)) * camPtr->fov * (float)gfxPtr->ScreenWidth / (float)gfxPtr->ScreenHeight;
							//float base = 1.0f - cosf(camPtr->fov * (float)gfxPtr->ScreenWidth / (float)gfxPtr->ScreenHeight);
							//float sign = u < 0.0f ? -1.0f : 1.0f;
							//u = 1.0f - cosf(u);
							//u = u * sign / base;
							//u = (u) / 2.0f + 0.5f;

							float v = (float)(j + ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1))) / (float)gfxPtr->ScreenHeight;
							//float v = vBase;
							//v = (2.0f * (v - 0.5f)) * camPtr->fov;
							//v = cosf(v);
							//v = (vBase - 0.5f) / v + 0.5f;

							Ray r = camPtr->GetRay(u, v, *camOldPtr);
							//Vec3 p = r.PointOnRay(2.0f);
							col += ReturnColorFromRay(r, *worldPtr, 0);
						}

						col /= (float)(*nsPtr);

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


		for (int i = gfx.ScreenWidth / 2 - 5; i <= gfx.ScreenWidth / 2 + 5; i++)
		{
			for (int j = gfx.ScreenHeight / 2 - 5; j <= gfx.ScreenHeight / 2 + 5; j++)
			{
				if (i == gfx.ScreenWidth / 2 - 5 || i == gfx.ScreenWidth / 2 + 5 ||
					j == gfx.ScreenHeight / 2 - 5 || j == gfx.ScreenHeight / 2 + 5)
				{
					//gfx.PutPixel(i, j, Colors::Magenta);
				}
			}
		}

		uint8_t* rgb_image = (uint8_t*)malloc(gfx.ScreenWidth * gfx.ScreenHeight * 3);

		for (int y = 0; y < gfx.ScreenHeight; y++)
		{
			for (int x = 0; x < gfx.ScreenWidth; x++)
			{
				rgb_image[(y * gfx.ScreenWidth + x) * 3 + 0] = (uint8_t)gfx.GetPixel(x, y).GetR();
				rgb_image[(y * gfx.ScreenWidth + x) * 3 + 1] = (uint8_t)gfx.GetPixel(x, y).GetG();
				rgb_image[(y * gfx.ScreenWidth + x) * 3 + 2] = (uint8_t)gfx.GetPixel(x, y).GetB();
			}
		}

		std::stringstream fileNameStream;

		fileNameStream << "image" << std::to_string(imageCounter) << ".png";

		std::string fileName = fileNameStream.str();

		//stbi_write_png(fileName.c_str(), gfx.ScreenWidth, gfx.ScreenHeight, 3, rgb_image, gfx.ScreenWidth * 3);

		imageCounter++;

	}
	else
	{
		int nx, ny, nn;

		std::stringstream fileNameStream;
		fileNameStream << "image" << std::to_string(imageCounter) << ".png";
		std::string fileName = fileNameStream.str();

		unsigned char *screenImage = stbi_load(fileName.c_str(), &nx, &ny, &nn, 0);

		for (int y = 0; y < gfx.ScreenHeight; y++)
		{
			for (int x = 0; x < gfx.ScreenWidth; x++)
			{
				Color c = Color(screenImage[(y * gfx.ScreenWidth + x) * 3 + 0],
					screenImage[(y * gfx.ScreenWidth + x) * 3 + 1],
					screenImage[(y * gfx.ScreenWidth + x) * 3 + 2]);
				gfx.PutPixel(x, y, c);
			}
		}

		imageCounter++;

		if (imageCounter > 1576)
		{
			imageCounter = 0;
		}
	}
}
