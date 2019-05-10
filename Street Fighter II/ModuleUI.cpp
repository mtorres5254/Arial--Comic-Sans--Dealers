#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"
#include "ModuleChunLi.h"
#include "ModuleChunLi2.h"
#include "ModuleUI.h"
#include "ModuleChunLi.h"


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
	font_id = App->font->Load("Assets/Images/font1.png", "abcdefghijklmnopqrstuvwxyz.+-1234567890", 1);
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

	//Render
	Counter();

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

void ModuleUI::Round1() {
	App->font->BlitText(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, font_Rounds, "r1");
	App->audio->PlayChunk(VoiceRound, 0);
	App->audio->PlayChunk(Voice1, 0);
	App->audio->PlayChunk(VoiceFight, 0);
}
void ModuleUI::Round2() {
	App->font->BlitText(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, font_Rounds, "r2");
	App->audio->PlayChunk(VoiceRound, 0);
	App->audio->PlayChunk(Voice2, 0);
	App->audio->PlayChunk(VoiceFight, 0);
}
void ModuleUI::Round3() {
	App->font->BlitText(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, font_Rounds, "r3");
	App->audio->PlayChunk(VoiceRound, 0);
	App->audio->PlayChunk(Voice3, 0);
	App->audio->PlayChunk(VoiceFight, 0);
}

void ModuleUI::Counter() {
	if (timenow > 0)
	{
		if (SDL_GetTicks() - timenow > 1000) {			
			time--;
			//LOG("%d", time);
			Counter1--;
			if (Counter1 == -1) { //if ==0 jump from x1 to x9 (21 to 19 for example)
				Counter1 = 9;
				Counter2--;
				
				if (Counter2 == 0) {
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
