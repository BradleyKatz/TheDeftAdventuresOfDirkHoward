#include "AudioManager.hpp"

void AudioManager::playBackgroundMusic(string fileName)
{
	if (!PlaySound((LPCSTR) fileName.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT))
		cerr << "ERROR: Could not bgm " + fileName << endl;
}

void AudioManager::stopBackgroundMusic()
{
	PlaySound(NULL, 0, 0);
}
