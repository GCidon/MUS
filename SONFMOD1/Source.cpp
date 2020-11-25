#include <iostream>

using namespace std;

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"

#include "SoundManager.h"

using namespace FMOD;



int main() {

	SoundManager man;

	man.loadSound("Battle.wav");

	man.run();


}