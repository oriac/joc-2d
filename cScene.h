#pragma once

#include "cTexture.h"

#define SCENE_Xo		(4*TILE_SIZE)
#define SCENE_Yo		TILE_SIZE
#define SCENE_WIDTH		32
#define SCENE_HEIGHT	128

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		16
#define BLOCK_SIZE		24

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);
	void Draw2(int tex_id);
	int *GetMap();
	void Scroll(int i);
	void ResetCam();
	int getDesp();
private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int id_DL;								//actual level display list
	int desplazament;
};
