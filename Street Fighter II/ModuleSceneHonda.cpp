#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneHonda.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleAudio.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleSceneKen.h"
#include "ModuleCongratsScreen.h"
// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneHonda::ModuleSceneHonda()
{
	// ground
	ground = {8, 376, 848, 64};

	// roof
	roof = {91, 7, 765, 49};

	// foreground
	foreground = {164, 66, 336, 51};

	// Background / sky
	background = {120, 128, 671, 199};

	// flag animation
	water.PushBack({8, 447, 283, 9});
	water.PushBack({296, 447, 283, 12});
	water.PushBack({588, 447, 283, 18});
	water.speed = 0.02f;
}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading background assets");
	
	graphics = App->textures->Load("Assets/honda_stage2.png");
	music = App->audio->LoadMusic("Assets/honda.ogg");
	App->audio->PlayMusic(music, 3000);
	App->player2->Enable();
	App->player->Enable();
	App->collision->Enable();
	return true;
}

// Load assets
bool ModuleSceneHonda::CleanUp()
{

	LOG("Unloading honda stage");
	
	App->textures->Unload(graphics);	
	App->audio->UnloadMusic(music);
	App->scene_honda->Disable();
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 160, &ground);
	App->render->Blit(graphics, 50, -15, &background, 0.75f); // back of the room
	
	App->render->Blit(graphics, 280, 125, &foreground);
	App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation
	App->render->Blit(graphics, 0, -16, &roof, 0.75f);


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->scene_honda, App->congrats_screen, 2.0f);
		App->audio->StopMusic(2000);

	}
	return UPDATE_CONTINUE;
}