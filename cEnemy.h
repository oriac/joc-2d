#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

    typedef struct {
            int x;
            int y;
			int dist;
			int nextx;
			int nexty;
    } Estado;
class cEnemy: public cBicho
{
public:
	cEnemy();
	~cEnemy();
	int GetStep();
	void SetStep(int x, int y, int * map);
	void Draw(int tex_id);
	int NextStep(int x, int y, int*map);
	Estado Logic(int x, int y,int posx, int posy, int* map);
	void kill();
	bool IsAlive();
private:
	bool alive;
	int nextStep;
};

