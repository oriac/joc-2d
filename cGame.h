#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cShoot.h"
#include "cData.h"
#include "cEnemy.h"
#include "cHud.h"

#define GAME_WIDTH	640
#define GAME_HEIGHT 480

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void NextLevel();
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	cScene Scene;
	cPlayer Player;
	cShoot Shoot[100];
	cShoot EnemyShoot[500];
	cEnemy Enemy[10];
	cEnemy Enemy2[10];
	cHud Hud;
	int shootCount;
	int enemyShootCount;
	bool Disparo[100];
	bool collide;
	bool collide2;
	bool firstTrap;
	cData Data;
	int endTime;
	int startTime;
	int loopTime;
	int endCd, startCd, shootCd;
	int endECd, startECd, shootECd;
	int ActualLevel;
};
