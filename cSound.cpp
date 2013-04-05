#include "cSound.h"



cSound::cSound(void)
{
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
}


cSound::~cSound(void)
{
}

void cSound::PlaySound(char *path,bool loop){
	FMOD::Sound *s;
	if(loop) {
		channel1->stop();
		system->createStream(path, 
					  FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &s);
		system->playSound(FMOD_CHANNEL_FREE, s, false, &channel1);
	}
	else {
		system->createSound(path, FMOD_SOFTWARE, 0, 
						&s);
		system->playSound(FMOD_CHANNEL_FREE, s, false,&channel2 );
	}
}

void cSound::PlaySound(char *path,bool loop,float vol){
	FMOD::Sound *s;
	if(loop) {
		channel1->stop();
		system->createStream(path, 
					  FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &s);
		system->playSound(FMOD_CHANNEL_FREE, s, false, &channel1);
	}
	else {
		system->createSound(path, FMOD_SOFTWARE, 0, 
						&s);
		system->playSound(FMOD_CHANNEL_FREE, s, false,&channel2 );
		channel2->setVolume(vol);
	}
}

void cSound::Update() {
	system->update();
}