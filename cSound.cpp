#include "cSound.h"
//#include "common.h"



cSound::cSound(void)
{
	//FSOUND_Init (44100, 32, 0);
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
}


cSound::~cSound(void)
{
}

void cSound::PlaySound(char *path,bool loop){
	FMOD::Sound *s;
	//system->createSound(path.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &s);
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

void cSound::Update() {
	system->update();
}
/*void cSound::addSound(char *path, string n){
    Sound* s;
    fmodsys->createSound(path, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &s);


    soundMap.insert(pair<string,Sound*>(n, s));
}

void SoundMgr::playOnce(string name){

    fmodsys->playSound(FMOD_CHANNEL_FREE,
        soundMap.find(name)->second, true, &fmodchn);
    fmodchn->setPosition(0, FMOD_TIMEUNIT_PCM);
    fmodchn->setPaused(false);
}

void SoundMgr::playRepeat(string name){

    fmodsys->playSound(FMOD_CHANNEL_FREE,
        soundMap.find(name)->second, true, &backChn);
    backChn->setMode(FMOD_LOOP_NORMAL);
    backChn->setPosition(0, FMOD_TIMEUNIT_PCM);
    backChn->setPaused(false);

}*/