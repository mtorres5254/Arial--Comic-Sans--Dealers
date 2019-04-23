#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleCongratsScreen.h"
#include "ModuleWelcomePage.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"


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

	graphics = App->textures->Load("Assets/Images/CongratsScreen.png");	
	music = App->audio->LoadMusic("Assets/Audio/congrats.ogg");
	App->audio->PlayMusic(music, 3000);
	App->UI->Disable();

	return true;
}

bool ModuleCongratsScreen::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading CongratsScreen");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(music);
	App->congrats_screen->Disable();


	return true;
}

update_status ModuleCongratsScreen::Update()
{

	App->render->Blit(graphics, 0, 0, &background);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->congrats_screen, App->welcome_page, 2.0f);
		App->audio->StopMusic(2500);
	}

	return UPDATE_CONTINUE;
}