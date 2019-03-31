#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleCongratsScreen.h"
#include "ModuleWelcomePage.h"


ModuleCongratsScreen::ModuleCongratsScreen()
{
	background.x = 0;
	background.y = 0;
	background.h = SCREEN_HEIGHT;
	background.w = SCREEN_WIDTH;
}

ModuleCongratsScreen::~ModuleCongratsScreen()
{}

bool ModuleCongratsScreen::Start()
{
	LOG("Loading CongratsScreen");

	graphics = App->textures->Load("CongratsScreen.png");	

	return true;
}

bool ModuleCongratsScreen::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading CongratsScreen");

	App->textures->Unload(graphics);
	App->congrats_screen->Disable();
	return true;
}

update_status ModuleCongratsScreen::Update()
{

	App->render->Blit(graphics, 0, 0, &background);

	// TODO 2: make so pressing SPACE the HONDA stage is loaded

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->congrats_screen, App->welcome_page, 2.0f);

	}

	return UPDATE_CONTINUE;
}