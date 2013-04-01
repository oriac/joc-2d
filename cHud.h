#pragma once

#include "cTexture.h"
#include "Globals.h"
#include <string>

using namespace std;

class cHud
{
public:
	cHud(void);
	~cHud(void);
	void DrawHearts(int tex_id,int life,int d);
	void DrawPoints(int tex_id,string Points,int d);
private:
	void Draw(int tex_id, float tx,float ty, int step_x,int step_y,float trans_x, float trans_y);
};


