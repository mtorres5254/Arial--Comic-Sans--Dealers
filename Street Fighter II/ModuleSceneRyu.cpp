#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleCongratsScreen.h"
#include "ModuleAudio.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleLoseScene.h"



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneRyu::ModuleSceneRyu()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// foreground
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 521;
	foreground.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.PushBack({ 848, 208, 40, 40 });
	flag.PushBack({ 848, 256, 40, 40 });
	flag.PushBack({ 848, 304, 40, 40 });
	flag.speed = 0.08f;

	// Girl Animation
	girl.PushBack({ 624, 16, 32, 56 });
	girl.PushBack({ 624, 80, 32, 56 });
	girl.PushBack({ 624, 144, 32, 56 });
	girl.speed = 0.05f;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleSceneRyu::~ModuleSceneRyu()
{}

// Load assets
bool ModuleSceneRyu::Start()
{
	LOG("Loading Ryu scene");

	graphics = App->textures->Load("Assets/Images/ken_stage.png");
	music = App->audio->LoadMusic("Assets/Sound/ken.ogg");
	App->audio->PlayMusic(music, 5000);
	//
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	App->UI->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneRyu::CleanUp()
{
	LOG("Unloading Ryu scene");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(music);
	//
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();
	App->UI->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneRyu::Update()
{
	// Calculate boat Y position -----------------------------
	if (foreground_pos < -6.0f)
		forward = false;
	else if (foreground_pos > 0.0f)
		forward = true;

	if (forward)
		foreground_pos -= 0.02f;
	else
		foreground_pos += 0.02f;

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	App->render->Blit(graphics, 0, (int)foreground_pos, &foreground, 0.92f);
	App->render->Blit(graphics, 192, 104 + (int)foreground_pos, &(girl.GetCurrentFrame()), 0.92f); // girl animation

	App->render->Blit(graphics, 0, 170, &ground);

	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	
	if (App->player->victorycount == 2) {		
		App->fade->FadeToBlack(App->scene_ryu, App->lose_scene, 2.0f);
		App->audio->StopMusic(250);
	}

	if (App->player2->victorycount == 2) {
		App->fade->FadeToBlack(App->scene_ryu, App->congrats_screen, 2.0f);
		App->audio->StopMusic(250);
	}

	if (App->UI->time == 0) {
		if (App->player->life > App->player2->life) {
			App->player->victorycount++;
		}
		if (App->player->life < App->player2->life) {
			App->player2->victorycount++;
		}
	}
	return UPDATE_CONTINUE;
}