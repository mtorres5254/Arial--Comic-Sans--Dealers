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
#include "ModuleAudio.h"


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

	graphics = App->textures->Load("Assets/TitleScreen.png");
	music = App->audio->LoadMusic("Assets/start_music.ogg");
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


	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) {

		App->fade->FadeToBlack(App->welcome_page, App->scene_ken, 2.0f);
		App->audio->StopMusic(2500);
	}

	return UPDATE_CONTINUE;
}