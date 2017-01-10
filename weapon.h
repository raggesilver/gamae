#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <SDL2/SDL.h>

enum WeaponType {
	AUTO,
	SEMI,
	PUMP,
	BOLT
};

/* Pump is shotgun*/

class Weapon
{
	public:
		Weapon(const char *name, int maxAmmo, int clipSize, float reloadDuration, float fireSpeed, float range, WeaponType type, const char *res);
		~Weapon();

		const char *name;
		const char *description; // Just in case

		/* On future make private from here */

		int maxAmmo;
		int curAmmo;

		int clipSize;

		WeaponType weaponType;

		float fireSpeed; // Delay between one shot and other, for pump and bolt types this means the time that the bolt action takes

		float range; // Max distance for the bullet

		float reloadDuration;
		float curReloadTime;

		SDL_Texture *gunTexture;
		SDL_Surface *gunSurface;
		SDL_Rect gunRect;
	
};

#endif