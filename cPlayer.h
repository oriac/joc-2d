#pragma once

#include "cBicho.h"
#include <sstream>
#include <string>

using namespace std;

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);
	int GetHp();
	void LoseHp();
	bool isAlive();
	void AddPoints(int punts);
	void Dead();
	void Respawn();
	bool IsExplote();
	string GetPoints();
private:
	bool explote;
	int hp;
	int alive;
	int points;
};
