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
	int count=0;
	uint frame = 0u;

	//for (uint i = 1u; i < frames_past; i++) {}

	return false;
}