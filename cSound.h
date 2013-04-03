#pragma once

#pragma comment(lib,"fmodex_vc")

#include "Globals.h"
#include <string>
//#include "fmod_errors.h"
#include "fmod.hpp"
#include "fmod_errors.h"
//#include "fmod.h"
//#include 


class cSound
{
public:
	cSound(void);
	~cSound(void);
	void PlaySound(char* path,bool loop);
	void Update();
private:
	FMOD::System     *system;
	FMOD::Channel    *channel1;
	FMOD::Channel    *channel2;
	/*FMOD::System     *system;
    FMOD::Sound      *sound1, *sound2, *sound3;
    FMOD::Channel    *channel;
    FMOD_RESULT       result;
    unsigned int      version;
    void             *extradriverdata;
	*/
};

