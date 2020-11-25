#pragma once

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <stdio.h>
#include <string>
using namespace FMOD;
using namespace std;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void loadSound(string name);

	void play();
	void stop();
	void pause();
	void changeVolume(float s);
	void changePanorama();

	void fadeIn(float ms);
	void fadeOut(float ms);

	void run();

protected:
	double _deltaTime;

	Sound* _sound;
	System* _system;
	Channel* _channel;
	FMOD_RESULT _result;

	float _volume = 1.0;
	float _pan = 1.0;

};

