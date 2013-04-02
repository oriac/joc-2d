#include "cShoot.h"

cShoot::cShoot(void)
{
}


cShoot::~cShoot(void)
{
}

void cShoot::Draw(int tex_id)
{
	float xo,yo,xf,yf;
	xo = 0.0f;	yo = 0.25f;
	xf = xo + 0.25f;
	yf = yo - 0.25f;

	DrawRect(tex_id,xo,yo,xf,yf);
}

bool cShoot::IsActive() {
	return active;
}

void cShoot::SetActive(bool b) {
	active = b;
}

void cShoot::SetInitPos(int playerState,int x, int y) {
	if(playerState == STATE_WALKLEFT||playerState == STATE_LOOKLEFT||playerState == STATE_SHOOT_LEFT)
				SetPosition(x-(TILE_SIZE*2)+(x%4),y);
			else if(playerState == STATE_LOOKUP||playerState == STATE_WALKUP)
				SetPosition(x-(x%4),y+(TILE_SIZE*2)-(y%4));
			else if(playerState == STATE_LOOKDOWN||playerState == STATE_WALKDOWN)
				SetPosition(x,y-(TILE_SIZE*2)+(y%4));
			else if(playerState == STATE_WALKRIGHT||playerState == STATE_LOOKRIGHT||playerState == STATE_SHOOT_RIGHT)
				SetPosition(x+(TILE_SIZE*2)-(x%4),y);
			else if(playerState == STATE_DUPLEFT)
				SetPosition(x-(TILE_SIZE*2)+(x%4),y+(TILE_SIZE*2)-(y%4));
			else if(playerState == STATE_DUPRIGHT)
				SetPosition(x+(TILE_SIZE*2)+(x%4),y+(TILE_SIZE*2)+(y%4));
			else if(playerState == STATE_DDOWNLEFT)
				SetPosition(x-(TILE_SIZE*2)-(x%4),y-(TILE_SIZE*2)-(y%4));
			else if(playerState == STATE_DDOWNRIGHT)
				SetPosition(x+(TILE_SIZE*2)-(x%4),y-(TILE_SIZE*2)+(y%4));
}

void cShoot::ShootStep(int shootState, int *map) {
	switch (shootState) {
				case STATE_SHOOT_LEFT:
					MoveLeft(map);
					break;
				case STATE_SHOOT_RIGHT:
					MoveRight(map);
					break;
				case STATE_WALKLEFT:
					MoveLeft(map);					
					break;
				case STATE_WALKRIGHT:
					MoveRight(map);
					break;
				case STATE_LOOKLEFT:
					MoveLeft(map);
					break;
				case STATE_LOOKRIGHT:
					MoveRight(map);
					break;
				case STATE_LOOKUP:
					MoveUp(map);
					break;
				case STATE_WALKUP:
					MoveUp(map);
					break;
				case STATE_LOOKDOWN:
					MoveDown(map);
					break;
				case STATE_WALKDOWN:
					MoveDown(map);
					break;
				case STATE_DUPLEFT:
					MoveUp(map);
					MoveLeft(map);
					SetState(STATE_DUPLEFT);
					break;
				case STATE_DUPRIGHT:
					MoveUp(map);
					MoveRight(map);
					SetState(STATE_DUPRIGHT);
					break;
				case STATE_DDOWNLEFT:
					MoveDown(map);
					MoveLeft(map);
					SetState(STATE_DDOWNLEFT);
					break;
				case STATE_DDOWNRIGHT:
					MoveDown(map);
					MoveRight(map);
					SetState(STATE_DDOWNRIGHT);
					break;
			}
}

void cShoot::ShootCollides(int shootState, int *map) {
	if(shootState == STATE_SHOOT_RIGHT||shootState == STATE_WALKRIGHT||shootState == STATE_LOOKRIGHT)
		active = !CollidesWall(map,true);
	else if(shootState == STATE_LOOKUP)
		active = !CollidesTopBot(map,true);
	else if(shootState == STATE_LOOKDOWN)
		active = !CollidesTopBot(map,false);
	else if(shootState == STATE_SHOOT_LEFT||shootState == STATE_WALKLEFT||shootState == STATE_LOOKLEFT)
		active = !CollidesWall(map,false);
	else if(shootState == STATE_DUPRIGHT)
		active = !(CollidesWall(map,true)||CollidesTopBot(map,true));
	else if(shootState == STATE_DUPLEFT)
		active = !(CollidesWall(map,false)||CollidesTopBot(map,true));
	else if(shootState == STATE_DDOWNLEFT)
		active = !(CollidesWall(map,false)||CollidesTopBot(map,false));
	else if(shootState == STATE_DDOWNRIGHT)
		active = !(CollidesWall(map,true)||CollidesTopBot(map,false));
}

void cShoot::CanShoot(int *map, cBicho &Player) {
	int x,y;
	GetTile(&x,&y);
	if(map[x+(y*SCENE_WIDTH)] != 0 || map[(x+1)+(y*SCENE_WIDTH)] != 0 || map[x+((y+1)*SCENE_WIDTH)] != 0 || map[(x+1)+((y+1)*SCENE_WIDTH)] != 0) active = false;
	else active = true;
	if(active) {
		if(GetState() == STATE_SHOOT_LEFT || GetState() == STATE_LOOKLEFT || GetState() == STATE_WALKLEFT ) {
			active = !(Player.CollidesMapWall(map,false));
			if(map[(x+1)+y*SCENE_WIDTH] != 0) active = false;
			if(map[(x+2)+y*SCENE_WIDTH] != 0) active = false;
		}
		else if(GetState() == STATE_LOOKDOWN) {
			active = !(Player.CollidesTopBot(map,false));
			if(map[x+((y+1)*SCENE_WIDTH)] != 0) active = false;
		}
			//else if(map[(x+1)+((y+1)*SCENE_WIDTH)] != 0) active = false;
		else if(GetState() == STATE_LOOKUP) {
			active = !(Player.CollidesTopBot(map,true));
			//if(map[x+((y-1)*SCENE_WIDTH)] != 0) active = false;
			//if(map[(x+1)+y*SCENE_WIDTH]) active = false;
			active = !CollidesMapTop(map);
		}
		else if(GetState() == STATE_SHOOT_RIGHT || GetState() == STATE_LOOKRIGHT || GetState() == STATE_WALKRIGHT ) {
			active = !(Player.CollidesMapWall(map,true));
			if(map[(x+1)+y*SCENE_WIDTH] != 0) active = false;
			//if(map[(x+1)+y*SCENE_WIDTH] != 0) active = false;
		}
	}

}