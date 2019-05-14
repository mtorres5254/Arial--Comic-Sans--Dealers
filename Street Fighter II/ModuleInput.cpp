#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"

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
		Gamepad = true;
	}
	if (SDL_NumJoysticks() == 2) {
		Pad2.Pad = SDL_GameControllerOpen(1);
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

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	SDL_GameControllerUpdate();

	if (Gamepad == false && SDL_NumJoysticks() > 0) {
		Pad1.Pad = SDL_GameControllerOpen(1);
		Gamepad = true;
	}
	if (Gamepad == true && SDL_NumJoysticks() == 0) {
		Pad1.Pad = NULL;
		Gamepad = false;
	}

	if (Gamepad2 == false && SDL_NumJoysticks() == 2) {
		Pad2.Pad = SDL_GameControllerOpen(2);
		Gamepad2 = true;
	}
	if (Gamepad2 == true && SDL_NumJoysticks() < 2) {
		Pad2.Pad = NULL;
		Gamepad2 = false;
	}
	
	//Gamepad logic
	if (Gamepad == true) {
		GetGamepadButton(&Pad1);
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
			if (SDL_GameControllerGetButton(Pad1.Pad, (SDL_GameControllerButton)i) == 1) {
				if (Pad1.key_state == KEY_IDLE) {
					Pad1.key_state == KEY_DOWN;
				}
				else {
					Pad1.key_state = KEY_REPEAT;
				}
			}
			else {
				if (Pad1.key_state == KEY_REPEAT || Pad1.key_state == KEY_DOWN) {
					Pad1.key_state = KEY_UP;
				}
				else {
					Pad1.key_state = KEY_IDLE;
				}
			}
		}
	}
   
	if (Gamepad2 == true) {
		GetGamepadButton(&Pad2);
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
			if (SDL_GameControllerGetButton(Pad2.Pad, (SDL_GameControllerButton)i) == 1) {
				if (Pad2.key_state == KEY_IDLE) {
					Pad2.key_state == KEY_DOWN;
				}
				else {
					Pad2.key_state = KEY_REPEAT;
				}
			}
			else {
				if (Pad2.key_state == KEY_REPEAT || Pad2.key_state == KEY_DOWN) {
					Pad2.key_state = KEY_UP;
				}
				else {
					Pad2.key_state = KEY_IDLE;
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
	

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}

void ModuleInput::GetGamepadButton(GamePad* gamepad) {
    if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_A) == 1) gamepad->button_state = A;
	if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_B) == 1) gamepad->button_state = B;
	if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_X) == 1) gamepad->button_state = X;
	if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_Y) == 1) gamepad->button_state = Y;
	if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1) gamepad->button_state = DPAD_UP;
	if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1) gamepad->button_state = DPAD_DOWN;
	if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1) gamepad->button_state = DPAD_LEFT;
	if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1) gamepad->button_state = DPAD_RIGHT;
	if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == 1) gamepad->button_state = LB;
	if (SDL_GameControllerGetButton(gamepad->Pad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == 1) gamepad->button_state = RB; 
}

void ModuleInput::GetGamepadAxis(GamePad* gamepad) {
	gamepad->Xaxis_state = SDL_GameControllerGetAxis(gamepad->Pad, SDL_CONTROLLER_AXIS_LEFTX);
	gamepad->Yaxis_state = SDL_GameControllerGetAxis(gamepad->Pad, SDL_CONTROLLER_AXIS_LEFTY);
}