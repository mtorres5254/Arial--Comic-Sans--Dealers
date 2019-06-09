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
	persones_relax.speed = 0.05f;
	persones_relax.loop = true;

	insert_coin.PushBack({ 25,593,184,16 });
	insert_coin.PushBack({ 25,1000,184,16 });
	insert_coin.speed = 0.01f;
	insert_coin.loop = true;
	
	logo.PushBack({65,1,69,36});
	logo.PushBack({70,40,62,55});
	logo.PushBack({79,95,52,58});
	logo.PushBack({67,161,76,38});
	logo.PushBack({143,1,71,61});
	logo.PushBack({153,68,44,66});
	logo.PushBack({150,139,69,46});
	logo.PushBack({248,5,64,71});
	logo.PushBack({238,82,52,71});
	logo.PushBack({233,161,64,64});
	logo.speed = 0.1f;
	logo.loop = false;

	persona1 = { 571,349,206,276 };
	persona2 = { 813,309,406,148 };

	personaDest = { 57,84,108,144 };
	persona2Dest = { 100,150,220,100 };


	logo_Rect = {62,677,576,222};
	logo_RectDest = {48,32,288,100};

	TheWorldWarrior = { 643,698,241,12 };
	TheWorldWarriorDest = { 64,146,241,12 };
	Capcom = { 707,744,118,8 };
	CapcomDest = { 128,192,118,8 };

}

ModuleWelcomePage::~ModuleWelcomePage()
{}

bool ModuleWelcomePage::Start()
{
	LOG("Loading WelcomePage");

	graphics = App->textures->Load("Assets/Images/intro_fons.png");
	persones = App->textures->Load("Assets/Images/intro_npc.png");
	logo_texture = App->textures->Load("Assets/Images/logo.png");

	music = App->audio->LoadMusic("Assets/Sound/Musics/start_music.ogg");
	punchEffect = App->audio->LoadChunk("Assets/Sound/Effects/high_attack.wav");

	App->audio->PlayMusic(music,1000);
	App->render->camera.x = App->render->camera.y = 0;

	personaDest = { 57,84,108,144 };
	persona2Dest = { 100,150,220,80 };
	logo_RectDest = { 48,32,288,100 };
	TheWorldWarriorDest = { 64,146,241,12 };
	CapcomDest = { 128,192,118,8 };

	animcount = 0;
	blackcount = 0;
	bool Anim2 = false;
	bool time = false;
	bool cameraMove = false;
	bool punch = false;
	bool logo_anim = false;

	return true;
}

bool ModuleWelcomePage::CleanUp()
{
	LOG("Unloading WelcomePage");

	App->textures->Unload(graphics);
	App->textures->Unload(persones);
	App->audio->UnloadMusic(music);

	return true;
}

update_status ModuleWelcomePage::Update()
{	
	//Animacio i moviment de l'edifici
	if (blackcount <= 170) {
		if (fons.y == 0) {
			blackcount++;
		}

		App->render->RectBlit(fons, graphics);

		if (Anim2 == false) {
			App->render->RectBlit2(persones, &persones_relax.GetCurrentFrame(), &personesRect);
			animcount++;
			if (animcount >= 235) {
				Anim2 = true;

				animcount = 0;
			}
		}

		if (Anim2 == true) {
			if (punch == false) {
				App->audio->PlayChunk(punchEffect, 1);
				punch = true;
			}

			App->render->RectBlit2(persones, &persona2, &persona2Dest);
			App->render->RectBlit2(persones, &persona1, &personaDest);
			if (time = false) {
				time = true;
				actualtime = SDL_GetTicks();
			}
			Persona1Move();
			Persona2Move(actualtime, 9000);
		}

		if (cameraMove == true) {
			fons.y -= 0.3f;
		}

		if (blackcount >= 80) {
			App->render->DrawQuad(fons, 0, 0, 0, blackcount * 1.5);
		}

		App->render->Blit(persones, 110, 180, &insert_coin.GetCurrentFrame(), 1.0f);
	}
	//Animació i moviment del logo
	if (blackcount > 170) {
		App->render->DrawQuad(fons, 0, 0, 0, 255);

		if (logo_anim == false) {
			App->render->Blit(logo_texture, 220, 100, &logo.GetCurrentFrame(), 1.0f);
			if ((int)logo.current_frame == 9) { logo_anim = true; }
		}
		if (logo_anim == true) {
			App->render->RectBlit2(persones, &logo_Rect, &logo_RectDest);

			if (TWWMove == false) {
				TheWorldWarriorDest = { 384,146,241,12 };
				TWWMove = true;
			}
			

			if (TheWorldWarriorDest.x > 64) {
				TheWorldWarriorDest.x -= 2;
			}
			
			App->render->RectBlit2(persones, &TheWorldWarrior, &TheWorldWarriorDest);

			App->render->RectBlit2(persones, &Capcom, &CapcomDest);
		}
	}

	

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1 || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_START] == 1) {
		App->audio->StopMusic(300);
		App->fade->FadeToBlack(App->welcome_page, App->selectionScene);
	}
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_X] == 1) {   // TREURE ABANS D?ENVIAR
		App->audio->StopMusic(300);
		App->fade->FadeToBlack(App->welcome_page, App->scene_dhalsim);
	}


	return UPDATE_CONTINUE;
}

void ModuleWelcomePage::Persona1Move() {
	personaDest.x -= 2;
	personaDest.y += 1;
}

void ModuleWelcomePage::Persona2Move(Uint32 time, int delay) {
	if (time + delay < SDL_GetTicks()) {
		persona2Dest.y += 1;
		cameraMove = true;
	}
}