#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 15
#define MAX_AXIS 6
#define JOYSTICK_DEAD_ZONE 6553
#define JOYSTICK_DEAD_ZONE_NEGATIVE -6553

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GamePad {
	SDL_GameController* Pad;
	KEY_STATE button_state[MAX_BUTTONS];
	Sint16 axis_state[MAX_AXIS];
};

struct History {
	KEY_STATE keyboard[MAX_KEYS];
	uint frame = 0u;
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];

	bool camMoving,border;
	bool Gamepad = false;
	bool Gamepad2 = false;

	int history_count = 0;

	GamePad Pad1;
	GamePad Pad2;

	SDL_Event event;
	
};

#endif // __ModuleInput_H__