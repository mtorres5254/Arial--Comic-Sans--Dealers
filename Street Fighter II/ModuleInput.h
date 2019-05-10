#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL.h"
#include <iostream>
#include <list>

#define MAX_KEYS 300
#define JOYSTICK_DEAD_ZONE 8000
enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{

public:

	SDL_Joystick* gGameController;
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	std::list<SDL_Event> eventList;
	bool camMoving,border;
};

#endif // __ModuleInput_H__