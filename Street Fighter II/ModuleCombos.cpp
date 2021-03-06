#include "Globals.h"
#include "Application.h"
#include "ModuleCombos.h"
#include "ModuleInput.h"
#include "ModuleChunLi.h"
#include "ModuleChunLi2.h"
#include "SDL/include/SDL.h"

ModuleCombos::ModuleCombos() : Module()
{

}

// Destructor
ModuleCombos::~ModuleCombos()
{}

bool ModuleCombos::Init() {

	LOG("Init Module COMBOS");

	return true;
}

bool ModuleCombos::CleanUp() {

	return true;
}

update_status ModuleCombos::Update() {	

	return update_status::UPDATE_CONTINUE;
}

bool ModuleCombos::CheckPunchP1() {
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		return true;
	}
	return false;
}

bool ModuleCombos::CheckPunchP2() {
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		return true;
	}
	return false;
}

bool ModuleCombos::CheckLightingKickP1() {
	actual_frameP1LK++;
	bool ret = false;
	if (actual_frameP1LK <= LIGHTNINGKICK) {
		switch (lightimgKickCount)
		{
		case 0:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				lightimgKickCount++;
			}
			break;
		case 1:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				lightimgKickCount++;
			}
			break;
		case 2:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				lightimgKickCount = 0;
				ret = true;
			}
			break;
		}
	}
	else {
		actual_frameP1LK = 0;
		lightimgKickCount = 0;
	}
	return ret;
}

bool ModuleCombos::CheckLightingKickP2() {
	actual_frameP2LK++;
	bool ret = false;
	if (actual_frameP2LK <= LIGHTNINGKICK) {
		switch (lightimgKickCount2)
		{
		case 0:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				lightimgKickCount2++;
			}
			break;
		case 1:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				lightimgKickCount2++;
			}
			break;
		case 2:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				lightimgKickCount2 = 0;
				ret = true;
			}
			break;
		}
	}
	else {
		actual_frameP2LK = 0;
		lightimgKickCount2 = 0;
	}
	return ret;
}

bool ModuleCombos::CheckWhirlwindKickP1() {
	actual_frameP1WK++;
	bool ret = false;
	if (actual_frameP1WK <= WHIRLWINDKICK) {
		switch (whirlwindKickCount) 
		{
		case 0:
			if (App->chunli->state == ST_CROUCH2) {
				HoldWKP1++;
			}
			if (App->chunli->state == ST_IDLE2) {
				if (HoldWKP1 > 10) {
					HoldWKP1 = 0;
					whirlwindKickCount++;
				}
			}
			break;
		case 1:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				whirlwindKickCount = 0;
				ret = true;
			}
			break;
		}
	}
	else {
		actual_frameP1WK = 0;
		whirlwindKickCount = 0;
	}
	return ret;
}

bool ModuleCombos::CheckWhirlwindKickP2() {
	actual_frameP2WK++;
	bool ret = false;
	if (actual_frameP2WK <= WHIRLWINDKICK) {
		switch (whirlwindKickCount2) {
		case 0:
			if (App->chunli2->state == ST_CROUCH) {
				HoldWKP2++;
			}
			if (App->chunli2->state == ST_IDLE) {
				if (HoldWKP2 > 10) {
					HoldWKP2 = 0;
					whirlwindKickCount2++;
				}
			}
			break;
		case 1:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				whirlwindKickCount2 = 0;
				ret = true;
			}
			break;			
		}
	}
	else {
		actual_frameP2WK = 0;
		whirlwindKickCount2 = 0;
	}
	return ret;
}