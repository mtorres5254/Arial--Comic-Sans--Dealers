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
	LOG("Init ModuleCOMBOS");

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
	if (actual_frameP1LK <= LIGHTNINGKICK) {
		switch (lightimgKickCount)
		{
		case 0:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
				lightimgKickCount++;
			}
			break;
		case 1:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
				lightimgKickCount++;
			}
			break;
		case 2:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
				lightimgKickCount = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP1LK = 0;
		lightimgKickCount = 0;
		return false;
	}
}

bool ModuleCombos::CheckLightingKickP2() {
	actual_frameP2LK++;
	if (actual_frameP2LK <= LIGHTNINGKICK) {
		switch (lightimgKickCount2)
		{
		case 0:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
				lightimgKickCount2++;
			}
			break;
		case 1:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
				lightimgKickCount2++;
			}
			break;
		case 2:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
				lightimgKickCount2 = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP2LK = 0;
		lightimgKickCount2 = 0;
		return false;
	}
}