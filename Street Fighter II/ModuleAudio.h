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

	Mix_Music* const LoadMusic(const char* path);
	Mix_Chunk* const LoadChunk(const char* path);
	bool UnloadMusic(Mix_Music * music);
	bool UnloadChunk(Mix_Chunk * chunk);
	bool PlayMusic(Mix_Music * music, int delay);
	bool PlayChunk(Mix_Chunk * chunk, int repeats);
	bool StopMusic(int delay);

public:
	Mix_Music* musics[MAX_AUDIOS];
	Mix_Chunk* effects[MAX_AUDIOS];
};

#endif // __ModuleAudio_H__
