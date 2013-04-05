#include "cScene.h"
#include "Globals.h"

cScene::cScene(void)
{
	desplazament = -80;
}

cScene::~cScene(void)
{
}

bool cScene::LoadLevel(int level)
{
	bool res;
	FILE *fd;
	char file[16];
	int i,j,px,py;
	char tile;
	float coordx_tile, coordy_tile;

	res=true;

	if(level<10) sprintf(file,"%s0%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);
	else		 sprintf(file,"%s%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	id_DL=glGenLists(1);
	glNewList(id_DL,GL_COMPILE);
		glBegin(GL_QUADS);
	
			for(j=SCENE_HEIGHT-1;j>=0;j--)
			{
				px=SCENE_Xo;
				py=SCENE_Yo+(j*TILE_SIZE);

				for(i=0;i<SCENE_WIDTH;i++)
				{
					fscanf(fd,"%c",&tile);
					if(tile==' ')
					{
						//Tiles must be != 0 !!!
						map[(j*SCENE_WIDTH)+i]=0;
					}
					else
					{
						//Tiles = 1,2,3,...
						map[(j*SCENE_WIDTH)+i] = tile-48;

						if(map[(j*SCENE_WIDTH)+i]%2) coordx_tile = 0.0f;
						else						 coordx_tile = 0.5f;
						if(map[(j*SCENE_WIDTH)+i]<3) coordy_tile = 0.0f;
						else						 coordy_tile = 0.5f;

						//BLOCK_SIZE = 24, FILE_SIZE = 64
						// 24 / 64 = 0.375
						glTexCoord2f(coordx_tile       ,coordy_tile+0.375f);	glVertex2i(px           ,py           );
						glTexCoord2f(coordx_tile+0.375f,coordy_tile+0.375f);	glVertex2i(px+BLOCK_SIZE,py           );
						glTexCoord2f(coordx_tile+0.375f,coordy_tile       );	glVertex2i(px+BLOCK_SIZE,py+BLOCK_SIZE);
						glTexCoord2f(coordx_tile       ,coordy_tile       );	glVertex2i(px           ,py+BLOCK_SIZE);
					}
					px+=TILE_SIZE;
				}
				fscanf(fd,"%c",&tile); //pass enter
			}

		glEnd();
	glEndList();

	fclose(fd);

	return res;
}

void cScene::Draw(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glTranslatef(0., -desplazament, 0.);
	int px, py;
	//comrpobacion de colosiones
	//glCallList(id_DL); 
	//glBindTexture(GL_TEXTURE_2D,tex_id);
	px=SCENE_Xo;
	py=SCENE_Yo+((SCENE_HEIGHT/2)*TILE_SIZE);
	glBegin(GL_QUADS);	
		glTexCoord2f(0,0);	glVertex2i(px, py);
		glTexCoord2f(1,0);	glVertex2i(px+32*16,py);
		glTexCoord2f(1,1);	glVertex2i(px+32*16,SCENE_Yo);
		glTexCoord2f(0,1);	glVertex2i(px,SCENE_Yo);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,tex_id+1);
	glBegin(GL_QUADS);	
		glTexCoord2f(0,0);	glVertex2i(px, py*2);
		glTexCoord2f(1,0);	glVertex2i(px+32*16,py*2);
		glTexCoord2f(1,1);	glVertex2i(px+32*16,py);
		glTexCoord2f(0,1);	glVertex2i(px,py);
	glEnd();
	//glBindTexture(GL_TEXTURE_2D,0);
	//glCallList(id_DL);
	
	glDisable(GL_TEXTURE_2D);
}

void cScene::Draw2(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glTranslatef(0., -desplazament, 0.);
	int px, py;
	//comrpobacion de colosiones
	//glCallList(id_DL);
	//glBindTexture(GL_TEXTURE_2D,tex_id);
	px=SCENE_Xo;
	py=SCENE_Yo+((32)*TILE_SIZE);
	glBegin(GL_QUADS);	
		glTexCoord2f(0,0);	glVertex2i(px, py);
		glTexCoord2f(1,0);	glVertex2i(px+32*16,py);
		glTexCoord2f(1,1);	glVertex2i(px+32*16,SCENE_Yo);
		glTexCoord2f(0,1);	glVertex2i(px,SCENE_Yo);
	glEnd();
	//glBindTexture(GL_TEXTURE_2D,tex_id+1);
	//glBindTexture(GL_TEXTURE_2D,0);
	//glCallList(id_DL);
	
	glDisable(GL_TEXTURE_2D);
}
int* cScene::GetMap()
{
	return map;
}

void cScene::Scroll(int i) {
	desplazament += i;
}

void cScene::ResetCam() {
	desplazament = -80;
}

int cScene::getDesp() {
	return desplazament;
}