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
		glTranslatef(0, 420+d-32*i, 0.);
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
}

void cHud::DrawBlueHearts(int tex_id,int life, int d)
{	
	for(int i=0;i<life;i++) {
		glPushMatrix();
		glTranslatef(576, 420+d - (32. *i), 0.);
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
}


void cHud::DrawPoints(int tex_id,string points, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	//writing punts:
	string aux = "punts";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw(tex_id,tx,ty,step_x,step_y,200.+16.*i,450+d);
	}
	Draw(tex_id,tx,ty,6,2,200+16.*5,450+d);

	n = points.size();
	for(int i=0;i<n;i++) {
		step_x = (points[i]-'0')+16;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw(tex_id,tx,ty,step_x,step_y,310.+16.*i,450+d);

	}
}

void cHud::DrawPlayer2Text(int tex_id, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	//writing punts:
	string aux = "press";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw(tex_id,tx,ty,step_x,step_y,400.+16.*i,450+d);
	}
	//f
		step_x = ('f'-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw(tex_id,tx,ty,step_x,step_y,400.+88.,450+d);
	
	//2
		step_x = ('2'-'0')+16;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw(tex_id,tx,ty,step_x,step_y,400.+104.,450+d);
	//to
	aux = "to";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw(tex_id,tx,ty,step_x,step_y,400.+128.+16.*i,450+d);
	}
	//play
	aux = "play";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw(tex_id,tx,ty,step_x,step_y,400.+168.+16.*i,450+d);
	}
}

void cHud::DrawGameOver(int tex_id, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	//writing punts:
	string aux = "game";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,220.+50.*i,240+d);
	}
	aux = "over";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,220.+50.*i,190+d);
	}
}

void cHud::DrawLevelComplete(int tex_id, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	//writing punts:
	string aux = "level";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,200.+50.*i,240+d);
	}
	aux = "complete";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,140.+50.*i,190+d);
	}
}

void cHud::DrawGameComplete(int tex_id, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	//writing punts:
	string aux = "game";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,216.+50.*i,240+d);
	}
	aux = "complete";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,140.+50.*i,190+d);
	}
}

void cHud::DrawPlayer2Wins(int tex_id, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	//writing punts:
	
    string aux = "player";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,50.+50.*i,205+d);
	}
	
	//2
		step_x = ('2'-'0')+16;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,350.,205+d);
	aux = "wins";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,416.+50.*i,205+d);
	}

}




void cHud::DrawPlayer1Wins(int tex_id, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	//writing punts:
	
    string aux = "player";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,50.+50.*i,205+d);
	}
	
	//1
		step_x = ('1'-'0')+16;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,350.,205+d);
	aux = "wins";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,416.+50.*i,205+d);
	}

}

void cHud::DrawPrepareToFight(int tex_id, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	//writing punts:
	string aux = "prepare";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,160.+50.*i,240+d);
	}
	aux = "to";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,152.+50.*i,190+d);
	}
	aux = "fight";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		Draw50(tex_id,tx,ty,step_x,step_y,268.+50.*i,190+d);
	}
}

void cHud::Draw(int tex_id, float tx,float ty, int step_x,int step_y,float trans_x, float trans_y) {
			glPushMatrix();
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

void cHud::Draw50(int tex_id, float tx,float ty, int step_x,int step_y,float trans_x, float trans_y) {
			glPushMatrix();
			glTranslatef(trans_x,trans_y,0.);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,tex_id);
			glBegin(GL_QUADS);
				glTexCoord2f(tx*step_x,ty*(step_y+1));		glVertex2i(0,0);
				glTexCoord2f(tx*(step_x+1),ty*(step_y+1));	glVertex2i(50,0);
				glTexCoord2f(tx*(step_x+1),ty*step_y);		glVertex2i(50,50);
				glTexCoord2f(tx*step_x,ty*step_y);			glVertex2i(0,50);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
}


