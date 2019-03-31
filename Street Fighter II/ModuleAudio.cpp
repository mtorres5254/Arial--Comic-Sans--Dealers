#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio()
{
	for (uint i = 0; i < MAX_AUDIOS; ++i) {
		musics[i] = nullptr;
		effects[i] = nullptr;
	}
}

// Destructor
ModuleAudio::~ModuleAudio() {

}

// Called before render is available
bool ModuleAudio::Init()
{
	LOG("Init Music library");
	bool ret = true;

	// load support for the PNG image format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Music lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	for (int i = 0; i < MAX_AUDIOS; i++) {
		musics[i] = nullptr;
		effects[i] = nullptr;
	}

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing Musics and Audio effects");

	for (uint i = 0; i < MAX_AUDIOS; ++i) {
		if (musics[i] != nullptr)
			Mix_FreeMusic(musics[i]);
		if (effects[i] != nullptr)
			Mix_FreeChunk(effects[i]);
	}

	Mix_Quit();
	return true;
}

// Load new music from file path
Mix_Music* const ModuleAudio::LoadMusic(const char* path)
{
	Mix_Music* music;
	music = Mix_LoadMUS(path);

	for (int i = 0; i < MAX_AUDIOS; i++) {
		if (music == nullptr) {
			musics[i] = music;
			break;
		}
	}

	return music;
}

bool ModuleAudio::UnloadMusic(Mix_Music *music)
{
	bool ret = false;

	if (music != nullptr)
	{
		for (int i = 0; i < MAX_AUDIOS; ++i)
		{
			if (musics[i] == music)
			{
				musics[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FreeMusic(music);
	}

	return ret;
}

// Load new effect from file path
Mix_Chunk* const ModuleAudio::LoadChunk(const char* path)
{
	Mix_Chunk* effect;
	effect = Mix_LoadWAV(path);

	for (int i = 0; i < MAX_AUDIOS; i++) {
		if (effect == nullptr) {
			effects[i] = effect;
			break;
		}
	}

	return effect;
}

bool ModuleAudio::UnloadChunk(Mix_Chunk *effect)
{
	bool ret = false;

	if (effect != nullptr)
	{
		for (int i = 0; i < MAX_AUDIOS; ++i)
		{
			if (effects[i] == effect)
			{
				effects[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FreeChunk(effect);
	}

	return ret;
}