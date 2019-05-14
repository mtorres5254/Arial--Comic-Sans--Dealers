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
	ground.x = 234;
	ground.y = 750;
	ground.w = 821;
	ground.h = 91;

	// Background 
	background.x = 21;
	background.y = 137;
	background.w = 622;
	background.h = 177;

	// Left elephant in the background
	
	

	leftelephant1.PushBack1({ 27,34,115,84 }, {}, {}, {}, {}, {});
	leftelephant1.PushBack1({ 147,34,115,84 }, {}, {}, {}, {}, {});
	leftelephant1.PushBack1({ 267,34,115,84 }, {}, {}, {}, {}, {});
	leftelephant1.PushBack1({ 147,34,115,84 }, {}, {}, {}, {}, {});
	leftelephant1.speed = 0.05f;

	leftelephant2.PushBack1({ 761,195,165,133 }, {}, {}, {}, {}, {});
	leftelephant2.PushBack1({ 928,195,220,133 }, {}, {}, {}, {}, {});
	leftelephant2.PushBack1({ 1150,195,229,133 }, {}, {}, {}, {}, {});
	leftelephant2.PushBack1({ 928,195,220,133 }, {}, {}, {}, {}, {});
	leftelephant2.speed = 0.05f;

	leftelephant3.PushBack1({ 563,566,217,175 }, {}, {}, {}, {}, {});
	leftelephant3.PushBack1({ 783,566,291,175 }, {}, {}, {}, {}, {});
	leftelephant3.PushBack1({ 1077,566,302,175 }, {}, {}, {}, {}, {});
	leftelephant3.PushBack1({ 783,563,291,178 }, {}, {}, {}, {}, {});
	leftelephant3.speed = 0.05f;
	// Right elephant in the background




	rightelephant1.PushBack1({ 635,34,115,84 }, {},  {}, {}, {}, {});
	rightelephant1.PushBack1({ 515,34,115,84 }, {}, {}, {}, {}, {});
	rightelephant1.PushBack1({ 395,34,115,84 }, {}, {}, {}, {}, {});
	rightelephant1.PushBack1({ 515,34,115,84 }, {}, {}, {}, {}, {});
	rightelephant1.speed = 0.05f;

	rightelephant2.PushBack1({ 1213,36,165,133 }, {}, {}, {}, {}, {});
	rightelephant2.PushBack1({ 991,36,220,133 }, {},  {}, {}, {}, {});
	rightelephant2.PushBack1({ 762,36,300,133 }, {}, {}, {}, {}, {});
	rightelephant2.PushBack1({ 991,36,220,133 }, {}, {}, {}, {}, {});
	rightelephant2.speed = 0.05f;

	
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
	App->render->Blit(graphics, -12, -16, &background, 0.92f); // background
	
	
	
	App->render->Blit(graphics, -56, 133, &ground);
	App->render->Blit(graphics, 107, 63, &(leftelephant1.GetCurrentFrame()), 0.92f);
	App->render->Blit(graphics, 378, 63, &(rightelephant1.GetCurrentFrame()), 0.92f); // Right elephant in the background 

//	App->render->Blit(graphics, -38, 50, &(leftelephant2.GetCurrentFrame()), 0.92f);//Left elephant in the background 
	//App->render->Blit(graphics, 432, 50, &(rightelephant2.GetCurrentFrame()), 0.92f);

	//App->render->Blit(graphics, -195, 50, &(leftelephant3.GetCurrentFrame()), 0.92f);
	
	roundpoints();
	fadeto();
	
	if (App->chunli2->position.x - App->chunli->position.x < App->render->camera.w + 33) {
			
		App->render->camera.x = -((App->chunli->position.x + App->chunli2->position.x) / 2 - App->render->camera.w / 2 + 33);


	}
	if (App->render->camera.x >= background.x - 10) {
		App->render->camera.x = background.x - 10;
		
	}
	
	if (App->render->camera.x <= (background.x - background.w) + SCREEN_WIDTH-28) {
		App->render->camera.x = (background.x - background.w) + SCREEN_WIDTH-28;
		
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneDhalsim::roundpoints() {

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
}

void ModuleSceneDhalsim::fadeto() {

	if (App->chunli->victorycount == 2) {
		App->fade->FadeToBlack(App->scene_dhalsim, App->lose_scene, 2.0f);
		App->audio->StopMusic(250);
	}

	if (App->chunli2->victorycount == 2) {
		App->fade->FadeToBlack(App->scene_dhalsim, App->congrats_screen, 2.0f);
		App->audio->StopMusic(250);
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->scene_dhalsim, App->congrats_screen, 2.0f);
		App->audio->StopMusic(2000);

	}
}