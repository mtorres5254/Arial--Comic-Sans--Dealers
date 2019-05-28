#ifndef __MODULEWELCOMEPAGE_H__
#define __MODULEWELCOMEPAGE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

class ModuleWelcomePage : public Module
{
public:
	ModuleWelcomePage();
	~ModuleWelcomePage();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* pointUI = nullptr;
	SDL_Texture* Licensed=nullptr;
	SDL_Texture* Capcom = nullptr;
	SDL_Rect background, pointer;
	SDL_Rect LicensedBy[6];
	SDL_Rect CapcomLogo[8];
	Mix_Music* music;
	Mix_Chunk* SelectFX;
	//Mix_Chunk* start_sound;

private:
	bool finish,select,Nintendo,capcom;
	int timer,aux;
};

#endif // __MODULEWELCOMEPAGE_H__