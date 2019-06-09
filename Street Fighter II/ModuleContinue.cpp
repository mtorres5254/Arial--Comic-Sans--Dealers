
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
#include "ModuleFont.h"
#include "ModuleUI.h"

ModuleContinue::ModuleContinue() {

}

ModuleContinue::~ModuleContinue()
{}

bool ModuleContinue:: Start() {

	LOG("Loading Continue selection");


	Enable();
	
	App->render->camera.x = -120;
	graphics1 = App->textures->Load("Assets/Images/ContinueNumbers.png");
	graphics2 = App->textures->Load("Assets/Images/ContinuechunLi2.png");
	music = App->audio->LoadMusic("Assets/Sound/Musics/continue.ogg");
	number1 = App->audio->LoadChunk("Assets/Sound/Effects/1.wav");
	number2 = App->audio->LoadChunk("Assets/Sound/Effects/2.wav");
	number3 = App->audio->LoadChunk("Assets/Sound/Effects/3.wav");
	number4 = App->audio->LoadChunk("Assets/Sound/Effects/4.wav");
	number5 = App->audio->LoadChunk("Assets/Sound/Effects/5.wav");
	number6 = App->audio->LoadChunk("Assets/Sound/Effects/6.wav");
	number7 = App->audio->LoadChunk("Assets/Sound/Effects/7.wav");
	number8 = App->audio->LoadChunk("Assets/Sound/Effects/8.wav");
	number9 = App->audio->LoadChunk("Assets/Sound/Effects/9.wav");
	gameover = App->audio->LoadChunk("Assets/Sound/Effects/gameover.wav");
	continuechange= App->audio->LoadChunk("Assets/Sound/Effects/continue-change.wav");

	scream= App->audio->LoadChunk("Assets/Sound/Effects/chunLi_scream.wav");

	font_id = App->font->Load("Assets/Images/font2.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~'!@#$%^&*()-_+=[]{}| :;¨º<>,./?", 1);

	ChunLi.PushBack({ 3, 3, 102, 95 });
	ChunLi.PushBack({ 3, 3, 102, 95 });
	ChunLi.PushBack({ 110, 3, 99,95 });
	ChunLi.PushBack({ 3, 3, 102, 95 });
	ChunLi.PushBack({ 215,4 , 101,94 });
	ChunLi.speed = 0.02f;


	numbers.PushBack({ 65, 0, 63, 97 });
	numbers.PushBack({ 130, 0, 63, 97 });
	numbers.PushBack({ 195, 0, 63, 97 });
	numbers.PushBack({ 0, 97, 63, 97 });
	numbers.PushBack({ 65, 97, 63, 97 });
	numbers.PushBack({ 130, 97, 63, 97 });
	numbers.PushBack({ 195, 97, 63, 97 });
	numbers.PushBack({ 261, 0, 63, 97 });
	numbers.PushBack({ 261, 97, 63, 97 });
	numbers.PushBack({ 1, 194, 61, 94 });
	numbers.PushBack({ 0, 0, 63, 97 });
	
	numbers.speed = 0.01f;
	numbers.loop = false;

	background.x = -0;
	background.y = 0;
	background.h = SCREEN_HEIGHT;
	background.w = SCREEN_WIDTH;

	App->audio->PlayMusic(music, 0);


	done1 = false;
	done2 = false;
	done3 = false;
	done4 = false;
	done5 = false;
	done6 = false;
	done7 = false;
	done8 = false;
	done9 = false;
	done10 = false;
	done11 = false;

	numbers.Reset();
	ChunLi.Reset();
	return true;
}

update_status ModuleContinue::Update() {

	

	Animation* current_animation1 = &ChunLi;
	Animation* current_animation2 = &numbers;

	if(redscreen==6)
	App->render->Blit(graphics2, 200, 70, &(ChunLi.frames[4]), 0.92f);

	else {
		App->render->Blit(graphics2, 200, 70, &(ChunLi.GetCurrentFrame()), 0.92f);
	}

	
	App->render->Blit(graphics1, 350, 70, &(numbers.GetCurrentFrame()), 0.92f);

	if ((int)numbers.current_frame == 0 ) {
		
		if (!done1) {
			App->audio->PlayChunk(continuechange, 1);
			App->audio->PlayChunk(number9, 1);
			done1 = true;
		}		
		App->font->BlitText(0, 5, font_id, " CONTINUE?9");
	}
	if ((int)numbers.current_frame == 1 ) {

		if (!done2) {
			App->audio->PlayChunk(continuechange, 1);
			App->audio->PlayChunk(number8, 1);
			done2 = true;
		}
		App->font->BlitText(0, 5, font_id, " CONTINUE?8");
	}
	if ((int)numbers.current_frame == 2) {

		if (!done3) {
			App->audio->PlayChunk(continuechange, 1);
			App->audio->PlayChunk(number7, 1);
			done3 = true;

		}
		App->font->BlitText(0, 5, font_id, " CONTINUE?7");
	}
	if ((int)numbers.current_frame == 3) {

		if (!done4) {
			App->audio->PlayChunk(continuechange, 1);
			App->audio->PlayChunk(number6, 1);
			done4 = true;
		}
		App->font->BlitText(0, 5, font_id, " CONTINUE?6");
	}
	if ((int)numbers.current_frame == 4) {

		if (!done5) {
			App->audio->PlayChunk(continuechange, 1);
			App->audio->PlayChunk(number5, 1);
			done5 = true;
		}
		App->font->BlitText(0, 5, font_id, " CONTINUE?5");
		
	}
	if ((int)numbers.current_frame == 5) {

		if (!done6) {
			App->audio->PlayChunk(continuechange, 1);
			App->audio->PlayChunk(number4, 1);
			done6 = true;
		}
		App->font->BlitText(0, 5, font_id, " CONTINUE?4");
	}
	if ((int)numbers.current_frame == 6) {

		if (!done7) {
			App->audio->PlayChunk(continuechange, 1);
			App->audio->PlayChunk(number3, 1);
			done7 = true;
		}
		App->font->BlitText(0, 5, font_id, " CONTINUE?3");
	}
	if ((int)numbers.current_frame == 7) {

		if (!done8) {
			App->audio->PlayChunk(continuechange, 1);
			App->audio->PlayChunk(number2, 1);
			done8 = true;
		}
		App->font->BlitText(0, 5, font_id, " CONTINUE?2");
	}
	if ((int)numbers.current_frame == 8) {

		if (!done9) {
			App->audio->PlayChunk(continuechange, 1);
			App->audio->PlayChunk(number1, 1);
			done9 = true;

		}
		App->font->BlitText(0, 5, font_id, " CONTINUE?1");
	}
	if ((int)numbers.current_frame == 9) {

		if (!done10) {
			App->audio->PlayChunk(continuechange, 1);
			done10 = true;

		}
		App->font->BlitText(0, 5, font_id, " CONTINUE?0");
	}

	if ((int)numbers.current_frame == 10) {

		 if (redscreen == 5) {
			App->render->DrawQuad(background, 0, 0, 0, true);
			redscreen=0;
			stop = 1;
					
			}
		else if (redscreen == 4) {
			App->render->DrawQuad(background, 255, 0, 0, true);
			redscreen++;
		}
		else if (redscreen == 3) {
			App->render->DrawQuad(background, 0, 0, 0, true);
			redscreen++;
		}
		else if (redscreen == 2) {
			App->render->DrawQuad(background, 255, 0, 0, true);
			redscreen++;
		}
		else if (redscreen == 1) {
			App->render->DrawQuad(background, 0, 0, 0, true);
			redscreen++;
		}
		else if (!done11) {
			 App->audio->StopMusic(0);
			App->audio->PlayChunk(scream, 1);
			App->audio->PlayChunk(gameover, 1);
			App->render->DrawQuad(background, 255, 0, 0, true);
			redscreen++;
			done11 = true;

		}	

		App->font->BlitText(140, 120, font_id, " GAME OVER");
	}
	

	if (timer < 60 && !done10) {
		App->font->BlitText(230, 5, font_id, " INSERT COIN");
		timer++;
	}
	else if (timer < 120) {
		timer++;
	}
	else {
		timer = 0;
	}
	
	if (stop > 0 && stop < 120) {
		stop++;
	}
	else if (stop == 120) {
		stop = 0;		
		App->fade->FadeToBlack(App->continu, App->welcome_page, 1.0f);
	}
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		
		App->fade->FadeToBlack(App->continu, App->welcome_page, 1.0f);
		

	}

	return UPDATE_CONTINUE;
}

bool ModuleContinue::CleanUp() {

	LOG("Unloading Selection page");
	
	App->textures->Unload(graphics1);
	App->textures->Unload(graphics2);
	
	App->audio->UnloadMusic(music);
	App->audio->UnloadChunk(number1);
	App->audio->UnloadChunk(number2);
	App->audio->UnloadChunk(number3);
	App->audio->UnloadChunk(number4);
	App->audio->UnloadChunk(number5);
	App->audio->UnloadChunk(number6);
	App->audio->UnloadChunk(number7);
	App->audio->UnloadChunk(number8);
	App->audio->UnloadChunk(number9);
	App->audio->UnloadChunk(continuechange);
	App->audio->UnloadChunk(scream);
	App->audio->UnloadChunk(gameover);
	App->font->UnLoad(font_id);
	return true;
}