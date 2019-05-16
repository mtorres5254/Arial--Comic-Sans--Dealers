#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 15
#define MAX_AXIS 6
#define MAX_PADS 4
#define JOYSTICK_DEAD_ZONE 0.2
#define JOYSTICK_DEAD_ZONE_NEGATIVE -0.2
#define MAX_HISTORY 180

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};
enum AXIS_STATE
{
AXIS_IDLE = 0,
AXIS_MOVE
};

struct GamePad {
	SDL_GameController* Pad;
	KEY_STATE button_state[MAX_BUTTONS];
	AXIS_STATE axis_state[MAX_AXIS];
	float Xaxis_state = 0.f;
	float Yaxis_state = 0.f;
};

struct History {
	GamePad* Pads[MAX_PADS];
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
	void GetGamepadAxis(GamePad*);

public:
	KEY_STATE keyboard[MAX_KEYS];

	bool camMoving,border;
	bool Gamepad = false;
	bool Gamepad2 = false;

	int history_count = 0;

	GamePad* Pads[MAX_PADS];
	GamePad Pad1;
	GamePad Pad2;

	History history[MAX_HISTORY];

	SDL_Event event;
	
};

#endif // __ModuleInput_H__