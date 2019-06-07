#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleLoseScene.h"
#include "ModuleWelcomePage.h"

ModuleLoseScene::ModuleLoseScene() {
	background.x = 0;
	background.y = 0;
	background.h = SCREEN_HEIGHT;
	background.w = SCREEN_WIDTH;
}

ModuleLoseScene::~ModuleLoseScene() {

}

bool ModuleLoseScene::Start() {
	LOG("Loading Lose Screen");
	timer = 0;
	graphics = App->textures->Load("Assets/Images/Lose.png");
	music = App->audio->LoadChunk("Assets/Sound/Effects/lose_screen.wav");
	App->audio->PlayChunk(music, 1);
	App->render->camera.x = App->render->camera.y = 0;

	return true;
}

bool ModuleLoseScene::CleanUp() {

	LOG("Unloading Lose Screen");

	App->textures->Unload(graphics);
	App->audio->UnloadChunk(music);

	return true;
}

update_status ModuleLoseScene::Update() {

	App->render->Blit(graphics, 0, 0, &background);
	timer++;

	//if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) 
	if (timer > 250)
	{

		App->fade->FadeToBlack(App->lose_scene, App->welcome_page, 2.0f);
	}

	return UPDATE_CONTINUE;
}