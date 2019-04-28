#ifndef _MODULEUI_H
#define _MODULEUI_H

#include "Module.h"
#include "Animation.h"
#include "ModuleFont.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;

	SDL_Rect HealthBar1;
	SDL_Rect RedBar1;
	SDL_Rect HealthBar2;
	SDL_Rect RedBar2;
	SDL_Rect KObar;
	SDL_Rect RoundBar1;
	SDL_Rect RoundBar2;

	SDL_Rect num0;
	SDL_Rect num1;
	SDL_Rect num2;
	SDL_Rect num3;
	SDL_Rect num4;
	SDL_Rect num5;
	SDL_Rect num6;
	SDL_Rect num7;
	SDL_Rect num8;
	SDL_Rect num9;

	Animation KOanim;

	
};

#endif // !_MODULEUI_H

