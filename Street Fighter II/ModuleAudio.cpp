#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio()
{
	for (int i = 0; i < MAX_AUDIOS; i++) {
			musics[i] = nullptr;
			effects[i] = nullptr;
	}
}

// Destructor
ModuleAudio::~ModuleAudio() {
	Mix_CloseAudio();
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

	Mix_Volume(1, 50);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		LOG("Mix_OpenAudio: %s\n", Mix_GetError());
	}

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing Musics and Audio effects");

	for (int i = MAX_AUDIOS; i > 0; i--) {
		if (musics[i] != nullptr) {
			Mix_FreeMusic(musics[i]);
		}
	}

	Mix_FadeOutChannel(-1, 1);

	for (int i = MAX_EFFECTS; i > 0; i--) {
		UnloadChunk(effects[i]);
	}
	

	Mix_CloseAudio();

	Mix_Quit();
	return true;
}

bool ModuleAudio::PlayMusic(Mix_Music * music, int delay) {

	Mix_FadeInMusic(music, -1, delay);

	return true;
}

bool ModuleAudio::StopMusic(int delay) {
	Mix_FadeOutMusic(delay);

	return true;
}

bool ModuleAudio::PlayChunk(Mix_Chunk * chunk, int repeats) {
	Mix_PlayChannel(-1, chunk, repeats - 1);
	return true;
}

// Load new music from file path
Mix_Music* const ModuleAudio::LoadMusic(const char* path)
{
	Mix_Music* music;
	music = Mix_LoadMUS(path);

	for (int i = 0; i < MAX_AUDIOS; i++) {
		if (musics[i] == nullptr) {
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
		for (int i = MAX_AUDIOS; i > 0; i--)
		{
			if (musics[i] == music)
			{
				musics[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FadeOutMusic(3000);
	}

	return ret;
}

// Load new effect from file path
Mix_Chunk* const ModuleAudio::LoadChunk(const char* path)
{
	int ret = 0;

	for (int i = 0; i < MAX_EFFECTS; i++) {
		if (effects[i] == nullptr) {
			effects[i] = Mix_LoadWAV(path);
			ret = i;
			break;
		}
	}
	

	return effects[ret];
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
				Mix_FreeChunk(effect);
				effects[i] = nullptr;
				ret = true;
				break;
			}
		}
	}
	return ret;
}