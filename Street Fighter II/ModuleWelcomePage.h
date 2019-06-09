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

public:
	SDL_Rect fons;
	SDL_Rect personesRect;
	SDL_Rect persona1;
	SDL_Rect persona2;

	Animation persones_relax;
	Animation persones_attack;

	SDL_Texture* graphics = nullptr;
	SDL_Texture* persones = nullptr;
	Mix_Music* music;
};

#endif // __MODULEWELCOMEPAGE_H__