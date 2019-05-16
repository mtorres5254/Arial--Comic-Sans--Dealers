#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"
#include <stdio.h>
#include <string.h>

ModuleInput::ModuleInput() : Module()
{
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	SDL_Init(SDL_INIT_GAMECONTROLLER);

	//Load joystick

	if (SDL_NumJoysticks() >= 1) {
		Pad1.Pad = SDL_GameControllerOpen(0);
		Pads[0] = &Pad1;
		Gamepad = true;
	}
	if (SDL_NumJoysticks() == 2) {
		Pad2.Pad = SDL_GameControllerOpen(1);
		Pads[1] = &Pad2;
		Gamepad2 = true;
	}
			
	

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	camMoving = false;
	border = false;
	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	if (history_count < MAX_HISTORY) {
		history_count++;
	}
	if (history_count == MAX_HISTORY) {
		history_count = 0;
	}

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (Gamepad == false && SDL_NumJoysticks() >= 1) {
		Pad1.Pad = SDL_GameControllerOpen(0);
		Pads[0] = &Pad1;
		Gamepad = true;
	}
	if (Gamepad == true && SDL_NumJoysticks() == 0) {
		SDL_GameControllerClose(Pad1.Pad);
		Pads[0] = nullptr;
		Gamepad = false;
	}

	if (Gamepad2 == false && SDL_NumJoysticks() >= 2) {
		Pad2.Pad = SDL_GameControllerOpen(1);
		Pads[1] = &Pad2;
		Gamepad2 = true;
	}
	if (Gamepad2 == true && SDL_NumJoysticks() < 2) {
		SDL_GameControllerClose(Pad2.Pad);
		Pads[1] = nullptr;
		Gamepad2 = false;
	}
	
	//Gamepad logic
	if (Gamepad == true) {
		//GetGamepadButton(&Pad1);
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
			if (SDL_GameControllerGetButton(Pad1.Pad, (SDL_GameControllerButton)i) == 1) {
				if (Pad1.button_state[i] == KEY_IDLE) {
					Pad1.button_state[i] = KEY_DOWN;
				}
				else {
					Pad1.button_state[i] = KEY_REPEAT;
				}
			}
			else {
				if (Pad1.button_state[i] == KEY_REPEAT || Pad1.button_state[i] == KEY_DOWN) {
					Pad1.button_state[i] = KEY_UP;
				}
				else {
					Pad1.button_state[i] = KEY_IDLE;
				}
			}
		}
		for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; ++i) {
			if (SDL_GameControllerGetAxis(Pad1.Pad, (SDL_GameControllerAxis)i) == 1) {
				if (Pad1.axis_state[i] == AXIS_IDLE) {
					Pad1.axis_state[i] = AXIS_MOVE;
				}
			}
			else {
				if (Pad1.axis_state[i] == AXIS_MOVE) {
					Pad1.axis_state[i] = AXIS_IDLE;
				}
			}
		}
	}
   
	if (Gamepad2 == true) {
		//GetGamepadButton
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
			if (SDL_GameControllerGetButton(Pad2.Pad, (SDL_GameControllerButton)i) == 1) {
				if (Pad2.button_state[i] == KEY_IDLE) {
					Pad2.button_state[i] = KEY_DOWN;
				}
				else {
					Pad2.button_state[i] = KEY_REPEAT;
				}
			}
			else {
				if (Pad2.button_state[i] == KEY_REPEAT || Pad2.button_state[i] == KEY_DOWN) {
					Pad2.button_state[i] = KEY_UP;
				}
				else {
					Pad2.button_state[i] = KEY_IDLE;
				}
			}
		}
		//GetGamepadAxis
		for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; ++i) {
			if (SDL_GameControllerGetAxis(Pad2.Pad, (SDL_GameControllerAxis)i) == 1) {
				if (Pad2.axis_state[i] == AXIS_IDLE) {
					Pad2.axis_state[i] = AXIS_MOVE;
				}
			}
			else {
				if (Pad2.axis_state[i] == AXIS_MOVE) {
					Pad2.axis_state[i] = AXIS_IDLE;
				}
			}
		}
	}
	
	//Keyboard logic
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	if (keyboard[SDL_SCANCODE_O]) {
		App->render->camera.x += 1;
	}

	if (keyboard[SDL_SCANCODE_P]) {
		App->render->camera.x -= 1;
	}

		

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT) { return update_status::UPDATE_STOP; }
	}
	

	memcpy(history[history_count].keyboard, keyboard, sizeof(KEY_STATE)*MAX_KEYS);
	memcpy(history[history_count].Pads, Pads, sizeof(GamePad)*MAX_PADS);

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}

void ModuleInput::GetGamepadAxis(GamePad* gamepad) {
	float auxX, auxY;
	auxX = SDL_GameControllerGetAxis(gamepad->Pad, SDL_CONTROLLER_AXIS_LEFTX);
	auxY = SDL_GameControllerGetAxis(gamepad->Pad, SDL_CONTROLLER_AXIS_LEFTY);

	gamepad->Xaxis_state = auxX / 32767;
	gamepad->Yaxis_state = auxY / 32767;
}