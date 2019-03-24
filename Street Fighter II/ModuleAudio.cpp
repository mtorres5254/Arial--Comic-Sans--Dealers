#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio() : Module()
{
	
	for (int i = 0; i < MAX_AUDIOS; i++) {
		audios[i] == nullptr;
	}
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init()
{
	LOG("Init Mixer library");
	bool ret = true;

	
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib.");
		ret = false;
	}

	music = App->audio->Load("Assets/Ryumusic.OGG");

	Mix_PlayChannel(-1, music, -1);
	
	return ret;
}

bool ModuleAudio::CleanUp()
{
	LOG("Freeing audios and Mixer library");

	// TODO 6: Free all textures
	for (int i = 0; i < MAX_AUDIOS; i++) {

		if (audios[i] != nullptr) {
			Mix_FreeChunk(audios[i]);
		}
	}
	Mix_CloseAudio();
	Mix_Quit();
	return true;
}


Mix_Chunk* const ModuleAudio::Load(const char* path)
{

	LOG("Loading Music");
	Mix_Chunk *music;
	music = Mix_LoadWAV(path);	

	for (int i = 0; i < MAX_AUDIOS; i++) {

		if (audios[i] == nullptr) {
			audios[i] = music;
			i = MAX_AUDIOS;
		}
	}

	return music;
	//return nullptr;
}
