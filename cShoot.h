#pragma once
#include "cBicho.h"
//#include "cScene.h"

#define STEP_LENGTH		8

class cShoot : public cBicho
{
public:
	cShoot(void);
	~cShoot(void);
	void Draw(int tex_id);
	//void MoveLeft(int *map);
	//void MoveRight(int *map);
};

