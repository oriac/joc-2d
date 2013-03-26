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
	collide = false;
	for (int i = 0; i < 100; ++i) {
		Disparo[i] = false;
	}
	//Disparo = false;
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

	//Enemy initialization

	if(!res) return false;
	Enemy.SetWidthHeight(32,32);
	Enemy.SetTile(4,1);


	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"bub.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BULLET,"bullet3.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(32,32);
	Player.SetSpeed(1);
	Player.SetTile(4,1);
	shootCount = 0;
	startCd = -500;
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
		int x,y;
		Player.GetPosition(&x,&y);
		if(y-Scene.getDesp() > GAME_WIDTH/3 ) Scene.Scroll(2);
	}
	if(keys[GLUT_KEY_LEFT]) {
		Player.MoveLeft(Scene.GetMap());
		
	}
	if(keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
	if(keys[GLUT_KEY_DOWN]) {
		Player.MoveDown(Scene.GetMap());
		int x,y;
		Player.GetPosition(&x,&y);
		if(y-Scene.getDesp() < GAME_WIDTH/5 ) Scene.Scroll(-2);
	}
	if (keys[GLUT_KEY_F1])		{
		
		endCd = glutGet(GLUT_ELAPSED_TIME);
		shootCd = endCd - startCd;
		if(shootCd > 250) {
			startCd = glutGet(GLUT_ELAPSED_TIME);
		
			int x;
			int y;
			Player.Shoot(Scene.GetMap());
			Player.GetTile(&x,&y);
			//bool pState = Player.GetState();
			if(Player.GetState() == STATE_WALKLEFT||Player.GetState() == STATE_LOOKLEFT||Player.GetState() == STATE_SHOOT_LEFT)
				Shoot[shootCount].SetTile(x-1,y);
			else if(Player.GetState() == STATE_LOOKUP)
				Shoot[shootCount].SetTile(x,y+2);
			else if(Player.GetState() == STATE_LOOKDOWN)
				Shoot[shootCount].SetTile(x,y-1);
			else
				Shoot[shootCount].SetTile(x+2,y);
			Shoot[shootCount].SetWidthHeight(32,32);
			Shoot[shootCount].SetState(Player.GetState());
			Shoot[shootCount].SetSpeed(2);
			Disparo[shootCount] = true;
			shootCount = (shootCount+1)%100;
			
		}
		//Shoot.MoveLeft(Scene.GetMap());
	}
	else Player.Stop();
	
	
	//Game Logic
	Player.Logic(Scene.GetMap());
	for(int i=0;i<100;i++) {
		if (Disparo[i] == true) {
			int shootState = Shoot[i].GetState(); 
			switch (shootState) {
				case STATE_SHOOT_LEFT:
					Shoot[i].MoveLeft(Scene.GetMap());
					break;
				case STATE_SHOOT_RIGHT:
					Shoot[i].MoveRight(Scene.GetMap());
					break;
				case STATE_WALKLEFT:
					Shoot[i].MoveLeft(Scene.GetMap());					
					break;
				case STATE_WALKRIGHT:
					Shoot[i].MoveRight(Scene.GetMap());
					break;
				case STATE_LOOKLEFT:
					Shoot[i].MoveLeft(Scene.GetMap());
					break;
				case STATE_LOOKRIGHT:
					Shoot[i].MoveRight(Scene.GetMap());
					break;
				case STATE_LOOKUP:
					Shoot[i].MoveUp(Scene.GetMap());
					break;
				case STATE_LOOKDOWN:
					Shoot[i].MoveDown(Scene.GetMap());
					break;
			}
			//Shoot[i].MoveLeft(Scene.GetMap());
			if(shootState == STATE_SHOOT_RIGHT||shootState == STATE_WALKRIGHT||shootState == STATE_LOOKRIGHT)
				Disparo[i] = !Shoot[i].CollidesWall(Scene.GetMap(),true);
			else if(shootState == STATE_LOOKUP)
				Disparo[i] = !Shoot[i].CollidesTopBot(Scene.GetMap(),true);
			else if(shootState == STATE_LOOKDOWN)
				Disparo[i] = !Shoot[i].CollidesTopBot(Scene.GetMap(),false);
			else Disparo[i] = !Shoot[i].CollidesWall(Scene.GetMap(),false);
			
			
			//Disparo[i] = !Shoot[i].CollidesWall(Scene.GetMap());
			cRect pos;
			if(!collide) {
				Enemy.GetArea(&pos);
				if(Shoot[i].Collides2(&pos)) {
					collide = true;
					Disparo[i]=false;
				}
			}
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
	
	cRect pos2;
	//collide = false;
	Player.GetArea(&pos2);
	for(int i=0;i<100;i++) {
		if(Disparo[i]) {
			Shoot[i].Draw(Data.GetID(IMG_BULLET));
		}
	
	}

	if (!collide) Enemy.Draw(Data.GetID(IMG_PLAYER));
	glutSwapBuffers();
}
