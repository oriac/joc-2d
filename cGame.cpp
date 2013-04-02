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
	PlaySound("ff7.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	bool res=true;
	this->firstTrap = false;
	bool firstPatrol = false;
	bool secondPatrol = false;
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
	res = Data.LoadImage(IMG_HEART,"heart2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_FONT,"font.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL01,"map1_1.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL01_2,"map1_2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BLOCKS,"blocks.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BLUEHEART,"blueheart.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;

	//Enemy initialization

	if(!res) return false;
	vector<Point> pat (4);
	for (int i = 0; i < 10; ++i) {
		Enemy[i].Init(true, pat);
		Enemy[i].SetWidthHeight(32,32);
		if ( i < 5) Enemy[i].SetTile((i*4)%32,36);
		else Enemy[i].SetTile((i*2)%32,76);
		Enemy[i].SetSpeed(1);

	}
	
	Point p1,p2,p3,p4;
	p1.tilex = 29;
	p1.tiley = 6;
	p2.tilex = 29;
	p2.tiley= 3;
	p3.tilex = 4;
	p3.tiley = 3;
	p4.tilex = 4;
	p4.tiley = 6;
	for ( int i = 0; i < 10; i++) {
		int aux;
		if ( i < 5 ) aux = 46;
		//else if ( i >= 2 &&  i < 5) aux = 100;
		else if ( i >= 5) aux = 120;
		p1.tiley = aux+2;
		p2.tiley = aux;
		p3.tiley = aux;
		p4.tiley = aux+2;
		pat[0] = p1;
		pat[1] = p2;
		pat[2] = p3;
		pat[3] = p4;
		Enemy2[i].Init(false,pat);
		Enemy2[i].SetWidthHeight(32,32);
		Enemy2[i].SetTile(4+(i*2),aux);
		Enemy2[i].SetSpeed(1);
		//if ( i <= 2) Enemy2[i].Active();
	}


	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"player.png",GL_RGBA);
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

	Player2.SetWidthHeight(32,32);
	Player2.SetSpeed(1);
	Player2.SetTile(16,1);
	//shootCount = 0;
	//startCd = -500;
	//Player.SetWidthHeight(32,32);
	Player2.SetState(STATE_LOOKRIGHT);

	collide = false;
	
	//Shoots init
	for (int i = 0; i < 100; ++i) {
		Shoot[i].SetWidthHeight(16,16);
		Shoot[i].SetSpeed(2);
	}
	for (int i = 0; i < 100; ++i) {
		Shoot2[i].SetWidthHeight(16,16);
		Shoot2[i].SetSpeed(2);
	}
	for (int i = 0; i < 500; ++i) {
		EnemyShoot[i].SetWidthHeight(16,16);
		EnemyShoot[i].SetSpeed(2);
	}
	shootCount = 0;
	shootCount2 = 0;
	enemyShootCount = 0;


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

void cGame::ReadKeyboardSpecial(unsigned char key, int x, int y, bool press)
{
	keysSpecial[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	int x,y;
	cRect pos;
	
	//Process Input
	if(keys[27])	res=false;
	if(keysSpecial[GLUT_KEY_UP]||keysSpecial[GLUT_KEY_DOWN]||keysSpecial[GLUT_KEY_LEFT]||keysSpecial[GLUT_KEY_RIGHT]) {
		if(keysSpecial[GLUT_KEY_LEFT]) Player.MoveLeft(Scene.GetMap());
		if(keysSpecial[GLUT_KEY_RIGHT]) Player.MoveRight(Scene.GetMap());
		if(keysSpecial[GLUT_KEY_DOWN]) {
			int x1,y1;
			Player.GetPosition(&x1,&y1);
			if(y1-Scene.getDesp() >= 0)
				Player.MoveDown(Scene.GetMap());
		}
		if(keysSpecial[GLUT_KEY_UP]) {
			int x1,y1;
			Player.GetPosition(&x1,&y1);
			if(y1-Scene.getDesp() < GAME_HEIGHT-64)
				Player.MoveUp(Scene.GetMap());
		}
		if(keysSpecial[GLUT_KEY_DOWN] && keysSpecial[GLUT_KEY_RIGHT]) {
			Player.SetState(STATE_DDOWNRIGHT);
		}
		else if(keysSpecial[GLUT_KEY_DOWN] && keysSpecial[GLUT_KEY_LEFT]) {
			Player.SetState(STATE_DDOWNLEFT);
		}
		if(keysSpecial[GLUT_KEY_UP] && keysSpecial[GLUT_KEY_LEFT]) {
			Player.SetState(STATE_DUPLEFT);
		}
		else if(keysSpecial[GLUT_KEY_UP] && keysSpecial[GLUT_KEY_RIGHT]) {
			Player.SetState(STATE_DUPRIGHT);
		}
	}
	else Player.Stop();
	if (keysSpecial[GLUT_KEY_F1]) {
		
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
	//input Player2
	if(keys[119]||keys[115]||keys[97]||keys[100]) {
		if(keys[97]) Player2.MoveLeft(Scene.GetMap());
		if(keys[100]) Player2.MoveRight(Scene.GetMap());
		if(keys[120]) {
			int x1,y1;
			Player2.GetPosition(&x1,&y1);
			if(y1-Scene.getDesp() >= 0)
				Player2.MoveDown(Scene.GetMap());
		}
		if(keys[119]) {
			int x1,y1;
			Player2.GetPosition(&x1,&y1);
			if(y1-Scene.getDesp() < GAME_HEIGHT-64)
				Player2.MoveUp(Scene.GetMap());
		}
		if(keys[120] && keys[100]) {
			Player2.SetState(STATE_DDOWNRIGHT);
		}
		else if(keys[120] && keys[97]) {
			Player2.SetState(STATE_DDOWNLEFT);
		}
		if(keys[119] && keys[97]) {
			Player2.SetState(STATE_DUPLEFT);
		}
		else if(keys[119] && keys[100]) {
			Player2.SetState(STATE_DUPRIGHT);
		}
	}
	else Player2.Stop();
	if (keysSpecial[GLUT_KEY_F4]) {
		
		end2Cd = glutGet(GLUT_ELAPSED_TIME);
		shoot2Cd = end2Cd - start2Cd;
		if(shoot2Cd > 250) {
			start2Cd = glutGet(GLUT_ELAPSED_TIME);
		
			int x;
			int y;
			Player2.Shoot(Scene.GetMap());
			Player2.GetPosition(&x,&y);
			Shoot2[shootCount2].SetInitPos(Player2.GetState(),x,y);
			Shoot2[shootCount2].SetState(Player2.GetState());
			//Shoot[shootCount].SetActive(!(Shoot[shootCount].CollidesMapWall(Scene.GetMap(),false)||
		    //					Shoot[shootCount].CollidesMapFloor(Scene.GetMap())));
			Shoot2[shootCount2].CanShoot(Scene.GetMap(),Player2);
			shootCount2 = (shootCount2+1)%100;
			
		}
	}

	//Scroll
	int x1,y1;
	Player.GetPosition(&x1,&y1);
	int x2,y2;
	Player2.GetPosition(&x2,&y2);
	if(y1-Scene.getDesp() > GAME_HEIGHT/3 && y2-Scene.getDesp() > GAME_HEIGHT/3) Scene.Scroll(2);
	else if(y1-Scene.getDesp() < GAME_HEIGHT/5 && y2-Scene.getDesp() < GAME_HEIGHT/5) Scene.Scroll(-2);
	
	
	//Enemy Logic
	Player.GetTile(&x,&y);
	if ( y > 50  && !this->firstTrap) {
			firstTrap = true;
			for ( int i = 0; i < 10; ++i) {
				Enemy[i].Active();
			}
	}
	if ( y > 90 && !this->secondPatrol) {
		for ( int i = 5; i < 10; ++i) {
				Enemy2[i].Active();
				Enemy[i].Active();
				//if ( i > 2 &&  i < 5) Enemy2[i].Active();
		}
		secondPatrol = true;
	}
	if ( y > 20 && !this->firstPatrol) {
		for ( int i = 0; i < 5; ++i) {
				Enemy2[i].Active();
				//if ( i > 2 &&  i < 5) Enemy2[i].Active();
		}
		firstPatrol = true;
	}

	for (int i = 0; i < 10; ++i) {
		if(Enemy[i].IsAlive()) {
			//cRect pos;
			Player.GetArea(&pos);
			if(Enemy[i].Collides2(&pos)) {
				Enemy[i].kill();
				Player.LoseHp();
			}

		}
		if(Enemy[i].IsAlive()) {
			//cRect pos;
			Player2.GetArea(&pos);
			if(Enemy[i].Collides2(&pos)) {
				Enemy[i].kill();
				Player2.LoseHp();
			}

		}
		if (Enemy[i].IsAlive()) Enemy[i].SetStep(x,y,Scene.GetMap());
	}
	endECd = glutGet(GLUT_ELAPSED_TIME);
	shootECd = endECd - startECd;
	for ( int i = 0; i < 10; ++i) {
		if(Enemy2[i].IsAlive()) {
			//cRect pos;
			Player.GetArea(&pos);
			if(Enemy2[i].Collides2(&pos)) {
				Enemy2[i].kill();
				Player.LoseHp();
			}

		}
		if(Enemy2[i].IsAlive()) {
			//cRect pos;
			Player2.GetArea(&pos);
			if(Enemy2[i].Collides2(&pos)) {
				Enemy2[i].kill();
				Player2.LoseHp();
			}

		}
		if (Enemy2[i].IsAlive()) {
			Enemy2[i].SetStep(x,y,Scene.GetMap());
			
				if(shootECd > 250) {
					startECd = glutGet(GLUT_ELAPSED_TIME);
		
					int x;
					int y;
					//Player.Shoot(Scene.GetMap());
					Enemy2[i].GetPosition(&x,&y);
					EnemyShoot[enemyShootCount].SetInitPos(STATE_LOOKDOWN,x,y);
					EnemyShoot[enemyShootCount].SetState(STATE_LOOKDOWN);
					//Shoot[shootCount].SetActive(!(Shoot[shootCount].CollidesMapWall(Scene.GetMap(),false)||
					//					Shoot[shootCount].CollidesMapFloor(Scene.GetMap())));
					EnemyShoot[enemyShootCount].CanShoot(Scene.GetMap(),Enemy2[i]);
					enemyShootCount = (enemyShootCount+1)%500;
				}
		}
	}

	//Game Logic
	if (y > 120) this->NextLevel();
	//Player.Logic(Scene.GetMap());
	for(int i=0;i<100;i++) {
		if(Shoot[i].IsActive()) {
			int shootState = Shoot[i].GetState();
			Shoot[i].ShootCollides(shootState, Scene.GetMap());
			Shoot[i].ShootStep(shootState,Scene.GetMap());
			//cRect pos;
			bool muerte = false;
			for (int j = 0; j < 10; ++j) {
				if(Enemy[j].IsAlive() && !muerte) {
					//Enemy.GetArea(&pos);
					Shoot[i].GetArea(&pos);
					//if(Shoot[i].Collides(&pos)) {
					if(Enemy[j].Collides2(&pos)) {
						Enemy[j].kill();
						Shoot[i].SetActive(false);
						muerte = true;
					}
				}
			}
			for (int j = 0; j < 10; ++j) {
				if(Enemy2[j].IsAlive()) {
					//Enemy.GetArea(&pos);
					Shoot[i].GetArea(&pos);
					//if(Shoot[i].Collides(&pos)) {
					if(Enemy2[j].Collides2(&pos)) {
						Enemy2[j].kill();
						Shoot[i].SetActive(false);
					}
				}
			}
		}
	}
	for(int i=0;i<100;i++) {
		if(Shoot2[i].IsActive()) {
			int shootState = Shoot2[i].GetState();
			Shoot2[i].ShootCollides(shootState, Scene.GetMap());
			Shoot2[i].ShootStep(shootState,Scene.GetMap());
			//cRect pos;
			bool muerte = false;
			for (int j = 0; j < 10; ++j) {
				if(Enemy[j].IsAlive() && !muerte) {
					//Enemy.GetArea(&pos);
					Shoot2[i].GetArea(&pos);
					//if(Shoot[i].Collides(&pos)) {
					if(Enemy[j].Collides2(&pos)) {
						Enemy[j].kill();
						Shoot2[i].SetActive(false);
						muerte = true;
					}
				}
			}
			for (int j = 0; j < 10; ++j) {
				if(Enemy2[j].IsAlive()) {
					//Enemy.GetArea(&pos);
					Shoot2[i].GetArea(&pos);
					//if(Shoot[i].Collides(&pos)) {
					if(Enemy2[j].Collides2(&pos)) {
						Enemy2[j].kill();
						Shoot2[i].SetActive(false);
					}
				}
			}
		}
	}
	for(int i=0;i<500;i++) {
		if(EnemyShoot[i].IsActive()) {
			int shootState = EnemyShoot[i].GetState();
			EnemyShoot[i].ShootCollides(shootState, Scene.GetMap());
			EnemyShoot[i].ShootStep(shootState,Scene.GetMap());
			//cRect pos;
			EnemyShoot[i].GetArea(&pos);
			if(Player.Collides2(&pos)) {
				EnemyShoot[i].SetActive(false);
				Player.LoseHp();
			}
		}
		if(EnemyShoot[i].IsActive()) {
			EnemyShoot[i].GetArea(&pos);
			if(Player2.Collides2(&pos)) {
				EnemyShoot[i].SetActive(false);
				Player2.LoseHp();
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
	glColor3f(0.0f,0.0f,1.0f);
	Player2.Draw(Data.GetID(IMG_PLAYER));
	glColor3f(1.0f,1.0f,1.0f);
	
	cRect pos2;
	//collide = false;
	//Player.GetArea(&pos2);
	for(int i=0;i<100;i++) {
		if(Shoot[i].IsActive()) {
			//glColor3f(0.0f,0.0f,1.0f);
			Shoot[i].Draw(Data.GetID(IMG_BULLET));
		}
	
	}
	for(int i=0;i<100;i++) {
		if(Shoot2[i].IsActive()) {
			glColor3f(0.0f,0.0f,1.0f);
			Shoot2[i].Draw(Data.GetID(IMG_BULLET));
		}
	
	}
	for ( int i = 0; i < 10; ++i) {
		if (Enemy2[i].IsAlive())Enemy2[i].Draw(Data.GetID(IMG_PLAYER));
		if (Enemy[i].IsAlive())Enemy[i].Draw(Data.GetID(IMG_PLAYER));	
	}
	for(int i=0;i<500;i++) {
		if(EnemyShoot[i].IsActive()) {
			glColor3f(0.8f,0.0f,1.0f);
			EnemyShoot[i].Draw(Data.GetID(IMG_BULLET));
		}
	
	}
	glColor3f(1.0f,1.0f,1.0f);
	Hud.DrawHearts(Data.GetID(IMG_HEART),Player.GetHp(),Scene.getDesp());
	Hud.DrawBlueHearts(Data.GetID(IMG_BLUEHEART),Player2.GetHp(),Scene.getDesp());
	Hud.DrawPoints(Data.GetID(IMG_FONT),"1337",Scene.getDesp());
	if(Player.GetHp() <= 0 && Player2.GetHp() <= 0)Hud.DrawGameOver(Data.GetID(IMG_FONT),Scene.getDesp());
	glutSwapBuffers();
}
