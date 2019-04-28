#ifndef _MODULEUI_H
#define _MODULEUI_H

#include "Module.h"
#include "Animation.h"
#include "ModuleFont.h"
#include "Globals.h"
#include "p2Point.h"

#define SECOND 1000 

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

	void Counter();

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

	Animation KOanim;

	int font_id;
	int time;
	int Counter1;
	int Counter2;
	int timenow;

	
};

#endif // !_MODULEUI_H

