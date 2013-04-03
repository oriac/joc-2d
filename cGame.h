#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cShoot.h"
#include "cData.h"
#include "cEnemy.h"
#include "cHud.h"
#include "cItem.h"
#include "cSound.h"

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
	void ReadKeyboardSpecial(unsigned char key, int x, int y, bool press);
	void ReadKeyboardRelease(unsigned char key, int x, int y, bool press);
	void ReadKeyboardSpecialRelease(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	unsigned char keysSpecial[256];
	unsigned char keysReleased[256];
	unsigned char keysSpecialReleased[256];
	cScene Scene;
	cPlayer Player;
	cPlayer Player2;
	cShoot Shoot[100];
	cShoot Shoot2[100];
	cShoot EnemyShoot[500];
	cEnemy Enemy[10];
	cEnemy Enemy2[10];
	cItem Item[4];
	cHud Hud;
	cSound Sound;
	int shootCount;
	int shootCount2;
	int enemyShootCount;
	bool Disparo[100];
	bool collide;
	bool collide2;
	bool firstTrap;
	bool firstPatrol;
	bool secondPatrol;
	cData Data;
	int endTime;
	int startTime;
	int loopTime;
	int endCd, startCd, shootCd;
	int end2Cd, start2Cd, shoot2Cd;
	int endECd, startECd, shootECd;
	//int 
	int ActualLevel;
	float red;
	bool p2IsPlaying;
};
