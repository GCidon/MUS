#include "SoundManager.h"
#include <iostream>
using namespace std;

#include <conio.h>
#include <stdio.h>
#include <time.h>

void ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		// printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

SoundManager::SoundManager() {
	_result = System_Create(&_system); // Creamos el objeto system
	ERRCHECK(_result);
	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	_result = _system->init(128, FMOD_INIT_NORMAL, 0); // Inicializacion de FMOD
	ERRCHECK(_result);
}

SoundManager::~SoundManager() {
	
}

void SoundManager::loadSound(string name) {
	_result = _system->createSound(
		("../sounds/" + name).c_str(), // path al archivo de sonido
		FMOD_DEFAULT, // valores (por defecto en este caso: sin loop, 2D)
		0, // informacion adicional (nada en este caso)
		&_sound);
}

void SoundManager::play(){
	_result = _system->playSound(
	_sound, // buffer que se "engancha" a ese canal
	0, // grupo de canales, 0 sin agrupar (agrupado en el master)
	false, // arranca sin "pause" (se reproduce directamente)
	&_channel); // devuelve el canal que asigna
	// el sonido ya se esta reproduciendo

}
void SoundManager::stop() {
	_channel->stop();
	_result = _sound->release();
	ERRCHECK(_result);
}
void SoundManager::pause() {
	bool paused;
	_result = _channel->getPaused(&paused); ERRCHECK(_result);
	_result = _channel->setPaused(!paused); ERRCHECK(_result);
}
void SoundManager::changeVolume(float s) {
	if (_volume <= 1.0 && _volume >= 0.0) {
		_volume = _volume + s;
		_result = _channel->setVolume(_volume); ERRCHECK(_result);
	}

	if (_volume > 1.0) _volume = 1.0;
	else if (_volume < 0.0) _volume = 0.0;
	printf("Volume: %f\n", _volume);
}
void SoundManager::changePanorama() {
	_channel->setPan(_pan*=-1);
}

void SoundManager::fadeIn(float ms) {



	_sleep(ms);
}

void SoundManager::fadeOut(float ms) {



	_sleep(ms);
}

void SoundManager::run() {
	time_t start;
	time(&start);
	while (true) {
		time_t fin;
		time(&fin);
		_deltaTime = fin - start;
		time(&start);
		if (_kbhit()) {
			int key = _getch();
			if ((key == 'P') || (key == 'p')) {
				pause();
			}
			else if (key == 'w') {
				changePanorama();
			}
			else if (key == 'i') {
				fadeIn();
			}
			else if (key == 'o') {
				fadeOut();
			}
			else if (key == ' ') {
				play();
			}
			else if ((key == 'S') || (key == 's')) {
				stop();
			}
			else if (key == 'V') {
				changeVolume(0.1);
			}
			else if (key == 'v') {
				changeVolume(-0.1);
			}
			else if ((key == 'Q') || (key == 'q')) break;
		}
		_result = _system->update();
	}
}

