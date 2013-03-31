#include "cHud.h"


cHud::cHud(void)
{
}
cHud::~cHud(void)
{
}

void cHud::DrawHearts(int tex_id,int life, int d)
{	
	for(int i=0;i<life;i++) {
		glPushMatrix();
		glTranslatef(32. *i, 420+d, 0.);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,tex_id);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1); glVertex2i(16,16);
			glTexCoord2f(1,1); glVertex2i(48,16);
			glTexCoord2f(1,0); glVertex2i(48,48);
			glTexCoord2f(0,0); glVertex2i(16,48);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
/*	glPushMatrix();
	glTranslatef(32., 400+d, 0.);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1); glVertex2i(32,32);
		glTexCoord2f(1,1); glVertex2i(64,32);
		glTexCoord2f(1,0); glVertex2i(64,64);
		glTexCoord2f(0,0); glVertex2i(32,64);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);*/
}

/*void cHud::DrawLeters(int tex_id,string points, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./10.;
	ty = 1./6.;
	int n = points.size();
	for(int i=0;i<n;i++) {
		step_x = (points[i]-'a')+33;
		step_y = step_x%10;
		step_y = step_x/10;
		Draw(tex_id,tx,ty,step_x,step_y,240.+16.*i,450+d);

	}
}*/

void cHud::DrawPoints(int tex_id,string points, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./10.;
	ty = 1./6.;
	//writing punts:
	string aux = "punts";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw(tex_id,tx,ty,step_x,step_y,170.+16.*i,450+d);
	}
	Draw(tex_id,tx,ty,6,2,170+16.*5,450+d);

	n = points.size();
	for(int i=0;i<n;i++) {
		step_x = (points[i]-'0')+16;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw(tex_id,tx,ty,step_x,step_y,280.+16.*i,450+d);

	}
}

void cHud::Draw(int tex_id, float tx,float ty, int step_x,int step_y,float trans_x, float trans_y) {
			glPushMatrix();
			//glTranslatef(240.+16.*i, 450+d, 0.);
			glTranslatef(trans_x,trans_y,0.);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,tex_id);
			glBegin(GL_QUADS);
				glTexCoord2f(tx*step_x,ty*(step_y+1));		glVertex2i(0,0);
				glTexCoord2f(tx*(step_x+1),ty*(step_y+1));	glVertex2i(20,0);
				glTexCoord2f(tx*(step_x+1),ty*step_y);		glVertex2i(20,20);
				glTexCoord2f(tx*step_x,ty*step_y);			glVertex2i(0,20);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
}
