#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "player.h"
#include <sstream>

using namespace std;

#define FRAMERATE 60
#define GRAVITY 15
#define MAX_RIGIDS 15

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

int timerFps, frames = 0;

TTF_Font *font;
SDL_Rect weaponFontRect;
SDL_Texture *weaponFontTexture;
SDL_Surface *weaponFontSurface;

Player *rigidBodies[MAX_RIGIDS] = { NULL };

SDL_Color white = {255,255,255};

void applyEffects(int _ground)
{
	for(int i = 0; i < MAX_RIGIDS; i++)
	{
		if(rigidBodies[i] != NULL) {
			if(rigidBodies[i]->y + 160 < _ground) {
				//printf("less than GROUND\n");
				if(rigidBodies[i]->y + 160 + GRAVITY > _ground) rigidBodies[i]->y = _ground - 160;
				else rigidBodies[i]->y += GRAVITY;
			}
		}
	}
}

void addRigid(Player *player)
{
	for(int i = 0; i < MAX_RIGIDS; i++)
	{
		if(rigidBodies[i] == NULL) {
			rigidBodies[i] = player;
			printf("Added rigid at %d\n", i);
			break;
		}
	}
}

int main(int argc, char const *argv[])
{
	cout << "Started" << endl;
	

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 1;
	}

	if(TTF_Init() != 0) {
		return 1;
	}

	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	int sWidth = dm.w;
	int sHeight = dm.h;

	weaponFontRect = { sWidth - 150, sHeight - 75, 150, 75 };
	font = TTF_OpenFont("res/fonts/Munro.ttf", 16);

	//Gm *gameManager = new Gm(sHeight);
	Player *me = new Player("Paulo", 10, 10, 10, 10, true);
	addRigid(me);

	Player *enemy = new Player("Enemy", 10, 10, 1000, 10, false);
	addRigid(enemy);

	SDL_Window *window = SDL_CreateWindow("GAMAE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sWidth, sHeight, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	SDL_Surface *bgSurface = IMG_Load("res/images/bg.png");
	SDL_Texture *bgText = SDL_CreateTextureFromSurface(renderer, bgSurface);

	bool quit = false;
	int numFrames = 0;

	while(!quit) {

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		if(keystate[SDL_SCANCODE_ESCAPE])
			quit = true;

		frames++;

		for(int i = 0; i < MAX_RIGIDS; i++)
		{
			if(rigidBodies[i] != NULL)
			{
				rigidBodies[i]->doPlay();
				if(60 / frames == 4)
				{
					rigidBodies[i]->fourthPlay();
					if(frames == 60)
						frames = 0;
				}
			}
		}

		applyEffects(sHeight);

	    SDL_Event event;
	    while(SDL_PollEvent(&event))
	    {
	        if(event.type == SDL_QUIT)
	            quit = true;
	    }

	    timerFps = SDL_GetTicks() - timerFps; //I get the time it took to update and draw;

        if(timerFps < 1000/FRAMERATE) // if timerFps is < 16.6666...7 ms (meaning it loaded the frame too fast)
        {
            SDL_Delay((1000/FRAMERATE) - timerFps); //delay the frame to be in time
        }

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	    SDL_RenderClear(renderer);

	    // Draw background
	    SDL_RenderCopy(renderer, bgText, NULL, NULL);

		for(int i = 0; i < MAX_RIGIDS; i++)
		{
			if(rigidBodies[i] != NULL)
			{
				rigidBodies[i]->playerTexture = SDL_CreateTextureFromSurface(renderer, rigidBodies[i]->playerSurface);

				if(!rigidBodies[i]->isMirrored) 
				{
					SDL_RenderCopy(renderer, rigidBodies[i]->playerTexture, NULL, &rigidBodies[i]->playerRect);
				} 
				else 
				{
					SDL_RenderCopyEx(renderer, rigidBodies[i]->playerTexture, NULL, &rigidBodies[i]->playerRect, (double) 0, NULL, SDL_FLIP_HORIZONTAL);
				}

				if(rigidBodies[i]->isPrimary)
				{

					rigidBodies[i]->weapons[rigidBodies[i]->selectedGun - 1]->gunTexture = SDL_CreateTextureFromSurface(renderer, rigidBodies[i]->weapons[rigidBodies[i]->selectedGun - 1]->gunSurface); // Create gun texture

					if(!rigidBodies[i]->isMirrored) 
					{
						SDL_RenderCopy(renderer,
										rigidBodies[i]->weapons[rigidBodies[i]->selectedGun - 1]->gunTexture,
										NULL,
										&rigidBodies[i]->weapons[rigidBodies[i]->selectedGun - 1]->gunRect);
					} 
					else 
					{
						SDL_RenderCopyEx(renderer,
										rigidBodies[i]->weapons[rigidBodies[i]->selectedGun - 1]->gunTexture,
										NULL,
										&rigidBodies[i]->weapons[rigidBodies[i]->selectedGun - 1]->gunRect,
										(double) 0,
										NULL,
										SDL_FLIP_HORIZONTAL);
					}
				}
			}
		}

		string _text = (string) me->weapons[me->selectedGun - 1]->name + " " + SSTR(me->weapons[me->selectedGun - 1]->clipSize) + "/" + SSTR(me->weapons[me->selectedGun - 1]->maxAmmo);
		weaponFontSurface = TTF_RenderText_Solid(font, _text.c_str(), white);
		weaponFontTexture = SDL_CreateTextureFromSurface(renderer, weaponFontSurface);

		SDL_RenderCopy(renderer, weaponFontTexture, NULL, &weaponFontRect);

		SDL_RenderPresent(renderer);

	}

	SDL_Quit();

	return 0;
}
