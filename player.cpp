#include <iostream>
#include "player.h"

using namespace std;

Player::Player(const char *name, int life, int speed, int x, int y, bool isPrimary) {
	this->name = name;
	//cout << this->name << endl;

	this->life = 10;
	//cout << this->life << endl;

	if(isPrimary)
	{
		this->playerSurface = IMG_Load("res/images/randomguy.png");
	} else {
		this->playerSurface = IMG_Load("res/images/randomguy-evil.png");
	}

	this->x = x;
	this->y = y;
	this->speed = speed;
	this->curSpeed = speed;

	this->playerRect = { this->x, this->y, 120, 160 };

	this->life = life;

	this->isPrimary = isPrimary;

	this->weapons[0] = new Weapon("M4", 210, 30, 3, 0.3, 500, AUTO, "res/weapons/M4/m4-default.png");
	
	this->weapons[1] = new Weapon("PUMP", 48, 8, 1, 0.5, 500, PUMP, "res/weapons/PUMP/pump-default.png");

	this->selectedGun = 1;
}

Player::~Player() {

}

void Player::doPlay() {
	if(this->isPrimary)
	{
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);

		if(keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
		{
			this->x -= this->curSpeed;
			this->isMirrored = true; 
		}

		if(keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
		{
			this->x += this->curSpeed;
			this->isMirrored = false;
		}

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYUP)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_1:
						this->selectedGun = 1;
						break;
					case SDLK_2:
						this->selectedGun = 2;
						break;
					case SDLK_q:
						this->selectedGun = (this->selectedGun == 1) ? 2 : 1;
						break;
				}
			}
		}
	}

	//int tempY = this->gameManager->applyGravity(this->y);
	//if(tempY != -1) this->y = tempY;

	this->playerRect.x = this->x;
	this->playerRect.y = this->y;

	if(this->isMirrored)
	{
		this->gunX = this->x - 45;
		this->gunY = this->y + 128 -50;
	}
	else
	{
		this->gunX = this->x + 55;
		this->gunY = this->y + 128 -50;
	}

	this->weapons[this->selectedGun - 1]->gunRect.x = this->gunX;
	this->weapons[this->selectedGun - 1]->gunRect.y = this->gunY;

	/*if(this->isPrimary)
	cout << this->isMirrored << "  " << this->x << " (" << this->gunX << endl;*/
}

void Player::fourthPlay()
{
	//printf("Fourth\n");
	return;
}