#include "item.h"


item::item(void)
{
}


item::~item(void)
{
}

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