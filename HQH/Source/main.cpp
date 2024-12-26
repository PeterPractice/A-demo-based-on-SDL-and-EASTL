#include "HQH.H"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h> // only include this one in the source file with main()!
#include <EAMain/EAMain.h>
#include "HQHDebugManager.h"
#include "HQHGameInstance.h"

void Init()
{
    EA::EAMain::SetReportFunction(HQH::ReportDefault);
}

void CreateManager()
{
    HQHDebugManager* pHQHDebugManager = HQHDebugManagerSA::CreateInstance("HQHDebugManager");
    EA_ASSERT(pHQHDebugManager);

    HQHGameInstance* pHQHGameInstance = HQHGameInstanceSA::CreateInstance("HQHGameInstance");
    EA_ASSERT(pHQHGameInstance);
}

void DestroyManager()
{
    HQHGameInstanceSA::DestroyInstance();
    HQHDebugManagerSA::DestroyInstance();
}

void PrintTips()
{
	HQH::Log("========\n");
	HQH::Log("Key control:\n");
	HQH::Log("1: Print debug1 EASTL.\n");
	HQH::Log("2: Print debug2 Random.\n");
	HQH::Log("D: Print debug info.\n");
	HQH::Log("Space: Accelerated (Flash) background.\n");
	HQH::Log("H: Print tips.\n");
	HQH::Log("Q(or Escape): Exit.\n");
	HQH::Log("========\n");
}

int main(int argc, char* argv[])
{
	Init();

	CreateManager();

	PrintTips();

	SDL_Init(SDL_INIT_VIDEO);

	const int WIDTH = 640;
	const int HEIGHT = 480;
	SDL_Window* window = SDL_CreateWindow("Hello SDL", WIDTH, HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_PRESENTVSYNC);

	SDL_StartTextInput();
	SDL_PumpEvents();

	int done = 0;
	size_t count = 0;
	size_t countStep = 1;
	bool isPrintDebugInfo = false;
	SDL_Event event;
	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_KEY_DOWN:
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_1:
				{
					if (HQHDebugManager* pHQHDebugManager = HQHDebugManagerSA::GetInstance())
					{
						pHQHDebugManager->RunDebug(1);
					}
				}
				break;

				case SDLK_2:
				{
					if (HQHDebugManager* pHQHDebugManager = HQHDebugManagerSA::GetInstance())
					{
						pHQHDebugManager->RunDebug(2);
					}
				}
				break;

				case SDLK_d:
				{
					isPrintDebugInfo = !isPrintDebugInfo;
				}
				break;

				case SDLK_SPACE:
				{
					++countStep;
				}
				break;

				case SDLK_h:
				{
					PrintTips();
				}
				break;

				case SDLK_ESCAPE:
				case SDLK_q:
				{
					done = 1;
				}
				break;

				default:
					break;
				}
			}
			break;

			case SDL_EVENT_KEY_UP:
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
				{
					countStep = 1;
				}
				break;

				default:
					break;
				}
			}
			break;

			case SDL_EVENT_TEXT_INPUT:
			{
				HQH::Log("INPUT: %s\n", event.text.text);
			}
			break;

			case SDL_EVENT_QUIT:
			{
				done = 1;
			}
			break;

			default:
				break;
			}
		}

		count += countStep;
		size_t countM = count % (256 * 6);
		Uint8 n = 1;
		Uint8 r = 0;
		Uint8 g = 0;
		Uint8 b = 0;
		if ((0 <= countM) && (255 >= countM))
		{
			r = (countM * n) % 256;
			g = 0;
			b = 255;
		}
		else if ((256 <= countM) && ((255 + 256) >= countM))
		{
			r = 255;
			g = 0;
			b = 255 - ((countM * n) % 256);
		}
		else if (((256 * 2) <= countM) && ((255 + (256 * 2)) >= countM))
		{
			r = 255;
			g = ((countM * n) % 256);
			b = 0;
		}
		else if (((256 * 3) <= countM) && ((255 + (256 * 3)) >= countM))
		{
			r = 255 - ((countM * n) % 256);
			g = 255;
			b = 0;
		}
		else if (((256 * 4) <= countM) && ((255 + (256 * 4)) >= countM))
		{
			r = 0;
			g = 255;
			b = ((countM * n) % 256);
		}
		else if (((256 * 5) <= countM) && ((255 + (256 * 5)) >= countM))
		{
			r = 0;
			g = 255 - ((countM * n) % 256);
			b = 255;
		}
		if (isPrintDebugInfo)
		{
			HQH::Log("countM: %4d, r: %3d, g: %3d, b: %3d. countStep: %d\n", countM, r, g, b, countStep);
		}
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	DestroyManager();

	return 0;
}
