#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneDhalsim.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleCongratsScreen.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleLoseScene.h"
#include "ModuleChunLi.h"
#include "ModuleChunLi2.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneDhalsim::ModuleSceneDhalsim()
{
	// Ground
	ground.x = 53;
	ground.y = 777;
	ground.w = 1302;
	ground.h = 73;

	// Background 
	background.x = 21;
	background.y = 137;
	background.w = 622;
	background.h = 177;

	// Left elephant in the background
	
	leftelephant.x = 26;
	leftelephant.y = 34;
	leftelephant.w = 115;
	leftelephant.h = 84;

	// Right elephant in the background

	rightelephant.x = 635;
	rightelephant.y = 34;
	rightelephant.w = 115;
	rightelephant.h = 84;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleSceneDhalsim::~ModuleSceneDhalsim()
{}

// Load assets
bool ModuleSceneDhalsim::Start()
{
	LOG("Loading Dhalsim scene");

	App->render->camera.x = -120;
	graphics = App->textures->Load("Assets/Images/Dhalsim_stage.png");
	music = App->audio->LoadMusic("Assets/Sound/Musics/dhalsim.ogg");
	App->audio->PlayMusic(music, 5000);
	//
	App->chunli->Enable();
	App->chunli2->Enable();
	App->collision->Enable();
	App->UI->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneDhalsim::CleanUp()
{
	LOG("Unloading Dhalsim scene");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(music);
	App->chunli->Disable();
	App->chunli2->Disable();
	App->collision->Disable();
	App->UI->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneDhalsim::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background); // background
	App->render->Blit(graphics, 119, 79, &leftelephant);  //Left elephant in the background 
	App->render->Blit(graphics, 390, 79, &rightelephant); // Right elephant in the background 
	App->render->Blit(graphics, -338, 176, &ground);

	if (App->chunli->victorycount == 2) {
		App->fade->FadeToBlack(App->scene_dhalsim, App->lose_scene, 2.0f);
		App->audio->StopMusic(250);
	}

	if (App->chunli2->victorycount == 2) {
		App->fade->FadeToBlack(App->scene_dhalsim, App->congrats_screen, 2.0f);
		App->audio->StopMusic(250);
	}

	if (App->UI->time <= 0) {
		if (App->chunli->life > App->chunli2->life) {
			App->chunli->victorycount++;
		}
		if (App->chunli->life < App->chunli2->life) {
			App->chunli2->victorycount++;
		}
		else
		{
			App->chunli->victorycount++;
			App->chunli2->victorycount++;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->scene_dhalsim, App->congrats_screen, 2.0f);
		App->audio->StopMusic(2000);

	}
	return UPDATE_CONTINUE;
}