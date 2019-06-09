#ifndef __MODULEWELCOMEPAGE_H__
#define __MODULEWELCOMEPAGE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"

class ModuleWelcomePage : public Module
{
public:
	ModuleWelcomePage();
	~ModuleWelcomePage();

	bool Start();
	update_status Update();
	bool CleanUp();

	void Persona1Move();
	void Persona2Move(Uint32 time, int delay);

public:
	SDL_Rect fons;
	SDL_Rect personesRect;
	SDL_Rect persona1;
	SDL_Rect personaDest;
	SDL_Rect persona2;
	SDL_Rect persona2Dest;

	SDL_Rect logo_Rect;
	SDL_Rect logo_RectDest;
	SDL_Rect TheWorldWarrior;
	SDL_Rect TheWorldWarriorDest;
	SDL_Rect Capcom;
	SDL_Rect CapcomDest;

	int animcount = 0;
	int blackcount = 0;

	bool Anim2 = false;
	bool time = false;
	bool cameraMove = false;
	bool punch = false;
	bool logo_anim = false;

	bool TWWMove = false;

	Uint32 actualtime;

	Animation persones_relax;
	Animation insert_coin;
	Animation logo;

	SDL_Texture* graphics = nullptr;
	SDL_Texture* persones = nullptr;
	SDL_Texture* logo_texture = nullptr;

	Mix_Music* music;
	Mix_Chunk* punchEffect;
};

#endif // __MODULEWELCOMEPAGE_H__