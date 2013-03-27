
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
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
		case STATE_DUPLEFT:		xo = 0.50f;	yo = 0.25f;
								break;
		case STATE_DUPRIGHT:	xo = 0.50f;	yo = 0.25f;
								break;
		case STATE_DDOWNLEFT:	xo = 0.50f;	yo = 0.50f;
								break;
		case STATE_DDOWNRIGHT:	xo = 0.50f;	yo = 0.50f;
								break;
	}
	xf = xo + 0.25f;
	yf = yo - 0.25f;

	DrawRect(tex_id,xo,yo,xf,yf);
}
