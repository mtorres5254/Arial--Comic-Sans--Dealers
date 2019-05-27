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
	background.x = 0;
	background.y = 0;
	background.h = SCREEN_HEIGHT;
	background.w = SCREEN_WIDTH;
	pointer.x = 6;
	pointer.y = 7;
	pointer.h = 18;
	pointer.w = 20;

	finish = false;
	select = false;
	timer = 0;
}

ModuleWelcomePage::~ModuleWelcomePage()
{}

bool ModuleWelcomePage::Start()
{
	LOG("Loading WelcomePage");

	graphics = App->textures->Load("Assets/Images/TitleScreen.png");
	pointUI = App->textures->Load("Assets/Images/MenuPointer.png");
	music = App->audio->LoadMusic("Assets/Sound/Musics/start_music.ogg");
	App->audio->PlayMusic(music, 300);
	start_sound = App->audio->LoadChunk("Assets/Sound/start_sound.wav");
	App->render->camera.x = App->render->camera.y = 0;
	   
	return true;
}

bool ModuleWelcomePage::CleanUp()
{
	LOG("Unloading WelcomePage");

	App->textures->Unload(graphics);
	App->textures->Unload(pointUI);
	App->audio->UnloadMusic(music);

	return true;
}

update_status ModuleWelcomePage::Update()
{	
	App->render->Blit(graphics, 0, 0, &background);

	if (select == false)
	{
		App->render->Blit(pointUI, 100, 180, &pointer);
	}
	else
	{
		++timer;
		if(timer==40)
		{
			finish = true;
		}
		if (timer % 10 == 0)
		{
			App->render->Blit(pointUI, 100, 180, &pointer);
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) 
	{
		select = true;
	}


	if (finish==true)
	{
		App->fade->FadeToBlack(App->welcome_page, App->selectionScene, 2.0f);
		App->audio->PlayChunk(start_sound, 0);
		App->audio->StopMusic(250);
	}
	return UPDATE_CONTINUE;
}