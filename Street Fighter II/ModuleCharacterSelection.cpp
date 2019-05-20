#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleCharacterSelection.h"
#include "ModuleAudio.h"
#include "ModuleLoseScene.h"
#include "ModuleSceneDhalsim.h"

ModuleCharacterSelection::ModuleCharacterSelection()
{
	//Background
	background.x = 0;
	background.y = 0;
	background.h = SCREEN_HEIGHT;
	background.w = SCREEN_WIDTH;

	//P2Pointer
	P2Pointer.x = 395;
	P2Pointer.y = 311;
	P2Pointer.w = 87;
	P2Pointer.h = 133;

	//P1Pointer
	P1Pointer.x = 160;
	P1Pointer.y = 311;
	P1Pointer.w = 87;
	P1Pointer.h = 133;
}

ModuleCharacterSelection::~ModuleCharacterSelection()
{}


bool ModuleCharacterSelection::Start()
{
	LOG("Loading characters selection");

	graphicsBack = App->textures->Load("Assets/Images/Player_Select.png");
	graphicsUI = App->textures->Load("Assets/Images/Character_Selection_UI.png");
	//music = App->audio->LoadMusic("Assets/Sound/Musics/start_music.ogg");
	//App->audio->PlayMusic(music, 300);
	//start_sound = App->audio->LoadChunk("Assets/Sound/start_sound.wav");
	App->render->camera.x = App->render->camera.y = 0;

	return true;
}

bool ModuleCharacterSelection::CleanUp()
{
	LOG("Unloading Selection page");

	App->textures->Unload(graphicsBack);
	App->textures->Unload(graphicsUI);
	//App->audio->UnloadMusic(music);

	return true;
}

update_status ModuleCharacterSelection::Update()
{
	App->render->Blit(graphicsBack, 0, 0, &background);

	if (map == false)
	{
		if (hide == false)
		{
			App->render->Blit(graphicsUI, -340, 160, &P1Pointer);
			App->render->Blit(graphicsUI, -340, 160, &P2Pointer);
			hide = true;
		}
			
	}
	else
	{
		if (hide == false)
		{
			App->render->Blit(graphicsUI, -340, 160, &P1Pointer);
			hide = true;
		}	
	}
	
	if (p1 == true && p2 == true)
	{
		map = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_F11] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		p1 = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_F12] == KEY_DOWN  || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		p2 = true;
	}

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) && map==true) {		
		App->fade->FadeToBlack(App->selectionScene, App->scene_dhalsim, 2.0f);
		App->audio->PlayChunk(start_sound, 0);
		App->audio->StopMusic(250);
	}

	return UPDATE_CONTINUE;
}