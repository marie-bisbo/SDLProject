#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool Init();
bool LoadMedia();
void Close();

SDL_Window* g_Window = NULL;
SDL_Surface* g_ScreenSurface = NULL;
SDL_Surface* g_SurfaceImage = NULL;

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
			while (!quit)
			{
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				SDL_BlitSurface(g_SurfaceImage, NULL, g_ScreenSurface, NULL);
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

	g_SurfaceImage = SDL_LoadBMP("C:/Personal/SDLProject/Media/a_window.bmp");
	if (g_SurfaceImage == NULL)
	{
		printf("Unable to load image: %s\n", SDL_GetError());
		bSuccess = false;
	}

	return bSuccess;
}

void Close()
{
	SDL_FreeSurface(g_SurfaceImage);
	g_SurfaceImage = NULL;

	SDL_DestroyWindow(g_Window);
	g_Window = NULL;

	SDL_Quit();
}
