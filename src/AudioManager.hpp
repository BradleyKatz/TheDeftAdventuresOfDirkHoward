#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>

using namespace std;

class AudioManager
{
private:
	// Forbid creating instances of this class, for it is not needed
	AudioManager(){}
public:
	static void playBackgroundMusic(string fileName);
	static void stopBackgroundMusic();
};

#endif
