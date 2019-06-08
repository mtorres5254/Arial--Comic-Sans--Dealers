#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleWelcomePage.h"
#include "ModuleAudio.h"
#include "ModuleSceneDhalsim.h"
#include "ModuleCharacterSelection.h"


ModuleWelcomePage::ModuleWelcomePage()
{
	intro.PushBack({ 0,0,384,224 });
	intro.PushBack({ 387,0,384,224 });
	intro.PushBack({ 774,0,384,224 });
	intro.PushBack({ 1161,0,384,224 });
	intro.PushBack({ 1551,0,384,224 });
	intro.PushBack({ 0,227,384,224 });
	intro.PushBack({ 390,230,384,224 });
	intro.PushBack({777,230,384,224 });
	intro.PushBack({ 1167,230,384,224 });
	intro.PushBack({ 1557,230,384,224 });
	intro.PushBack({ 0,460,384,224 });
	intro.PushBack({ 393,460,384,224 });
	intro.PushBack({ 783,460,384,224 });
	intro.PushBack({ 1173,460,384,224 });
	intro.PushBack({ 1582,460,384,224 });
	intro.PushBack({ 0,717,384,224 });
	intro.PushBack({ 399,717,384,224 });
	intro.PushBack({ 789,717,384,224 });
	intro.PushBack({ 1198,717,384,224 });
	intro.PushBack({ 1615,717,384,224 });
	intro.PushBack({ 0,972,384,224 });
	intro.PushBack({ 405,972,384,224 });
	intro.PushBack({ 814,972,384,224 });
	intro.PushBack({ 1231,972,384,224 });
	intro.speed = 0.06f;
	intro.loop = false;
}

ModuleWelcomePage::~ModuleWelcomePage()
{}

bool ModuleWelcomePage::Start()
{
	LOG("Loading WelcomePage");

	graphics = App->textures->Load("Assets/Images/intro.png");
	music = App->audio->LoadMusic("Assets/Sound/Musics/start_music.ogg");
	App->audio->PlayMusic(music,1000);
	App->render->camera.x = App->render->camera.y = 0;
	return true;
}

bool ModuleWelcomePage::CleanUp()
{
	LOG("Unloading WelcomePage");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(music);

	return true;
}

update_status ModuleWelcomePage::Update()
{	

	App->render->Blit(graphics, 0, 0, &intro.GetCurrentFrame());

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_START] == 1 || (int)intro.current_frame == 23) {
		App->fade->FadeToBlack(App->welcome_page, App->scene_dhalsim);
		App->audio->StopMusic(250);
	}

	return UPDATE_CONTINUE;
}
