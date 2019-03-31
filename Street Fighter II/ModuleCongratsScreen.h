#ifndef __MODULEWCONGRATSSCREEN_H__
#define __MODULECONGRATSSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

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

};

#endif // __MODULECONGRATSSCREEN_H__