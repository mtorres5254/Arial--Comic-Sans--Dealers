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

	SDL_Rect Map;
	SDL_Rect Characters;
	SDL_Rect P1Pointer;
	SDL_Rect P1PpointerDest;
	SDL_Rect P2Pointer;
	SDL_Rect P2PointerDest;
	SDL_Rect Plane;
	SDL_Rect P1CharacterDest;
	SDL_Rect P2CharacterDest;

	SDL_Rect Ryu;
	SDL_Rect Ken;
	SDL_Rect Blanka;
	SDL_Rect Guile;
	SDL_Rect EHonda;
	SDL_Rect Dhalsim;
	SDL_Rect Zangief;
	SDL_Rect ChunLi;

	bool P1selected = false;
	bool P2selected = false;

	SDL_Texture* graphics = nullptr;

	Mix_Music* music;

	Mix_Chunk* character_effect;
	Mix_Chunk* map_effect;
	Mix_Chunk* plane_effect;
};

#endif 