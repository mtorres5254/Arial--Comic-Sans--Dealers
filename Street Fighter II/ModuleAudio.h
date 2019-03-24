#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

struct Mix_Chunk;

#define MAX_AUDIOS 50

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Chunk* const Load(const char* path);

public:
	Mix_Chunk *music;
	Mix_Chunk *audios[MAX_AUDIOS];
};

#endif // __ModuleAudios_H__