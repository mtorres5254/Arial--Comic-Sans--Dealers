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

	LicensedBy[0].x = 112;
	LicensedBy[0].y = 12;
	LicensedBy[0].h = 14;
	LicensedBy[0].w = 165;

	LicensedBy[1].x = 112;
	LicensedBy[1].y = 33;
	LicensedBy[1].h = 14;
	LicensedBy[1].w = 165;

	LicensedBy[2].x = 112;
	LicensedBy[2].y = 53;
	LicensedBy[2].h = 14;
	LicensedBy[2].w = 165;

	LicensedBy[3].x = 112;
	LicensedBy[3].y = 73;
	LicensedBy[3].h = 14;
	LicensedBy[3].w = 165;

	LicensedBy[4].x = 112;
	LicensedBy[4].y = 94;
	LicensedBy[4].h = 14;
	LicensedBy[4].w = 165;

	LicensedBy[5].x = 112;
	LicensedBy[5].y = 114;
	LicensedBy[5].h = 14;
	LicensedBy[5].w = 165;
	
	LicensedBy[6].x = 112;
	LicensedBy[6].y = 135;
	LicensedBy[6].h = 14;
	LicensedBy[6].w = 165;

	finish = false;
	select = false;
	Nintendo = true;
	timer = 0;
	aux = 0;
}

ModuleWelcomePage::~ModuleWelcomePage()
{}

bool ModuleWelcomePage::Start()
{
	LOG("Loading WelcomePage");

	graphics = App->textures->Load("Assets/Images/TitleScreen.png");
	pointUI = App->textures->Load("Assets/Images/MenuPointer.png");
	Licensed = App->textures->Load("Assets/Images/LicensedBy.png");
	music = App->audio->LoadMusic("Assets/Sound/Musics/start_music.ogg");
	//SelectFX = App->audio->LoadChunk("Assets/Sound/Musics/.ogg");
	//start_sound = App->audio->LoadChunk("Assets/Sound/start_sound.wav");
	App->render->camera.x = App->render->camera.y = 0;
	   
	return true;
}

bool ModuleWelcomePage::CleanUp()
{
	LOG("Unloading WelcomePage");

	App->textures->Unload(graphics);
	App->textures->Unload(pointUI);
	App->textures->Unload(Licensed);
	App->audio->UnloadMusic(music);
	//App->audio->UnloadChunk(SelectFX);

	return true;
}

update_status ModuleWelcomePage::Update()
{	
	if (Nintendo == true)
	{
		++timer;
		if (timer == 120)
		{
			Nintendo = false;
			timer = 0;
			App->audio->PlayMusic(music, 300);
		}
		if (timer < 95)App->render->Blit(Licensed, 120, 100, &LicensedBy[0]);
		if (timer > 94 && timer < 101)App->render->Blit(Licensed, 120, 100, &LicensedBy[1]);
		if (timer > 100 && timer < 106)App->render->Blit(Licensed, 120, 100, &LicensedBy[2]);
		if (timer > 105 && timer < 111)App->render->Blit(Licensed, 120, 100, &LicensedBy[3]);
		if (timer > 110 && timer < 116)App->render->Blit(Licensed, 120, 100, &LicensedBy[4]);
		if (timer > 115 && timer <119)App->render->Blit(Licensed, 120, 100, &LicensedBy[5]);
		if (timer > 118)App->render->Blit(Licensed, 120, 100, &LicensedBy[6]);
	}

	if (Nintendo == false)
	{
		App->render->Blit(graphics, 0, 0, &background);
		if (select == false)
		{
			App->render->Blit(pointUI, 100, 180, &pointer);
		}
		else
		{
			++timer;
			if (timer == 20)
			{
				finish = true;
			}
			if (timer % 7 == 0)
			{
				App->render->Blit(pointUI, 100, 180, &pointer);
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN)
		{
			select = true;
			//App->audio->PlayChunk(SelectFX, 0);
		}


		if (finish == true)
		{
			App->fade->FadeToBlack(App->welcome_page, App->selectionScene, 0.8f);
			//App->audio->PlayChunk(start_sound, 0);
			App->audio->StopMusic(250);
		}
	}

	return UPDATE_CONTINUE;
}