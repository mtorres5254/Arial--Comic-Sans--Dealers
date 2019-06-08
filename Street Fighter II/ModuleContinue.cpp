
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"

#include "ModuleContinue.h"


ModuleContinue::ModuleContinue() {

}

ModuleContinue::~ModuleContinue()
{}

bool ModuleContinue:: Start() {


	return true;
}

update_status ModuleContinue::Update() {


	return UPDATE_CONTINUE;
}

bool ModuleContinue::CleanUp() {


	return true;
}