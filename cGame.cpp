#include "cGame.h"
#include "Globals.h"


cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

void cGame::NextLevel() {
	bool result = false;
	result = Scene.LoadLevel(2);
	Scene.ResetCam();
	Player.SetTile(4,1);
}

bool cGame::Init()
{
	bool res=true;
	
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
	res = Data.LoadImage(IMG_HEART,"heart.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_FONT,"font.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL01,"map1_1.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL01_2,"map1_2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BLOCKS,"blocks.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;

	//Enemy initialization

	if(!res) return false;
	vector<Point> pat (4);
	Enemy.Init(true, pat);
	Enemy.SetWidthHeight(32,32);
	Enemy.SetTile(30,4);
	Enemy.SetSpeed(1);
	Point p1,p2,p3,p4;
	p1.tilex = 29;
	p1.tiley = 6;
	p2.tilex = 29;
	p2.tiley= 3;
	p3.tilex = 4;
	p3.tiley = 3;
	p4.tilex = 4;
	p4.tiley = 6;
	pat[0] = p1;
	pat[1] = p2;
	pat[2] = p3;
	pat[3] = p4;
	Enemy2.Init(false,pat);
	Enemy2.SetWidthHeight(32,32);
	Enemy2.SetTile(4,6);
	Enemy2.SetSpeed(1);


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

	collide = false;
	
	//Shoots init
	for (int i = 0; i < 100; ++i) {
		Disparo[i] = false;
		Shoot[i].SetWidthHeight(16,16);
		Shoot[i].SetSpeed(2);
	}
	shootCount = 0;


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
	if(keys[GLUT_KEY_UP]||keys[GLUT_KEY_DOWN]||keys[GLUT_KEY_LEFT]||keys[GLUT_KEY_RIGHT]) {
		if(keys[GLUT_KEY_LEFT]) Player.MoveLeft(Scene.GetMap());
		if(keys[GLUT_KEY_RIGHT]) Player.MoveRight(Scene.GetMap());
		if(keys[GLUT_KEY_DOWN]) Player.MoveDown(Scene.GetMap());
		if(keys[GLUT_KEY_UP]) Player.MoveUp(Scene.GetMap());
		if(keys[GLUT_KEY_DOWN] && keys[GLUT_KEY_RIGHT]) {
			Player.SetState(STATE_DDOWNRIGHT);
		}
		else if(keys[GLUT_KEY_DOWN] && keys[GLUT_KEY_LEFT]) {
			Player.SetState(STATE_DDOWNLEFT);
		}
		if(keys[GLUT_KEY_UP] && keys[GLUT_KEY_LEFT]) {
			Player.SetState(STATE_DUPLEFT);
		}
		else if(keys[GLUT_KEY_UP] && keys[GLUT_KEY_RIGHT]) {
			Player.SetState(STATE_DUPRIGHT);
		}
	}
	else Player.Stop();
	if (keys[GLUT_KEY_F1])		{
		
		endCd = glutGet(GLUT_ELAPSED_TIME);
		shootCd = endCd - startCd;
		if(shootCd > 250) {
			startCd = glutGet(GLUT_ELAPSED_TIME);
		
			int x;
			int y;
			Player.Shoot(Scene.GetMap());
			Player.GetPosition(&x,&y);
			Shoot[shootCount].SetInitPos(Player.GetState(),x,y);
			Shoot[shootCount].SetState(Player.GetState());
			//Shoot[shootCount].SetActive(!(Shoot[shootCount].CollidesMapWall(Scene.GetMap(),false)||
		    //					Shoot[shootCount].CollidesMapFloor(Scene.GetMap())));
			Shoot[shootCount].CanShoot(Scene.GetMap(),Player);
			shootCount = (shootCount+1)%100;
			
		}
	}

	//Scroll
	int x,y;
	Player.GetPosition(&x,&y);
	if(y-Scene.getDesp() > GAME_HEIGHT/3 ) Scene.Scroll(2);
	else if(y-Scene.getDesp() < GAME_HEIGHT/5 ) Scene.Scroll(-2);
	
	
	//Enemy Logic
	Player.GetTile(&x,&y);
	if(Enemy.IsAlive()) {
		cRect pos;
		Player.GetArea(&pos);
		if(Enemy.Collides2(&pos)) {
			Enemy.kill();
			Player.LoseHp();
		}
	}
	if (Enemy.IsAlive()) Enemy.SetStep(x,y,Scene.GetMap());
	if (Enemy2.IsAlive()) Enemy2.SetStep(x,y,Scene.GetMap());

	if (y > 120) this->NextLevel();

	//Game Logic
	//Player.Logic(Scene.GetMap());
	for(int i=0;i<100;i++) {
		
		if(Shoot[i].IsActive()) {
			int shootState = Shoot[i].GetState();
			Shoot[i].ShootCollides(shootState, Scene.GetMap());
			Shoot[i].ShootStep(shootState,Scene.GetMap());
			cRect pos;
			if(Enemy.IsAlive()) {
				//Enemy.GetArea(&pos);
				Shoot[i].GetArea(&pos);
				//if(Shoot[i].Collides(&pos)) {
				if(Enemy.Collides2(&pos)) {
					Enemy.kill();
					Shoot[i].SetActive(false);
				}
			}
			if(Enemy2.IsAlive()) {
				//Enemy.GetArea(&pos);
				Shoot[i].GetArea(&pos);
				//if(Shoot[i].Collides(&pos)) {
				if(Enemy2.Collides2(&pos)) {
					Enemy2.kill();
					Shoot[i].SetActive(false);
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

	Scene.Draw(Data.GetID(IMG_LEVEL01));
	Player.Draw(Data.GetID(IMG_PLAYER));
	
	cRect pos2;
	//collide = false;
	Player.GetArea(&pos2);
	for(int i=0;i<100;i++) {
		if(Shoot[i].IsActive()) {
			Shoot[i].Draw(Data.GetID(IMG_BULLET));
		}
	
	}
	if(Enemy2.IsAlive())Enemy2.Draw(Data.GetID(IMG_PLAYER));
	if (Enemy.IsAlive())Enemy.Draw(Data.GetID(IMG_PLAYER));
	Hud.DrawHearts(Data.GetID(IMG_HEART),Player.GetHp(),Scene.getDesp());
	Hud.DrawPoints(Data.GetID(IMG_FONT),"1337",Scene.getDesp());
	glutSwapBuffers();
}
