#include <iostream>
#include "gm.h"

Gm::Gm(int _ground) {
		this->_ground = _ground;
	}

int Gm::applyGravity(int y) {
		int _y = y;
		if(_y + 160 < _ground) {
			printf("less than GROUND\n");
			if(_y + 160 + GRAVITY > _ground) _y = _ground;
			else _y += GRAVITY;
			return _y;
		}
		return -1;
	}