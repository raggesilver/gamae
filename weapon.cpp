//
// Created by pimpao on 07/01/17.
//
#include "weapon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Weapon::Weapon(const char *name, int maxAmmo, int clipSize, float reloadDuration, float fireSpeed, float range,
               WeaponType type, const char *res)
{
    this->name = name;
    this->maxAmmo = maxAmmo;
    this->clipSize = clipSize;
    this->reloadDuration = reloadDuration;
    this->fireSpeed = fireSpeed;
    this->range = range;
    this->weaponType = type;

    this->gunSurface = IMG_Load(res);
    this->gunRect = {0, 0, 100, 60};
}

Weapon::~Weapon()
{

}