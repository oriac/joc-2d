#pragma once
#include "cbicho.h"
class cItem :
	public cBicho
{
public:
	cItem(void);
	~cItem(void);
	void Draw(int tex_id);
	bool IsActive();
	void SetActive(bool b);
	private:
	bool active;
};

