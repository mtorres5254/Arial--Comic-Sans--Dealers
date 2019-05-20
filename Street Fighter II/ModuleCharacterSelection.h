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

	SDL_Rect background;
	SDL_Rect P1Pointer;
	SDL_Rect P2Pointer;

	bool map=false,p1=false,p2=false;

	SDL_Texture* graphics = nullptr;
	Mix_Music* music;
	Mix_Chunk* start_sound;

private:
	int frame=0;
};

#endif 