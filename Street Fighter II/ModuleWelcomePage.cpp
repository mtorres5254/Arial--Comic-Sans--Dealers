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
	fons = { 0,608,714,397 };
	personesRect = { 49,134,285,90 };

	persones_relax.PushBack({ 24,34,533,162 });
	persones_relax.PushBack({ 24,24,533,162 });
	persones_relax.speed = 0.02f;
	persones_relax.loop = true;
}

ModuleWelcomePage::~ModuleWelcomePage()
{}

bool ModuleWelcomePage::Start()
{
	LOG("Loading WelcomePage");

	graphics = App->textures->Load("Assets/Images/intro_fons.png");
	persones = App->textures->Load("Assets/Images/intro_npc.png");
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

	App->render->RectBlit( fons,graphics);

	App->render->RectBlit2(persones,&persones_relax.GetCurrentFrame(), &personesRect);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_START] == 1) {
		App->fade->FadeToBlack(App->welcome_page, App->scene_dhalsim);
		App->audio->StopMusic(250);
	}

	return UPDATE_CONTINUE;
}
