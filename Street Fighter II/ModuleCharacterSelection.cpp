#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleCharacterSelection.h"
#include "ModuleAudio.h"
#include "ModuleSceneDhalsim.h"

/*
 *Render is not scaling background -> solve 
*/

ModuleCharacterSelection::ModuleCharacterSelection()
{
	//Background
	background.x = 0;
	background.y = 0;
	background.h = 705;//705
	background.w = 934;//934

	//P1Pointer
	P1Pointer.x = 332;
	P1Pointer.y = 706;
	P1Pointer.w = 87;
	P1Pointer.h = 133;

	//P2Pointer
	P2Pointer.x = 519;
	P2Pointer.y = 706;
	P2Pointer.w = 87;
	P2Pointer.h = 133;
}

ModuleCharacterSelection::~ModuleCharacterSelection()
{}


bool ModuleCharacterSelection::Start()
{
	LOG("Loading characters selection");

	graphics = App->textures->Load("Assets/Images/Player_Select.png");
	music = App->audio->LoadMusic("Assets/Sound/Musics/start_music.ogg");
	App->audio->PlayMusic(music, 300);
	start_sound = App->audio->LoadChunk("Assets/Sound/start_sound.wav");
	App->render->camera.x = App->render->camera.y = 0;

	return true;
}

bool ModuleCharacterSelection::CleanUp()
{
	LOG("Unloading Selection page");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(music);

	return true;
}

update_status ModuleCharacterSelection::Update()
{
	App->render->Blit(graphics, 0, 0, &background);

	if (map == false)
	{
		if (p1 == true)
		{
			App->render->Blit(graphics, 100, 100, &P1Pointer);
		}
		else
		{
			if (frame == 3)
			{
				App->render->Blit(graphics, 100, 100, &P1Pointer);				
			}
		}


		if (p2 == true)
		{
			App->render->Blit(graphics, 100, 150, &P2Pointer);
		}
		else
		{
			if (frame == 3)
			{
				App->render->Blit(graphics, 130, 100, &P2Pointer);
			}
		}	
	}
	else
	{
		if (frame == 3)
		{
			App->render->Blit(graphics, 150, 100, &P1Pointer);
			frame = 0;
		}	
	}
	if (frame == 3) frame = 0;
	frame++;
	
	if (p1 == true && p2 == true)
	{
		map = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		p1 = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_DOWN  || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		p2 = true;
	}

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) && map==true) {		
		App->fade->FadeToBlack(App->selectionScene, App->scene_dhalsim, 2.0f);
		App->audio->PlayChunk(start_sound, 0);
		App->audio->StopMusic(250);
	}

	////Temporal////
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		App->fade->FadeToBlack(App->selectionScene, App->scene_dhalsim, 2.0f);
		App->audio->PlayChunk(start_sound, 0);
		App->audio->StopMusic(250);
	}
	//////////////
	return UPDATE_CONTINUE;
}