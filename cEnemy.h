#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

class cEnemy: public cBicho
{
public:
	cEnemy();
	~cEnemy();

	void Draw(int tex_id);
};
