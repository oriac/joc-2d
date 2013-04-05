#include <queue>
#include <vector>
#include "cEnemy.h"
using namespace std;
cEnemy::cEnemy() 
{
}
cEnemy::~cEnemy(){}
void cEnemy::Init(bool ismelee, vector<Point> pat)
{

	this->patrulla = pat;
	this->melee = ismelee;
	this->PointActual = 0;
	alive = false;
	explote = false;
}
void cEnemy::Draw(int tex_id)
{	
	float xo,yo,xf,yf;

	switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	xo = 0.25f;	yo = 0.5f;
								break;
		//4
		case STATE_LOOKRIGHT:	xo = 0.25f;	yo = 0.75f;
								break;
		//1..3
		case STATE_WALKLEFT:	xo = 0.0f + (GetFrame()*0.25f);	yo = 0.5f ;
								NextFrame(3);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo = 0.0f+ (GetFrame()*0.25f); yo = 0.75f ;
								NextFrame(3);
								break;
		case STATE_LOOKUP:		xo = 0.25f;	yo = 1.0f;
								break;
		case STATE_WALKUP:		xo = 0.0f + (GetFrame()*0.25f); yo = 1.0;
								NextFrame(3);
								break;
		case STATE_WALKDOWN:	xo = 0.0f + (GetFrame()*0.25f); yo = 0.25f;
								NextFrame(3);
								break;
		
			//4						
		case STATE_LOOKDOWN:	xo = 0.25f;	yo = 0.25f;
								break;
		case STATE_SHOOT_LEFT:	xo = 0.25f; yo = 0.5f;
								break;
		case STATE_SHOOT_RIGHT: xo = 0.25f; yo = 0.75f;
								break;
		case STATE_DUPLEFT:		xo = 0.0f + (GetFrame()*0.25f); yo = 1.0;
								NextFrame(3);
								break;
		case STATE_DUPRIGHT:	xo = 0.0f + (GetFrame()*0.25f); yo = 1.0;
								NextFrame(3);
								break;
		case STATE_DDOWNLEFT:	xo = 0.0f + (GetFrame()*0.25f); yo = 0.25f;
								NextFrame(3);
								break;
		case STATE_DDOWNRIGHT:	xo = 0.0f + (GetFrame()*0.25f); yo = 0.25f;
								NextFrame(3);
								break;
		case STATE_EXPLOTE:	xo = 0.75f; yo = 0.25f + (GetFrame()*0.25f);
								if (yo == 1.0f) explote = false;
								NextFrame(4);
								break;
	}
	xf = xo + 0.25f;
	yf = yo - 0.25f;

	DrawRect(tex_id,xo,yo,xf,yf);
}

bool cEnemy::IsAlive()
{
	return alive;
}

void cEnemy::Active()
{
	alive = true;
}

bool cEnemy::IsExplote()
{
	return explote;
}

void cEnemy::kill()
{
	explote = true;
	alive = false;
	cBicho::SetState(STATE_EXPLOTE);
}

int cEnemy::CaulculStep(int x, int y) {
	switch (x){
		case 1:
			{
				switch (y){
					case 0:
						return 0;
						break;
					case 1:
						return 2;
						break;
					case -1:
						return 3;
						break;
				}
			}
			break;
		case -1:
			{
				switch (y){
					case 0:
						return 1;
						break;
					case 1:
						return 2;
						break;
					case -1:
						return 3;
						break;
				}
			}
			break;
		case 0:
			{
				switch (y) {
					case -1:
						return 3;
						break;
					case 1:
						return 2;
						break;
				}
			}
			break;
		}
	return -1;
}

int cEnemy::NextStep(int x, int y, int*map) {
	int posx,posy;
	int nx,ny;
	Estado actual;
	cBicho::GetTile(&posx,&posy);
	actual = Logic(x,y,posx,posy, map);
	if (actual.dist != -1) {
		nx = actual.nextx - posx;
		ny = actual.nexty - posy;
	}
	if (actual.dist > 0 ) {
		return this->CaulculStep(nx,ny);
	}
	else {
		return -1;
	}
}

Estado cEnemy::Logic(int x, int y,int posx, int posy, int * map)
{
	int auxx,auxy,nx,ny;
	bool collides;
	cBicho::GetPosition(&auxx, &auxy);
    Estado vec1, adyacente, actual;
	vec1.x = posx;
	vec1.y = posy;
	vec1.dist = 0;
	vec1.nextx = -1;
	vec1.nexty = -1;
    queue <Estado > vecinos;
    vecinos.push(vec1);
    vector< vector<int> > visitados(32,vector<int> (128,0));
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
	bool primer = true;
    while( ! vecinos.empty() ){
            actual = vecinos.front();
            vecinos.pop();
            if(actual.x == x && actual.y == y) {
				cBicho::SetPosition(auxx,auxy);
				return actual;
            }
            visitados[actual.x][actual.y]=1;
            for( int k = 0; k < 4; ++k) {
				collides = false; 
                nx = dx[k] + actual.x;
                ny = dy[k] + actual.y;
				if (nx < 32 && nx >= 0 && ny >=0 && ny < 128 && actual.dist < 50) {
                    if (visitados[nx][ny] !=1 ) {
						cBicho::SetTile(actual.x,actual.y);
						switch (k) {
							case 0: collides = cBicho::CollidesWall(map,false);
									break;
							case 1: collides = cBicho::CollidesWall(map,true);
									break;
							case 2: collides = cBicho::CollidesTopBot(map,false);
									break;
							case 3: collides = cBicho::CollidesTopBot(map,true);
									break;
						}
						if ( !collides ) {
                            adyacente.x = nx;
                            adyacente.y = ny;
							adyacente.dist = actual.dist+1;
							if (primer) {
								adyacente.nextx = nx;
								adyacente.nexty = ny;
							}
							else {
								adyacente.nextx = actual.nextx;
								adyacente.nexty = actual.nexty;
							}
                            vecinos.push(adyacente);
                            visitados[nx][ny] = 1;
						}
                    }
                }
            }
			primer = false;
    }
	cBicho::SetPosition(auxx,auxy);
	Estado aux;
	aux.dist = -1;
    return aux;
}

void cEnemy::SetStep(int x, int y, int * map)
{
int posEx, posEy;
	GetPosition(&posEx,&posEy);
	if (posEx % 16 == 0 && posEy % 16 == 0) {
		if ( this->melee) nextStep = (NextStep(x,y,map));
		else {
			int tilex, tiley;
			this->GetTile(&tilex,&tiley);
			int n = this->patrulla.size();
			if (PointActual < n - 1 && tilex == this->patrulla[PointActual].tilex && tiley == this->patrulla[PointActual].tiley) 
				this->PointActual++;
			else if (tilex == this->patrulla[patrulla.size() - 1].tilex && tiley == this->patrulla[patrulla.size() - 1].tiley) 
				this->PointActual = 0;
			nextStep = this->NextStep(patrulla[this->PointActual].tilex,patrulla[this->PointActual].tiley,map);
			
		}
	}
		switch (nextStep) {
			case -1:
				Stop();
				break;
			case 0:
				MoveRight(map);
				break;
			case 1:
				MoveLeft(map);
				break;
			case 2:
				MoveUp(map);
				break;
			case 3:
				MoveDown(map);
				break;
		}
}

int cEnemy::GetStep()
{
	return this->nextStep;
}
