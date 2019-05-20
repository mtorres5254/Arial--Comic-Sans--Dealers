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

	SDL_Texture * graphics = nullptr;
	SDL_Rect background;
	Mix_Music* music;
	Mix_Chunk* start_sound;
};

#endif 