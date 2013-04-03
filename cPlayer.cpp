
#include "cPlayer.h"

cPlayer::cPlayer() {hp = 0;alive=false;points=0; explote = false;}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
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
		case STATE_EXPLOTE:		xo = 0.75f; yo = 0.25f + (GetFrame()*0.25f);
								if (yo == 1.0f) explote = false;
								NextFrame(4);
								break;
	}
	xf = xo + 0.25f;
	yf = yo - 0.25f;

	DrawRect(tex_id,xo,yo,xf,yf);
}

int cPlayer::GetHp() {
	return hp;
}

void cPlayer::WinHp() {
	hp++;
}

void cPlayer::LoseHp() {
	hp--;
}

bool cPlayer::isAlive() {
	return alive;
}
bool cPlayer::IsExplote() {
	return explote;
}
void cPlayer::AddPoints(int punts) {
	points += punts;
}

void cPlayer::Respawn() {
	hp = 3;
	alive = true;
	points = 0;
}

string cPlayer::GetPoints() {
	/*char aux[10];
	sprintf(aux,"%d",&points);
	string s(aux);
	return s;*/
	//std::string s = std::to_string(points);
	//return s;
	//int a = 10;
	stringstream ss;
	ss << points;
	return ss.str();
}

void cPlayer::Dead() {
	cBicho::SetState(STATE_EXPLOTE);
	explote = true;
	alive = false;
}