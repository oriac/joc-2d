#include "cGame.h"
#include "Globals.h"


cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

void cGame::NextLevel() {
	//PlaySound("ff7.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	Sleep(6000);
	if (ActualLevel ==1) {
		++ActualLevel;
		Sound.PlaySound("ff7.wav",true);
		for (int i = 0; i < 4; ++i) {
			if (i ==0) Item[i].SetTile(23,27);
			else if (i ==1) Item[i].SetTile(15,65);
			else if (i ==2) Item[i].SetTile(26,91);
			else Item[i].SetTile(13,115);
			Item[i].SetActive(true);
		}
		Player.SetTile(4,1);
		Player2.SetTile(7,1);
	}
	else if (ActualLevel == 2 && Player.isAlive() && Player2.isAlive()) {
		Sound.PlaySoundA("pvp.mp3",true);
		ActualLevel = 3;
		for (int i = 0; i < 4; ++i) {
			if (i ==0) Item[i].SetTile(17,16);
			else if (i ==1) Item[i].SetTile(13,16);
			else if (i ==2) Item[i].SetTile(3,3);
			else Item[i].SetTile(27,3);
			Item[i].SetActive(true);
		}
		Player.SetTile(8,20);
		Player2.SetTile(22,20);
	}
	else if(ActualLevel == 2) {
		ActualLevel =1;
		this->Init();
	}
	bool result = false;
	result = Scene.LoadLevel(ActualLevel);	
	Scene.ResetCam();
	if (ActualLevel == 3) Scene.Scroll(80);

	vector<Point> pat (4);
	for (int i = 0; i < 10; ++i) {
		Enemy[i].Init(true, pat);
		Enemy[i].SetWidthHeight(32,32);
		if (i < 5) Enemy[i].SetTile((i*4)%32,36);
		else Enemy[i].SetTile((i*2)%32,72);
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
	}
	firstPatrol = false;
	firstTrap = false;
	secondPatrol = false;
		//Shoots init
	for (int i = 0; i < 100; ++i) {
		Shoot[i].SetWidthHeight(16,16);
		Shoot[i].SetSpeed(2);
		Shoot[i].SetActive(false);
	}
	for (int i = 0; i < 100; ++i) {
		Shoot2[i].SetWidthHeight(16,16);
		Shoot2[i].SetSpeed(2);
		Shoot2[i].SetActive(false);
	}
	for (int i = 0; i < 500; ++i) {
		EnemyShoot[i].SetWidthHeight(16,16);
		EnemyShoot[i].SetSpeed(2);
		EnemyShoot[i].SetActive(false);
	}
	shootCount = 0;
	shootCount2 = 0;
	enemyShootCount = 0;
}

bool cGame::Init()
{
	ActualLevel = 1;
	//PlaySound("ff6.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP|SND_NOSTOP);
	Sound.PlaySound("ff6.wav",true);
	Scene.ResetCam();
	bool res=true;
	startTime = glutGet(GLUT_ELAPSED_TIME);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	red = 1.0f;
	res = Data.LoadImage(IMG_HEART,"heart2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_FONT,"font.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL01,"maptest.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL01_2,"map1_2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL02,"map2_1.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL02_2,"map2_2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL03,"map3.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BLOCKS,"blocks.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BLUEHEART,"blueheart.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_ARMOR,"armadura.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_PLAYERARMOR,"playerfullArmor.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_NAKEDPLAYER,"nakedPlayer.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;
	res = Data.LoadImage(IMG_PLAYER2ARMOR,"player2fullArmor.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_NAKEDPLAYER2,"nakedPlayer2.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);


	//Item init

	for (int i = 0; i < 4; ++i) {
		if (i ==0) Item[i].SetTile(24,41);
		else if (i ==1) Item[i].SetTile(24,65);
		else if (i ==2) Item[i].SetTile(6,97);
		else Item[i].SetTile(16,120);
		//Item[i].SetTile(i*2+4, 7);
		Item[i].SetActive(true);
		Item[i].SetWidthHeight(32,32);
	}

	//Enemy initialization

	res = Data.LoadImage(IMG_ENEMY2,"enemy2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_ENEMY,"enemy.png",GL_RGBA);
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
		//Enemy2[i].kill();
		//if ( i <= 2) Enemy2[i].Active();
	}
	firstPatrol = false;
	firstTrap = false;
	secondPatrol = false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"player.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_PLAYER2,"player2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BULLET,"bullet3.png",GL_RGBA);
	if(!res) return false;
	Player.Respawn();
	Player.SetWidthHeight(32,32);
	Player.SetSpeed(1);
	Player.SetTile(4,1);
	shootCount = 0;
	startCd = -500;
	//Player.SetWidthHeight(32,32);
	Player.SetState(STATE_LOOKRIGHT);

	if(p2IsPlaying)Player2.Respawn();
	//else Player2.Dead();
	Player2.SetWidthHeight(32,32);
	Player2.SetSpeed(1);
	Player2.SetTile(16,1);
	//shootCount = 0;
	//startCd = -500;
	//Player.SetWidthHeight(32,32);
	Player2.SetState(STATE_LOOKRIGHT);
	//Player2.Dead();
	collide = false;
	
	//Shoots init
	for (int i = 0; i < 100; ++i) {
		Shoot[i].SetWidthHeight(16,16);
		Shoot[i].SetSpeed(2);
		Shoot[i].SetActive(false);
	}
	for (int i = 0; i < 100; ++i) {
		Shoot2[i].SetWidthHeight(16,16);
		Shoot2[i].SetSpeed(2);
		Shoot2[i].SetActive(false);
	}
	for (int i = 0; i < 500; ++i) {
		EnemyShoot[i].SetWidthHeight(16,16);
		EnemyShoot[i].SetSpeed(2);
		EnemyShoot[i].SetActive(false);
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
	keys[key] = true;
	keysReleased[key] = false;
}

void cGame::ReadKeyboardSpecial(unsigned char key, int x, int y, bool press)
{
	keysSpecial[key] = true;
	keysSpecialReleased[key] = false;
}

void cGame::ReadKeyboardRelease(unsigned char key, int x, int y, bool press)
{
	keys[key] = false;
	keysReleased[key] = true;
}

void cGame::ReadKeyboardSpecialRelease(unsigned char key, int x, int y, bool press)
{
	keysSpecial[key] = false;
	keysSpecialReleased[key] = true;
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
	
	Sound.Update();
	//Process Input
	if(keys[27])	res=false;
	if(Player.isAlive()) {
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
		if (keysSpecial[GLUT_KEY_INSERT]) {
		
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
				if(Shoot[shootCount].IsActive())Sound.PlaySound("shoot.wav",false);
				shootCount = (shootCount+1)%100;
				//PlaySound("shoot.wav", NULL, SND_ASYNC|SND_FILENAME|SND_NOSTOP);
				
			
			}
		}
	}
	if(keysSpecialReleased[GLUT_KEY_UP]) {
		keysSpecialReleased[GLUT_KEY_UP] = false;
		if(Player.GetState() == STATE_DUPLEFT) Player.SetState(STATE_WALKLEFT);
		else if(Player.GetState() == STATE_DUPRIGHT) Player.SetState(STATE_WALKRIGHT);
	}
	else if(keysSpecialReleased[GLUT_KEY_DOWN]) {
		keysSpecialReleased[GLUT_KEY_DOWN] = false;
		if(Player.GetState() == STATE_DDOWNLEFT) Player.SetState(STATE_WALKLEFT);
		else if(Player.GetState() == STATE_DDOWNRIGHT) Player.SetState(STATE_WALKRIGHT);
	}
	else if(keysSpecialReleased[GLUT_KEY_RIGHT]) {
		keysSpecialReleased[GLUT_KEY_RIGHT] = false;
		if(Player.GetState() == STATE_DUPRIGHT) Player.SetState(STATE_WALKUP);
		else if(Player.GetState() == STATE_DDOWNRIGHT) Player.SetState(STATE_WALKDOWN);
	}
	else if(keysSpecialReleased[GLUT_KEY_LEFT]) {
		keysSpecialReleased[GLUT_KEY_LEFT] = false;
		if(Player.GetState() == STATE_DDOWNLEFT) Player.SetState(STATE_WALKDOWN);
		else if(Player.GetState() == STATE_DUPLEFT) Player.SetState(STATE_WALKUP);
	}


	//input Player2
	if(Player2.isAlive()) {
		if(keys[119]||keys[120]||keys[97]||keys[100]) {
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
				if(Shoot2[shootCount2].IsActive())Sound.PlaySound("shoot.wav",false);
				shootCount2 = (shootCount2+1)%100;
			}
		}
	}
	if(keysReleased[119]) {
		keysReleased[119] = false;
		if(Player2.GetState() == STATE_DUPLEFT) Player2.SetState(STATE_WALKLEFT);
		else if(Player2.GetState() == STATE_DUPRIGHT) Player2.SetState(STATE_WALKRIGHT);
	}
	else if(keysReleased[120]) {
		keysReleased[120] = false;
		if(Player2.GetState() == STATE_DDOWNLEFT) Player2.SetState(STATE_WALKLEFT);
		else if(Player2.GetState() == STATE_DDOWNRIGHT) Player2.SetState(STATE_WALKRIGHT);
	}
	else if(keysReleased[100]) {
		keysReleased[100] = false;
		if(Player2.GetState() == STATE_DUPRIGHT) Player2.SetState(STATE_WALKUP);
		else if(Player2.GetState() == STATE_DDOWNRIGHT) Player2.SetState(STATE_WALKDOWN);
	}
	else if(keysReleased[97]) {
		keysReleased[97] = false;
		if(Player2.GetState() == STATE_DDOWNLEFT) Player2.SetState(STATE_WALKDOWN);
		else if(Player2.GetState() == STATE_DUPLEFT) Player2.SetState(STATE_WALKUP);
	}
	if (keysSpecial[GLUT_KEY_F9]) Init();
	if (keysSpecial[GLUT_KEY_F2]) {
		if(!p2IsPlaying && Player.GetHp()>0) {
			p2IsPlaying = true;
			Player.GetTile(&x,&y);
			Player2.SetTile(x,y);
			Player2.Respawn();
		}
	}
	//Scroll
	int x1,y1;
	Player.GetPosition(&x1,&y1);
	int x2,y2;
	Player2.GetPosition(&x2,&y2);
	if(ActualLevel!=3) {
		if (Player.GetHp()>0 && Player2.GetHp()>0) {
			if(y1-Scene.getDesp() > GAME_HEIGHT/3 && y2-Scene.getDesp() > GAME_HEIGHT/3) Scene.Scroll(2);
			else if(y1-Scene.getDesp() < GAME_HEIGHT/5 && y2-Scene.getDesp() < GAME_HEIGHT/5) Scene.Scroll(-2);
		}
		else if(Player2.GetHp() <= 0 && Player.GetHp() <= 0);
		else if(Player2.GetHp() <= 0) {
			if(y1-Scene.getDesp() > GAME_HEIGHT/3) Scene.Scroll(2);
			else if(y1-Scene.getDesp() < GAME_HEIGHT/5) Scene.Scroll(-2);
		}
		else if (Player.GetHp() <= 0) {
			if(y2-Scene.getDesp() > GAME_HEIGHT/3) Scene.Scroll(2);
			else if(y2-Scene.getDesp() < GAME_HEIGHT/5) Scene.Scroll(-2);
		}
	}
	
	
	//Enemy Logic
	Player.GetTile(&x,&y);
	Player2.GetTile(&x2,&y2);
	if ( Scene.getDesp() > 800-80  && !this->firstTrap) {
			firstTrap = true;
			for ( int i = 0; i < 10; ++i) {
				Enemy[i].Active();
			}
	}
	if ( Scene.getDesp() > 1440-80 && !this->secondPatrol) {
		for ( int i = 5; i < 10; ++i) {
				Enemy2[i].Active();
				Enemy[i].Active();
				//if ( i > 2 &&  i < 5) Enemy2[i].Active();
		}
		secondPatrol = true;
	}
	if ( Scene.getDesp() > 320-80 && !this->firstPatrol) {
		for ( int i = 0; i < 5; ++i) {
				Enemy2[i].Active();
				//if ( i > 2 &&  i < 5) Enemy2[i].Active();
		}
		firstPatrol = true;
	}

	for (int i = 0; i < 10; ++i) {
		if(Enemy[i].IsAlive() && Player.isAlive()) {
			//cRect pos;
			Player.GetArea(&pos);
			if(Enemy[i].Collides2(&pos)) {
				Enemy[i].kill();
				Player.LoseHp();
				Sound.PlaySound("explosion.aiff",false,0.4);
			}

		}
		if(Enemy[i].IsAlive() && Player2.isAlive()) {
			//cRect pos;
			Player2.GetArea(&pos);
			if(Enemy[i].Collides2(&pos)) {
				Enemy[i].kill();
				Player2.LoseHp();
				Sound.PlaySound("explosion.aiff",false,0.4);
			}

		}
		if (Enemy[i].IsAlive() && Player.isAlive() && Player2.isAlive() && i%2 == 0) Enemy[i].SetStep(x,y,Scene.GetMap());
		else if (Enemy[i].IsAlive() && Player.isAlive() && Player2.isAlive() && i%2 != 0) Enemy[i].SetStep(x2,y2,Scene.GetMap());
		else if (Enemy[i].IsAlive() && Player.isAlive() && !Player2.isAlive() ) Enemy[i].SetStep(x,y,Scene.GetMap());
		else if (Enemy[i].IsAlive() && !Player.isAlive() && Player2.isAlive() ) Enemy[i].SetStep(x2,y2,Scene.GetMap());
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
				Sound.PlaySound("explosion.aiff",false,0.4);
			}

		}
		if(Enemy2[i].IsAlive()) {
			//cRect pos;
			Player2.GetArea(&pos);
			if(Enemy2[i].Collides2(&pos)) {
				Enemy2[i].kill();
				Player2.LoseHp();
				Sound.PlaySound("explosion.aiff",false,0.4);
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
					if(EnemyShoot[enemyShootCount].IsActive())Sound.PlaySound("laserEnemy.wav",false,0.1);
					enemyShootCount = (enemyShootCount+1)%500;
					
				}
		}
	}

	//Game Logic
	if (Scene.getDesp()>=1800) {
		Sound.PlaySound("Victory.ogg",true);
		this->NextLevel();
	}
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
						Player.AddPoints(1000);
						muerte = true;
						Sound.PlaySound("explosion.aiff",false,0.4);
					}
				}
			}
			muerte = false;
			for (int j = 0; j < 10 && !muerte; ++j) {
				if(Enemy2[j].IsAlive()) {
					//Enemy.GetArea(&pos);
					Shoot[i].GetArea(&pos);
					//if(Shoot[i].Collides(&pos)) {
					if(Enemy2[j].Collides2(&pos)) {
						Enemy2[j].kill();
						Player.AddPoints(1000);
						Shoot[i].SetActive(false);
						muerte = true;
						Sound.PlaySound("explosion.aiff",false,0.4);
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
			for (int j = 0; j < 10 && !muerte; ++j) {
				if(Enemy[j].IsAlive() ) {
					//Enemy.GetArea(&pos);
					Shoot2[i].GetArea(&pos);
					//if(Shoot[i].Collides(&pos)) {
					if(Enemy[j].Collides2(&pos)) {
						Enemy[j].kill();
						Shoot2[i].SetActive(false);
						Player.AddPoints(1000);
						muerte = true;
						Sound.PlaySound("explosion.aiff",false,0.4);
					}
				}
			}
			muerte = false;
			for (int j = 0; j < 10 && !muerte; ++j) {
				if(Enemy2[j].IsAlive()) {
					//Enemy.GetArea(&pos);
					Shoot2[i].GetArea(&pos);
					//if(Shoot[i].Collides(&pos)) {
					if(Enemy2[j].Collides2(&pos)) {
						Enemy2[j].kill();
						Shoot2[i].SetActive(false);
						Player.AddPoints(1000);
						muerte = true;
						Sound.PlaySound("explosion.aiff",false,0.4);
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
			if(Player.isAlive() && Player.Collides2(&pos)) {
				EnemyShoot[i].SetActive(false);
				if(Player.GetHp()>3)Sound.PlaySound("hurtArmor.ogg",false,2.0);
				else Sound.PlaySound("hurt2.wav",false,0.5);
				Player.LoseHp();
			}
		}
		if(EnemyShoot[i].IsActive()) {
			EnemyShoot[i].GetArea(&pos);
			if(Player2.isAlive() && Player2.Collides2(&pos)) {
				EnemyShoot[i].SetActive(false);
				if(Player2.GetHp()>3)Sound.PlaySound("hurtArmor.ogg",false,2.0);
				else Sound.PlaySound("femHurt.mp3",false,0.5);
				Player2.LoseHp();
			}
		}
	}

	if (Player.isAlive()) {
		Player.GetArea(&pos);
		for (int i = 0; i < 4; i++) {
			if (Item[i].IsActive() && Item[i].Collides2(&pos)) {
				Item[i].SetActive(false);
				Player.WinHp();
				Sound.PlaySound("Powerup.ogg",false);
			}
		}
		if (ActualLevel == 3) {
			for (int i = 0; i < 100; i++) {
				if (Shoot2[i].IsActive() && Shoot2[i].Collides2(&pos)) {
					Player.LoseHp();
					Shoot2[i].SetActive(false);
					if(Player.GetHp()>3)Sound.PlaySound("hurtArmor.ogg",false,2.0);
					else Sound.PlaySound("hurt2.wav",false,0.5);
				}
			}
		}
	}

	if (Player2.isAlive()) {
		Player2.GetArea(&pos);
		for (int i = 0; i < 4; i++) {
			if (Item[i].IsActive() && Item[i].Collides2(&pos)) {
				Item[i].SetActive(false);
				Player2.WinHp();
				Sound.PlaySound("Powerup.ogg",false);
			}
		}
		if (ActualLevel == 3) {
			for (int i = 0; i < 100; i++) {
				if (Shoot[i].IsActive() && Shoot[i].Collides2(&pos)) {
					Shoot[i].SetActive(false);
					Player2.LoseHp();
					if(Player2.GetHp()>3)Sound.PlaySound("hurtArmor.ogg",false,2.0);
					else Sound.PlaySound("femHurt.mp3",false,0.5);
				}
			}
		}
	}

	if(Player.GetHp() <= 0 && Player.isAlive()) {
		Player.Dead();
		//Player.SetTile(4,1);
	}
	if(Player2.GetHp() <= 0 && Player2.isAlive() ) {
		Player2.Dead();
		//Player2.SetTile(16,1);
	}
	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	if(Player.GetHp()<=0 && Player2.GetHp()<=0) {
		glColor3f(1.0f,red,red);
		if(red >= 0.0f)red -= 0.005;
	}
	// Draw Scena
	if ( ActualLevel == 1) Scene.Draw(Data.GetID(IMG_LEVEL01));
	else if (ActualLevel == 2)  Scene.Draw(Data.GetID(IMG_LEVEL02));
	else Scene.Draw2(Data.GetID(IMG_LEVEL03));
	glColor3f(1.0f,1.0f,1.0f);

	// Draw Player

	if(Player.isAlive() || Player.IsExplote()) {
		if ( Player.GetHp() > 3) Player.Draw(Data.GetID(IMG_PLAYERARMOR));
		else if ( Player.GetHp() == 1) Player.Draw(Data.GetID(IMG_NAKEDPLAYER));
		else Player.Draw(Data.GetID(IMG_PLAYER));
	}
	//glColor3f(0.0f,0.0f,1.0f);

	// Draw Player 2

	if(Player2.isAlive() || Player2.IsExplote()) {
		if ( Player2.GetHp() > 3) Player2.Draw(Data.GetID(IMG_PLAYER2ARMOR));
		else if ( Player2.GetHp() == 1) Player2.Draw(Data.GetID(IMG_NAKEDPLAYER2));
		else Player2.Draw(Data.GetID(IMG_PLAYER2));
	}
	//glColor3f(1.0f,1.0f,1.0f);
	
	//draw items

	for (int i = 0; i < 4; i++) {
		if (Item[i].IsActive()) Item[i].Draw(Data.GetID(IMG_ARMOR));
	}


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
	glColor3f(1.0f,1.0f,1.0f);
	for ( int i = 0; i < 10; ++i) {
		if (Enemy2[i].IsAlive() || Enemy2[i].IsExplote())
			Enemy2[i].Draw(Data.GetID(IMG_ENEMY2));
		if (Enemy[i].IsAlive() || Enemy[i].IsExplote())Enemy[i].Draw(Data.GetID(IMG_ENEMY));	
	}
	for(int i=0;i<500;i++) {
		if(EnemyShoot[i].IsActive()) {
			glColor3f(0.8f,0.0f,1.0f);
			EnemyShoot[i].Draw(Data.GetID(IMG_BULLET));
		}
	
	}
	glColor3f(1.0f,1.0f,1.0f);
	if(Scene.getDesp()>=1798 && ActualLevel == 1) {
		Hud.DrawLevelComplete(Data.GetID(IMG_FONT),Scene.getDesp());
	}
	else if(Scene.getDesp()>=1798 && ActualLevel == 2 && (!Player.isAlive() || !Player2.isAlive())) {
		Hud.DrawGameComplete(Data.GetID(IMG_FONT),Scene.getDesp());
	}
	else if(Scene.getDesp()>=1798 && ActualLevel == 2 && Player.isAlive() && Player2.isAlive()) {
		Hud.DrawPrepareToFight(Data.GetID(IMG_FONT),Scene.getDesp());
	}
	
	if(!p2IsPlaying) Hud.DrawPlayer2Text(Data.GetID(IMG_FONT),Scene.getDesp());
	Hud.DrawHearts(Data.GetID(IMG_HEART),Player.GetHp(),Scene.getDesp());
	Hud.DrawBlueHearts(Data.GetID(IMG_BLUEHEART),Player2.GetHp(),Scene.getDesp());
	Hud.DrawPoints(Data.GetID(IMG_FONT),Player.GetPoints(),Scene.getDesp());
	if(Player.GetHp() <= 0 && Player2.GetHp() <= 0)Hud.DrawGameOver(Data.GetID(IMG_FONT),Scene.getDesp());
	glutSwapBuffers();
}
