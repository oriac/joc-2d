#pragma once
#include "cBicho.h"
#include "cScene.h"

#define STEP_LENGTH		8

class cShoot : public cBicho
{
public:
	cShoot(void);
	~cShoot(void);
	void Draw(int tex_id);
	void SetInitPos(int playerState,int x, int y);
	//void MoveLeft(int *map);
	//void MoveRight(int *map);
	bool IsActive();
	void SetActive(bool b);
	void ShootStep(int shootState,int *map);
	void ShootCollides(int shootState, int *map);
private:
	bool active;
};

