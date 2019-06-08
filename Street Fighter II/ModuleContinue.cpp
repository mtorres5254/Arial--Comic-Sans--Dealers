
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "Animation.h"

#include "ModuleContinue.h"
#include "ModuleSceneDhalsim.h"
#include "ModuleWelcomePage.h"
#include "ModuleAudio.h"



ModuleContinue::ModuleContinue() {

}

ModuleContinue::~ModuleContinue()
{}

bool ModuleContinue:: Start() {

	LOG("Loading Continue selection");

	Enable();
	
	graphics1 = App->textures->Load("Assets/Images/ContinueNumbers.png");
	graphics2 = App->textures->Load("Assets/Images/ContinuechunLi1.png");
	music = App->audio->LoadMusic("Assets/Sound/Musics/continue.ogg");

	ChunLi.PushBack1({ 3, 3, 102, 95}, {}, {}, {}, {}, {}, {});
	ChunLi.PushBack1({ 3, 3, 102, 95 }, {}, {}, {}, {}, {}, {});
	ChunLi.PushBack1({ 110, 3, 99,95 }, {}, {}, {}, {}, {}, {});
	ChunLi.PushBack1({ 3, 3, 102, 95 }, {}, {}, {}, {}, {}, {});
	ChunLi.PushBack1({ 215,4 , 101,94 }, {}, {}, {}, {}, {}, {});
	ChunLi.speed = 0.02f;


	numbers.PushBack1({ 65, 0, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.PushBack1({ 130, 0, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.PushBack1({ 195, 0, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.PushBack1({ 0, 97, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.PushBack1({ 65, 97, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.PushBack1({ 130, 97, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.PushBack1({ 195, 97, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.PushBack1({ 261, 0, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.PushBack1({ 261, 97, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.PushBack1({ 0, 0, 63, 97 }, {}, {}, {}, {}, {}, {});
	numbers.speed = 0.01f;
	numbers.loop = false;


	App->audio->PlayMusic(music, 0);
	return true;
}

update_status ModuleContinue::Update() {

	Animation* current_animation1 = &ChunLi;
	Animation* current_animation2 = &numbers;

	App->render->Blit(graphics2, 200, 70, &(ChunLi.GetCurrentFrame()), 0.92f);
	App->render->Blit(graphics1, 350, 70, &(numbers.GetCurrentFrame()), 0.92f);

	if (App->input->keyboard[SDL_SCANCODE_ESCAPE] == 1) {
		LOG("YES0");
		App->fade->FadeToBlack(App->continu, App->welcome_page, 2.0f);
		//App->audio->StopMusic(2000);

	}

	return UPDATE_CONTINUE;
}

bool ModuleContinue::CleanUp() {

	LOG("Unloading Selection page");
	
	App->textures->Unload(graphics1);
	App->textures->Unload(graphics2);
	
	App->audio->UnloadMusic(music);
	return true;
}