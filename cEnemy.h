#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

    typedef struct {
            int x;
            int y;
			int dist;
    } Estado;
class cEnemy: public cBicho
{
public:
	cEnemy();
	~cEnemy();

	void Draw(int tex_id);
	void NextStep(int x, int y, int*map);
	int Logic(int x, int y,int posx, int posy);
};

