#include "Globals.h"
#include "Application.h"
#include "ModuleCombos.h"
#include "ModuleInput.h"
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

bool CommandPunch::Check(uint frames_past) const
{
	int count = 0;
	uint frames = 0u;

	for (uint i = 1u; i < frames_past; ++i) {
		if (count > 0 && (i - frames) > MAX_COMMAND_FRAMES) {
			return false;
		}
		History history = App->input->GetPrevious(i);

		const GamePad* pad = (history.Pads[0]);

		switch (count)
		{
		case 0: { if (pad->button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) { return true; } } break;
		}
	}
	return false;
}