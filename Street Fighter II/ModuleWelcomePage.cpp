#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleWelcomePage.h"
#include "ModuleAudio.h"
#include "ModuleLoseScene.h"


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

	graphics = App->textures->Load("Assets/Images/TitleScreen.png");
	music = App->audio->LoadMusic("Assets/Sound/start_music.ogg");
	App->audio->PlayMusic(music, 3000);

	App->render->camera.x = App->render->camera.y = 0;
	   
	return true;
}

bool ModuleWelcomePage::CleanUp()
{
	LOG("Unloading WelcomePage");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(music);
	App->welcome_page->Disable();


	return true;
}

update_status ModuleWelcomePage::Update()
{
	
	App->render->Blit(graphics, 0, 0, &background);


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->welcome_page, App->scene_ryu, 2.0f);
		App->audio->StopMusic(2500);
	}
	if (App->input->keyboard[SDL_SCANCODE_F9] == 1) {

		App->fade->FadeToBlack(App->welcome_page, App->lose_scene, 2.0f);
		App->audio->StopMusic(250);
	}

	return UPDATE_CONTINUE;
}