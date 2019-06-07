#ifndef __MODULECHARACTERSELECTION_H__
#define __MODULECHARACTERSELECTION_H__

#include "Module.h"
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
	SDL_Texture* ui = nullptr;
	SDL_Texture* versus = nullptr;
	Mix_Music* music;
	Mix_Chunk* character_effect;
	Mix_Chunk* map_effect;
	Mix_Chunk* plane_effect;

private:
	int frame=0;
	bool selected;
};

#endif 