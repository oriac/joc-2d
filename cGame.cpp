#include "cGame.h"
#include "Globals.h"


cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;
	Disparo = false;
	//Graphics initialization
	startTime = glutGet(GLUT_ELAPSED_TIME);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_BLOCKS,"blocks.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"bub.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BULLET,"bullet3.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(32,32);
	Player.SetTile(4,1);
	shootCount = 0;
	//Player.SetWidthHeight(32,32);
	Player.SetState(STATE_LOOKRIGHT);

	return res;
}



bool cGame::Loop()
{
	bool res=true;
	int timePerFrame = 20;
	res = Process();
	endTime = glutGet(GLUT_ELAPSED_TIME);
	loopTime = endTime - startTime;
	startTime = glutGet(GLUT_ELAPSED_TIME);
	if (timePerFrame-loopTime >= 0) {
		Sleep(timePerFrame-loopTime);
	}
	//update(loopTime);
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	
	if(keys[GLUT_KEY_UP]) {
		Player.MoveUp(Scene.GetMap());
		Scene.Scroll(2);
	}
	if(keys[GLUT_KEY_LEFT]) {
		Player.MoveLeft(Scene.GetMap());
		
	}
	else if(keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
	else if(keys[GLUT_KEY_DOWN]) {
		Player.MoveDown(Scene.GetMap());
		Scene.Scroll(-2);
	}
	else if (keys[GLUT_KEY_F1])		{
		
		endCd = glutGet(GLUT_ELAPSED_TIME);
		shootCd = endCd - startCd;
		if(shootCd > 250) {
			startCd = glutGet(GLUT_ELAPSED_TIME);
		
			int x;
			int y;
			Player.Shoot(Scene.GetMap());
			Player.GetTile(&x,&y);
			Shoot[shootCount].SetTile(x-1,y);
			Shoot[shootCount].SetWidthHeight(32,32);
			Shoot[shootCount].SetState(STATE_LOOKRIGHT);
			shootCount = (shootCount+1)%100;
			Disparo = true;
		}
		//Shoot.MoveLeft(Scene.GetMap());
	}
	else Player.Stop();
	
	
	//Game Logic
	Player.Logic(Scene.GetMap());
	if (Disparo) {
		for(int i=0;i<100;i++) {
			Shoot[i].MoveLeft(Scene.GetMap());
			Disparo = !Shoot[i].CollidesWall(Scene.GetMap());
		}
	}
	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

	Scene.Draw(Data.GetID(IMG_BLOCKS));
	Player.Draw(Data.GetID(IMG_PLAYER));
	if (Disparo){
		for(int i=0;i<100;i++) {
			Shoot[i].Draw(Data.GetID(IMG_BULLET));
		}
	}

	glutSwapBuffers();
}
