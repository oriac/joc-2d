#include "cItem.h"


cItem::cItem(void)
{
}


cItem::~cItem(void)
{
}

void cItem::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	xo = 0.0f;
	yo = 1.0f;
	xf = 1.0f;
	yf = 0.0f;

	DrawRect(tex_id,xo,yo,xf,yf);
}

bool cItem::IsActive()
{
	return active;
}

void cItem::SetActive(bool b)
{
	active = b;
}