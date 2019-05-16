#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"
#include "ModuleChunLi.h"
#include "ModuleChunLi2.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleSceneDhalsim.h"
#include <string.h>



ModuleUI::ModuleUI() {

	//HealthBar1
	HealthBar1.x = 43;
	HealthBar1.y=  24;
	HealthBar1.w = 153;
	HealthBar1.h = 19;

	RedBar1.x = 43;
	RedBar1.y = 54;
	RedBar1.w = 153;
	RedBar1.h = 19;

	//HealthBar2
	HealthBar2.x = 43;
	HealthBar2.y = 24;
	HealthBar2.w = 153;
	HealthBar2.h = 19;

	RedBar2.x = 43;
	RedBar2.y = 54;
	RedBar2.w = 153;
	RedBar2.h = 19;

	//KOBar
	KObar.x = 205;
	KObar.y = 18;
	KObar.w = 27;
	KObar.h = 24;

	//RoundBar1
	RoundBar1.x = 247;
	RoundBar1.y= 39;
	RoundBar1.w = 17;
	RoundBar1.h = 20;

	//RoundBar2
	RoundBar2.x = 247 ;
	RoundBar2.y = 39;
	RoundBar2.w = 17;
	RoundBar2.h = 20;
	
	KOanim.PushBack({205,18,27,24});
	KOanim.PushBack({205,56,27,24});
	KOanim.speed = 0.1f;
}

ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
	LOG("Loading UI textures");
	App->font->Enable();
	bool ret = true;

	graphics1 = App->textures->Load("Assets/Images/Battle_HUD.png"); 
	font_id = App->font->Load("Assets/Images/font1.png", "abcdefghijklmnopqrstuvwxyz.+-1234567890 ", 1);
	font_Rounds = App->font->Load("Assets/Images/font_round.png", "r123", 2);

	VoiceRound = App->audio->LoadChunk("Assets/Sound/Round.wav");
	Voice1 = App->audio->LoadChunk("Assets/Sound/1.wav");
	Voice2 = App->audio->LoadChunk("Assets/Sound/2.wav");
	Voice3 = App->audio->LoadChunk("Assets/Sound/3.wav");
	VoiceFight = App->audio->LoadChunk("Assets/Sound/Fight.wav");

	timenow = SDL_GetTicks();
	time = 99;
	Counter1 = 9; //unit
	Counter2 = 9; //decimal

	round = 1;
	
	return ret;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading UI graphics");

	App->textures->Unload(graphics1);

	return true;
}

update_status ModuleUI:: Update()
{
	//Logic
	HealthBar1.w = App->chunli->healthbar;
	HealthBar2.w = App->chunli2->healthbar;

	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN && GamepadInfo == false) {
		GamepadInfo = true;
	}
	else if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN && GamepadInfo == true) {
		GamepadInfo = false;
	}

	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_DOWN && Historyinfo == false) {
		Historyinfo = true;
	}
	else if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_DOWN && Historyinfo == true) {
		Historyinfo = false;
	}
	
	//Render
	Counter();
	if (GamepadInfo == true) {
		GamepadDebug();
	}

	if (Historyinfo == true) {
		HistoryDebug();
	}
	//
	for (int i = 0; i < 20; i++) {
		if (Hispos[i].occuped == true) {
			Hispos[i].count++;
			if (Hispos[i].count >= 300) {
				Hispos[i].occuped = false;
				Hispos[i].count = 0;
			}
		}
	}

	App->font->BlitText(30, 43, font_id, "chun");
	App->font->BlitText(95, 43, font_id, "li");

	App->font->BlitText(265, 43, font_id, "chun");
	App->font->BlitText(330, 43, font_id, "li");


	App->render->Blit(graphics1, SCREEN_WIDTH / 2 - RedBar1.w - KObar.w / 2, 20, &RedBar1, false);
	App->render->Blit(graphics1, SCREEN_WIDTH / 2 - HealthBar1.w - KObar.w / 2, 20, &HealthBar1, false);
	App->render->BlitSym(graphics1, SCREEN_WIDTH / 2 + KObar.w / 2, 20, &RedBar2, false);
	App->render->BlitSym(graphics1, SCREEN_WIDTH / 2 + KObar.w / 2, 20, &HealthBar2, false);


	if (App->chunli->life > 250 && App->chunli2->life > 250) {
		App->render->Blit(graphics1, SCREEN_WIDTH / 2 - (KObar.w / 2), 15, &KObar, false);
	}
	else {
		App->render->Blit(graphics1, SCREEN_WIDTH / 2 - (KObar.w / 2), 15, &KOanim.GetCurrentFrame(), false);
	}


	if (App->chunli2->victorycount == 1 || App->chunli2->victorycount == 2) {
		App->render->Blit(graphics1, (SCREEN_WIDTH / 2)-153-(KObar.w/2)-20, 20, &RoundBar1, false);
		victorycount = 1;
	}

	if (App->chunli->victorycount == 1 || App->chunli->victorycount == 2) {
	
		App->render->Blit(graphics2, (SCREEN_WIDTH / 2) + 153 + (KObar.w / 2) , 20, &RoundBar2, false);		
		if(App->chunli->DeathCount==0)
		victorycount1 = 1;
	}
	
	
	return UPDATE_CONTINUE;
}


void ModuleUI::Counter() 
{
	if (timenow > 0)
	{
		if (SDL_GetTicks() - timenow > 1000) {			
			time--;
			
			Counter1--;
			if (Counter1 == -1) {
				Counter1 = 9;
				Counter2--;

				if (Counter2 <= 0) {
					Counter2 = 0;
				}

			}		
			timenow = SDL_GetTicks();		
		}
	}

	switch (Counter2)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2), 45, font_id, "0");
		break;
	}
	switch (Counter1)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 - (KObar.w / 2) + 16, 45, font_id, "0");
		break;
	}
}

void ModuleUI::GamepadDebug() {
	//escriure aqui el codi que mostra la info debug
	if (App->input->Gamepad == false && App->input->Gamepad2 == false) {
		App->font->BlitText(0, 0, font_id, "No gamepads conected");
	}
	else if (App->input->Gamepad == true) {
		App->font->BlitText(0, 0, font_id, "Player 1 controller conected");
	}
	else if (App->input->Gamepad == true && App->input->Gamepad2 == true) {
		App->font->BlitText(0, 0, font_id, "Player 1 and Player 2controller conected");
	}	
}

void ModuleUI::HistoryDebug() {
	for (int i = 0; i < 20; i++) {
		Hispos[i].Positions = new SDL_Point({0, 150 - (14 * i)});
	}
	for (int a = 0; a < SDL_CONTROLLER_BUTTON_MAX; a++) {
		for (int i = 0; i < MAX_HISTORY; i++) {
			if (App->input->history[i].keyboard[a] != KEY_IDLE) {
				if (App->input->history[i].keyboard[a] != App->input->history[i].keyboard[a]) {
					for (int j = 0; j < 20; j++) {
						if (Hispos[j].occuped == false) {
							App->font->BlitText(Hispos[j].Positions->x, Hispos[j].Positions->y, font_id, "hola");
						}
					}
				}
			}
		}
	}
	


}

