#ifndef __MODULECHARACTERSELECTION_H__
#define __MODULECHARACTERSELECTION_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

class ModuleCharacterSelection : public Module
{
public:
	ModuleCharacterSelection();
	~ModuleCharacterSelection();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Rect Map;
	SDL_Rect background;
	SDL_Rect P1Pointer;
	SDL_Rect P2Pointer;
	SDL_Rect Cross;


	SDL_Texture* graphicsUI = nullptr;
	SDL_Texture* graphicsBack = nullptr;
	Mix_Music* music;
	Mix_Chunk* start_sound;
};

#endif 