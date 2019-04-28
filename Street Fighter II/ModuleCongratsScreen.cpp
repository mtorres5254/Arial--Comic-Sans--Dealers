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
	music = App->audio->LoadMusic("Assets/Sound/congrats.ogg");
	App->audio->PlayMusic(music, 300);
	App->render->camera.x = App->render->camera.y = 0;

	return true;
}

bool ModuleCongratsScreen::CleanUp()
{
	LOG("Unloading Congrats Screen");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(music);

	return true;
}

update_status ModuleCongratsScreen::Update()
{

	App->render->Blit(graphics, 0, 0, &background);

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) {

		App->fade->FadeToBlack(App->congrats_screen, App->welcome_page, 2.0f);
		App->audio->StopMusic(250);
	}

	return UPDATE_CONTINUE;
}