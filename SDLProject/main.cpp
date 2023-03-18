#include <SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};

bool Init();
bool LoadMedia();
void Close();
SDL_Surface* LoadSurface(std::string path);

SDL_Window* g_Window = NULL;
SDL_Surface* g_ScreenSurface = NULL;
SDL_Surface* g_KeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* g_CurrentSurface = NULL;

int main(int argc, char* args[])
{
	if (!Init())
	{
		printf("Failed to initialise!\n");
	}
	else
	{
		if (!LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			SDL_Event event;
			bool quit = false;
			g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			while (!quit)
			{
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (event.type == SDL_KEYDOWN)
					{
						switch (event.key.keysym.sym)
						{
						case SDLK_UP:
							g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;
						}
					}
				}
				SDL_BlitSurface(g_CurrentSurface, NULL, g_ScreenSurface, NULL);
				SDL_UpdateWindowSurface(g_Window);
			}
		}
	}

	Close();

	return 0;
}

bool Init()
{
	bool bSuccess = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialise! SDL_Error: %s", SDL_GetError());
		bSuccess = false;
	}
	else
	{
		g_Window = SDL_CreateWindow("An SDL window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (g_Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s", SDL_GetError());
			bSuccess = false;
		}
		else
		{
			g_ScreenSurface = SDL_GetWindowSurface(g_Window);
		}
	}

	return bSuccess;
}

bool LoadMedia()
{
	bool bSuccess = true;

	g_KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = LoadSurface("C:/Personal/SDLProject/Media/default.bmp");
	if (g_KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Unable to load default image: %s\n", SDL_GetError());
		bSuccess = false;
	}

	g_KeyPressSurfaces[KEY_PRESS_SURFACE_UP] = LoadSurface("C:/Personal/SDLProject/Media/up.bmp");
	if (g_KeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Unable to load up image: %s\n", SDL_GetError());
		bSuccess = false;
	}

	g_KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = LoadSurface("C:/Personal/SDLProject/Media/down.bmp");
	if (g_KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Unable to load down image: %s\n", SDL_GetError());
		bSuccess = false;
	}

	g_KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = LoadSurface("C:/Personal/SDLProject/Media/left.bmp");
	if (g_KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Unable to load left image: %s\n", SDL_GetError());
		bSuccess = false;
	}

	g_KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = LoadSurface("C:/Personal/SDLProject/Media/right.bmp");
	if (g_KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Unable to load right image: %s\n", SDL_GetError());
		bSuccess = false;
	}

	return bSuccess;
}

void Close()
{
	SDL_FreeSurface(g_CurrentSurface);
	g_CurrentSurface = NULL;

	SDL_DestroyWindow(g_Window);
	g_Window = NULL;

	SDL_Quit();
}

SDL_Surface* LoadSurface(std::string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}
