#ifndef GM_H
#define GM_H

#include <iostream>

using namespace std;

#define GRAVITY 10

class Gm
{
public:
	Gm(int _ground);
	~Gm();

	int applyGravity(int y);

	int _ground;
	
};

#endif