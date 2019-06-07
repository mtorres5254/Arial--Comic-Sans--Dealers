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
	timer = 0;
	graphics = App->textures->Load("Assets/Images/CongratsScreen.png");	
	music = App->audio->LoadChunk("Assets/Sound/Effects/lose_screen.wav");
	App->audio->PlayChunk(music, 1);
	App->render->camera.x = App->render->camera.y = 0;

	return true;
}

bool ModuleCongratsScreen::CleanUp()
{
	LOG("Unloading Congrats Screen");
	App->textures->Unload(graphics);
	App->audio->UnloadChunk(music);

	return true;
}

update_status ModuleCongratsScreen::Update()
{
	timer++;
	App->render->Blit(graphics, 0, 0, &background);

	//if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) {
	if(timer>250)
	{
		App->fade->FadeToBlack(App->congrats_screen, App->welcome_page, 2.0f);
	}

	return UPDATE_CONTINUE;
}