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
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

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

	graphics = App->textures->Load("Assets/Images/Lose.png");
	music = App->audio->LoadMusic("Assets/Sound/lose_scene.ogg");
	App->audio->PlayMusic(music, 3000);
	
	
		
	
	App->UI->Disable();

	return true;
}

bool ModuleLoseScene::CleanUp() {

	LOG("Unloading Lose Screen");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(music);
	App->lose_scene->Disable();



	return true;
}

update_status ModuleLoseScene::Update() {

	App->render->Blit(graphics, 0, 0, &background);

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) {

		App->fade->FadeToBlack(App->lose_scene, App->welcome_page, 2.0f);
		App->audio->StopMusic(2500);
	}

	return UPDATE_CONTINUE;
}