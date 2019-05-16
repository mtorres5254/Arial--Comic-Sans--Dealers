#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL.h"
#include <iostream>
#include <list>

#define MAX_KEYS 300
#define MAX_BUTTONS 15
#define JOYSTICK_DEAD_ZONE 8000

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
	Uint8 Pressed[MAX_BUTTONS];
	float Xaxis_state;
	float Yaxis_state;
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	void GetGamepadButton(GamePad*);
	void GetGamepadAxis(GamePad*);

public:
	KEY_STATE keyboard[MAX_KEYS];
	bool camMoving,border;
	bool Gamepad = false;
	bool Gamepad2 = false;
	GamePad Pad1;
	GamePad Pad2;
	SDL_Event event;
};

#endif // __ModuleInput_H__