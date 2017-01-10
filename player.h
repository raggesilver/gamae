#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "weapon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

//Weapon *GUN_M4 = new Weapon("M4", 210, 30, 3, 0.3, 500, AUTO, "res/images/M4/m4-default.png");

class Player
{
	public:
		Player(const char* name, int life, int speed, int x, int y, bool isPrimary);
		~Player();
		void doPlay();
        void fourthPlay();

		const char *name;

        bool isSpawned, isChangingWeapon;
        int x, y, gunX, gunY;

        // 1 = primary and 2 = secondary
        int selectedGun;

        int speed, curSpeed;

        int life;

        bool isOnAir, isMirrored, isPrimary;

        //Gm *gameManager;

        /* Mental note to create a way to distribute physics over time, so jump for instance I'll give the height and the strength and the game will make the jump smooth, as well as apply gravity*/

        Weapon *weapons[2];

        SDL_Texture *playerTexture;
        SDL_Rect playerRect;
        SDL_Surface *playerSurface;

};
#endif
