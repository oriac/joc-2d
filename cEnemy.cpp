#include <queue>
#include <vector>
#include "cEnemy.h"
using namespace std;
cEnemy::cEnemy() {}
cEnemy::~cEnemy(){}

void cEnemy::Draw(int tex_id)
{	
	float xo,yo,xf,yf;

	switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.25f;
								break;
		//4
		case STATE_LOOKRIGHT:	xo = 0.25f;	yo = 0.25f;
								break;
		//1..3
		case STATE_WALKLEFT:	xo = 0.0f;	yo = 0.25f + (GetFrame()*0.25f);
								NextFrame(3);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo = 0.25f; yo = 0.25f + (GetFrame()*0.25f);
								NextFrame(3);
								break;
		case STATE_LOOKUP:		xo = 0.50f;	yo = 0.25f;
								break;
		//4
		case STATE_LOOKDOWN:	xo = 0.50f;	yo = 0.50f;
								break;
		case STATE_SHOOT_LEFT:	xo = 0.0f; yo = 1.0f;
								break;
		case STATE_SHOOT_RIGHT: xo = 0.5f; yo = 1.0f;
								break;
	}
	xf = xo + 0.25f;
	yf = yo - 0.25f;

	DrawRect(tex_id,xo,yo,xf,yf);
}
void cEnemy::NextStep(int x, int y, int*map) {
	int posx,posy;
	int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
	int min,actual,nx,ny,mov;
	cBicho::GetTile(&posx,&posy);
	min = 100000;
	mov = -1;
	for( int k = 0; k < 4; ++k) {
			nx = dx[k];
			ny = dy[k];
			actual = Logic(x,y,posx+nx,posy+ny);
			if (actual != -1 && actual < min) {
				min = actual;
				mov = k;
			}
	}
	switch (mov) {
		case 0: 
			cBicho::MoveLeft(map);
			break;
		case 1:
			cBicho::MoveRight(map);
			break;
		case 2:
			cBicho::MoveDown(map);
			break;
		case 3:
			cBicho::MoveUp(map);
			break;
		case -1:
			cBicho::Stop();
			break;
	}

}
int cEnemy::Logic(int x, int y,int posx, int posy)
{
    Estado vec1;
	vec1.x = posx;
	vec1.y = posy;
	vec1.dist = 0;
    queue <Estado > vecinos;
    vecinos.push(vec1);
    vector< vector<int> > visitados(25,vector<int> (25,0));
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    while( ! vecinos.empty() ){
            Estado actual = vecinos.front();
            vecinos.pop();
            if(actual.x == x && actual.y == y) {
				return actual.dist;
            }
            visitados[actual.x][actual.y]=1;
            for( int k = 0; k < 4; ++k) {
                int nx = dx[k] + actual.x;
                int ny = dy[k] + actual.y;
                if (nx < 25 && nx >= 0 && ny >=0 && ny < 25) {
                    if (visitados[nx][ny] !=1) {
                            Estado adyacente;
                            adyacente.x = nx;
                            adyacente.y = ny;
							adyacente.dist = actual.dist+1;
                            vecinos.push(adyacente);
                            visitados[nx][ny] = 1;
                    }
                }
            }
            //vecinos.pop();
    }
    return -1;
}
