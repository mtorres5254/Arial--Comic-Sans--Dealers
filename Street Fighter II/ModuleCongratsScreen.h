#ifndef __MODULEWCONGRATSSCREEN_H__
#define __MODULECONGRATSSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

class ModuleCongratsScreen : public Module
{
public:
	ModuleCongratsScreen();
	~ModuleCongratsScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Mix_Chunk* music;

private:
	int timer;
};

#endif // __MODULECONGRATSSCREEN_H__