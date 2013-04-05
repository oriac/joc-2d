#pragma once

#include "cTexture.h"
#include "Globals.h"

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_LOOKUP		4
#define STATE_LOOKDOWN		5
#define STATE_SHOOT_LEFT	6
#define STATE_SHOOT_RIGHT	7
#define STATE_DUPLEFT		8
#define STATE_DUPRIGHT		9
#define STATE_DDOWNLEFT		10
#define STATE_DDOWNRIGHT	11
#define STATE_WALKUP		12
#define STATE_WALKDOWN		13
#define STATE_EXPLOTE		14

class cRect
{
public:
	int left,top,
		right,bottom;
};

class cBicho
{
public:
	cBicho(void);
	cBicho(int x,int y,int w,int h);
	~cBicho(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x,int *y);
	void SetTile(int tx,int ty);
	void GetTile(int *tx,int *ty);
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w,int *h);

	bool Collides(cRect *rc);
	bool Collides2(cRect *rc);
	bool CollidesWall(int *map, bool right);
	bool CollidesMapWall(int *map,bool right);
	bool CollidesTopBot(int *map,bool top);
	bool CollidesMapTop(int *map);
	bool CollidesMapFloor(int *map);
	void GetArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);

	void MoveUp(int *map);
	void MoveDown(int *map);
	void MoveRight(int *map);
	void MoveLeft(int *map);
	void Shoot(int *map);
	void Jump(int *map);
	void Stop();

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

	void SetSpeed(int i);
	
private:
	int x,y;
	int w,h;
	int state;

	bool jumping;
	int jump_alfa;
	int jump_y;
	int speed;
	int seq,delay;
};
