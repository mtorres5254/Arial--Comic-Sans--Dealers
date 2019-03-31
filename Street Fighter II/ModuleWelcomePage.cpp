#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneKen.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleWelcomePage.h"


ModuleWelcomePage::ModuleWelcomePage()
{
	background.x = 0;
	background.y = 0;
	background.h = SCREEN_HEIGHT;
	background.w = SCREEN_WIDTH;
}

ModuleWelcomePage::~ModuleWelcomePage()
{}

bool ModuleWelcomePage::Start()
{
	LOG("Loading WelcomePage");

	graphics = App->textures->Load("TitleScreen.png");
	   
	return true;
}

bool ModuleWelcomePage::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading WelcomePage");

	App->textures->Unload(graphics);
	App->welcome_page->Disable();

	return true;
}

update_status ModuleWelcomePage::Update()
{
	
	App->render->Blit(graphics, 0, 0, &background);

	// TODO 2: make so pressing SPACE the HONDA stage is loaded

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) {

		App->fade->FadeToBlack(App->welcome_page, App->scene_ken, 2.0f);

	}

	return UPDATE_CONTINUE;
}