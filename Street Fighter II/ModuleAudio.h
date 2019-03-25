#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_AUDIOS 50

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Music* const Load(const char* path);

public:
	Mix_Music *music;
	Mix_Music *audios[MAX_AUDIOS];
};

#endif // __ModuleAudios_H__