#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleChunLi.h"
#include "ModuleChunLi2.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleSceneDhalsim.h"


#include "SDL/include/SDL.h"



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
	font_Rounds = App->font->Load("Assets/Images/font_round.png", "DNORU0123456789 ", 2);
	font2 = App->font->Load("Assets/Images/font2.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~'!@#$%^&*()-_+=[]{}| :;��<>,./?", 3);
	timenow = SDL_GetTicks();

	sFight = App->audio->LoadChunk("Assets/Sound/Effects/Fight.wav");
	s1 = App->audio->LoadChunk("Assets/Sound/Effects/1.wav");
	s2 = App->audio->LoadChunk("Assets/Sound/Effects/2.wav");
	s3 = App->audio->LoadChunk("Assets/Sound/Effects/3.wav");
	sRound = App->audio->LoadChunk("Assets/Sound/Effects/Round.wav");

	time = 99;
	Counter1 = 9; //unit
	Counter2 = 9; //tens
	
	scoreP1 = 000000;
	scoreP2 = 000000;
	p1time = 0;
	p1life = 0;
	p2time = 0;
	p2life = 0;
	round1 = 0;

	return ret;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading UI graphics");

	App->textures->Unload(graphics1);

	App->font->UnLoad(font_id);
	App->font->UnLoad(font_Rounds);
	App->font->UnLoad(font2);
	
	App->audio->UnloadChunk(s1);
	App->audio->UnloadChunk(s2);
	App->audio->UnloadChunk(s3);
	App->audio->UnloadChunk(sFight);
	App->audio->UnloadChunk(sRound);
	return true;
}

update_status ModuleUI:: Update()
{
	//Logic
	HealthBar1.w = App->chunli->healthbar;
	HealthBar2.w = App->chunli2->healthbar;

	
	//Render
	Counter();
	PointsP1();
	PointsP2();
	if (GamepadInfo == true) {
		GamepadDebug();
	}

	if (Resultinfo >= 0) {
		Result();
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
		App->render->Blit(graphics1, (SCREEN_WIDTH / 2)+153+(KObar.w/2), 20, &RoundBar1, false);
		victorycount = 1;
	}

	if (App->chunli->victorycount == 1 || App->chunli->victorycount == 2) {
	
		App->render->Blit(graphics1, (SCREEN_WIDTH / 2) - 153 - (KObar.w / 2)-20 , 20, &RoundBar2, false);		
		if(App->chunli->DeathCount==0)
		victorycount1 = 1;
	}

	
	
	
	return UPDATE_CONTINUE;
}


void ModuleUI::Counter() 
{	
	if (timenow > 0)
	{
		if(App->chunli->lose == false && App->chunli2->lose == false)

		if (SDL_GetTicks() - timenow > 1000) 
		{		
			if (!round) {
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
				timer = 0;
			}
				
		}
	}

	if (time==99) {
		
		if (timer <120) {
			
			
			if (timer == 0) {
				
				App->audio->PlayChunk(sRound, 1);
			}
			if (timer == 40) {
				if (App->chunli->victorycount == 0 && App->chunli2->victorycount == 0)
				App->audio->PlayChunk(s1, 1);
				if ((App->chunli->victorycount == 1 && App->chunli2->victorycount == 0) || (App->chunli->victorycount == 0 && App->chunli2->victorycount == 1))
				App->audio->PlayChunk(s2, 1);
				if (App->chunli->victorycount == 1 && App->chunli2->victorycount == 1)
					App->audio->PlayChunk(s3, 1);
			}
			if (timer == 100) {
				App->audio->PlayChunk(sFight, 1);
			}		
			
			if (App->chunli->victorycount == 0 && App->chunli2->victorycount == 0)
			App->font->BlitText(SCREEN_WIDTH / 2 - 45, 85, font_Rounds, "ROUND 1");
			if ((App->chunli->victorycount == 1 && App->chunli2->victorycount == 0)||(App->chunli->victorycount == 0 && App->chunli2->victorycount == 1))
				App->font->BlitText(SCREEN_WIDTH / 2 - 45, 85, font_Rounds, "ROUND 2");
			if (App->chunli->victorycount == 1 && App->chunli2->victorycount == 1)
				App->font->BlitText(SCREEN_WIDTH / 2 - 45, 85, font_Rounds, "ROUND 3");


			App->font->BlitText(SCREEN_WIDTH / 2 - 47, 115, font2, "BATTLE 01");
			round = true;
			timer++;
		}	

		else {
			round = false;
			timer = 0;
		}
	}	

	else {
		round = false;
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

void ModuleUI::PointsP1()
{
	six = scoreP1 / 100000;
	five = scoreP1 / 10000 % 10;
	four = scoreP1 / 1000 % 10;
	three = scoreP1 / 100 % 10;
	two = scoreP1 / 10 % 10;
	one = scoreP1 % 10;

	
	switch (one)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 - (90), 5, font_id, "0");
		break;
	}

	switch (two)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 - (104), 5, font_id, "0");
		break;
	}

	switch (three)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 - (118), 5, font_id, "0");
		break;
	}

	switch (four)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 - (132), 5, font_id, "0");
		break;
	}

	switch (five)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 - (146), 5, font_id, "0");
		break;
	}

	switch (six)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 - (160), 5, font_id, "0");
		break;
	}
}

void ModuleUI::PointsP2()
{
	six = scoreP2 / 100000; 
	five = scoreP2 / 10000 % 10;
	four = scoreP2 / 1000 % 10;
	three = scoreP2 / 100 % 10;
	two = scoreP2 / 10 % 10;
	one = scoreP2 % 10;

	switch (one)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 + (150), 5, font_id, "0");
		break;
	}

	switch (two)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 + (136), 5, font_id, "0");
		break;
	}

	switch (three)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 + (122), 5, font_id, "0");
		break;
	}

	switch (four)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 + (108), 5, font_id, "0");
		break;
	}

	switch (five)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 + (94), 5, font_id, "0");
		break;
	}

	switch (six)
	{
	case 9:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "9");
		break;
	case 8:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "8");
		break;
	case 7:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "7");
		break;
	case 6:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "6");
		break;
	case 5:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "5");
		break;
	case 4:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "4");
		break;
	case 3:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "3");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "2");
		break;
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "1");
		break;
	case 0:
		App->font->BlitText(SCREEN_WIDTH / 2 + (80), 5, font_id, "0");
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

void ModuleUI::Result()
{
	switch (Resultinfo)
	{
	case 1:
		if (SDL_GetTicks() - App->chunli2->lose_timer < 4000)
		{
			calculateBonus(1);
			App->font->BlitText(SCREEN_WIDTH / 2 - 45, 85, font_id, "p1 wins");
		}		
		if (App->chunli->victoryRound1 == true || App->chunli->victoryRound2 == true)
		{
			if (SDL_GetTicks() - App->chunli2->lose_timer > 4000)
			{
				App->font->BlitText(SCREEN_WIDTH / 2 - 75, 65, font_id, "time");
				showScreen(SCREEN_WIDTH / 2 + 75, 65, p1time);
			}
			if (SDL_GetTicks() - App->chunli2->lose_timer > 5000)
			{
				App->font->BlitText(SCREEN_WIDTH / 2 - 75, 85, font_id, "life");
				showScreen(SCREEN_WIDTH / 2 + 75, 85, p1life);
			}
			if (SDL_GetTicks() - App->chunli2->lose_timer > 6000)
			{
				App->font->BlitText(SCREEN_WIDTH / 2 - 75, 115, font_id, "bonus");
				//if (App->chunli2->lose_timer > 7000)
				//{
					showScreen(SCREEN_WIDTH / 2 + 75, 115, p1time + p1life);
				/*}
				else
				{
					aux += (p1time + p1life) / 1000;
					showScreen(SCREEN_WIDTH / 2 + 75, 115, aux);
				}*/
				
			}
		}
		break;
	case 2:
		if (SDL_GetTicks() - App->chunli->lose_timer < 4000)
		{
			calculateBonus(2);
			App->font->BlitText(SCREEN_WIDTH / 2 - 45, 85, font_id, "p2 wins");
		}
		if (App->chunli2->victoryRound1 == true || App->chunli2->victoryRound2 == true)
		{
			if (SDL_GetTicks() - App->chunli->lose_timer > 4000)
			{
				App->font->BlitText(SCREEN_WIDTH / 2 - 75, 65, font_id, "time");
				showScreen(SCREEN_WIDTH / 2 + 75, 65, p2time);
			}
			if (SDL_GetTicks() - App->chunli->lose_timer > 5000)
			{
				App->font->BlitText(SCREEN_WIDTH / 2 - 75, 85, font_id, "life");
				showScreen(SCREEN_WIDTH / 2 + 75, 85, p2life);
			}
			if (SDL_GetTicks() - App->chunli->lose_timer > 6000)
			{
				App->font->BlitText(SCREEN_WIDTH / 2 - 75, 115, font_id, "bonus");
				//if(App->chunli->lose_timer > 7000)
				//{
					showScreen(SCREEN_WIDTH / 2 + 75, 115, p2time + p2life);
				/*}				
				else
				{
					aux += (p2time + p2life) / 1000;
					showScreen(SCREEN_WIDTH / 2 + 75, 115, aux);
				}*/
			}

		}
		break;
	default:
		App->font->BlitText(SCREEN_WIDTH / 2 - 45, 85, font_id, " ");
		Resultinfo = -1;
		ScoreAdded = false;
		break;
	}

}

void ModuleUI::calculateBonus(int player)
{
	if (player == 1)
	{
		p1life = App->chunli->life*3*10;
		p1time = time * 100;
		if (ScoreAdded == false)
		{
			scoreP1 += p1time + p1life;
			ScoreAdded = true;
		}
	}
	else
	{
		p2life = App->chunli2->life*3*10;
		p2time = time * 100;
		if (ScoreAdded == false)
		{
			scoreP2 += p2time + p2life;
			ScoreAdded = true;
		}
	}
}

void ModuleUI::showScreen(int x, int y,int num)
{
	int fiveScore = num / 10000;
	int fourScore = num / 1000 % 10;
	int threeScore = num / 100 % 10;
	int twoScore = num / 10 % 10;
	int oneScore = num % 10;

	switch (oneScore)
	{
	case 9:
		App->font->BlitText(x, y, font_id, "9");
		break;
	case 8:
		App->font->BlitText(x, y, font_id, "8");
		break;
	case 7:
		App->font->BlitText(x, y, font_id, "7");
		break;
	case 6:
		App->font->BlitText(x, y, font_id, "6");
		break;
	case 5:
		App->font->BlitText(x, y, font_id, "5");
		break;
	case 4:
		App->font->BlitText(x, y, font_id, "4");
		break;
	case 3:
		App->font->BlitText(x, y, font_id, "3");
		break;
	case 2:
		App->font->BlitText(x, y, font_id, "2");
		break;
	case 1:
		App->font->BlitText(x, y, font_id, "1");
		break;
	case 0:
		App->font->BlitText(x, y, font_id, "0");			
		break;
	}
	switch (twoScore)
	{
	case 9:
		App->font->BlitText(x - 14, y, font_id, "9");
		break;
	case 8:
		App->font->BlitText(x - 14, y, font_id, "8");
		break;
	case 7:
		App->font->BlitText(x - 14, y, font_id, "7");
		break;
	case 6:
		App->font->BlitText(x - 14, y, font_id, "6");
		break;
	case 5:
		App->font->BlitText(x - 14, y, font_id, "5");
		break;
	case 4:
		App->font->BlitText(x- 42, y, font_id, "4");
		break;
	case 3:
		App->font->BlitText(x - 14, y, font_id, "3");
		break;
	case 2:
		App->font->BlitText(x - 14, y, font_id, "2");
		break;
	case 1:
		App->font->BlitText(x- 14, y, font_id, "1");
		break;
	case 0:
		App->font->BlitText(x - 14, y, font_id, "0");
		break;
	}
	switch (threeScore)
	{
	case 9:
		App->font->BlitText(x- 28, y, font_id, "9");
		break;
	case 8:
		App->font->BlitText(x- 28, y, font_id, "8");
		break;
	case 7:
		App->font->BlitText(x- 28, y, font_id, "7");
		break;
	case 6:
		App->font->BlitText(x- 28, y, font_id, "6");
		break;
	case 5:
		App->font->BlitText(x- 28, y, font_id, "5");
		break;
	case 4:
		App->font->BlitText(x- 28, y, font_id, "4");
		break;
	case 3:
		App->font->BlitText(x- 28, y, font_id, "3");
		break;
	case 2:
		App->font->BlitText(x- 28, y, font_id, "2");
		break;
	case 1:
		App->font->BlitText(x- 28, y, font_id, "1");
		break;
	case 0:
		App->font->BlitText(x - 28, y, font_id, "0");		
		break;
	}
	switch (fourScore)
	{
	case 9:
		App->font->BlitText(x - 42, y, font_id, "9");
		break;
	case 8:
		App->font->BlitText(x - 42, y, font_id, "8");
		break;
	case 7:
		App->font->BlitText(x - 42, y, font_id, "7");
		break;
	case 6:
		App->font->BlitText(x - 42, y, font_id, "6");
		break;
	case 5:
		App->font->BlitText(x - 42, y, font_id, "5");
		break;
	case 4:
		App->font->BlitText(x - 42, y, font_id, "4");
		break;
	case 3:
		App->font->BlitText(x - 42, y, font_id, "3");
		break;
	case 2:
		App->font->BlitText(x - 42, y, font_id, "2");
		break;
	case 1:
		App->font->BlitText(x - 42, y, font_id, "1");
		break;
	case 0:
		App->font->BlitText(x - 42, y, font_id, "0");
		break;
	}
	switch (fiveScore)
	{
	case 9:
		App->font->BlitText(x - 56, y, font_id, "9");
		break;
	case 8:
		App->font->BlitText(x - 56, y, font_id, "8");
		break;
	case 7:
		App->font->BlitText(x - 56, y, font_id, "7");
		break;
	case 6:
		App->font->BlitText(x - 56, y, font_id, "6");
		break;
	case 5:
		App->font->BlitText(x - 56, y, font_id, "5");
		break;
	case 4:
		App->font->BlitText(x - 56, y, font_id, "4");
		break;
	case 3:
		App->font->BlitText(x-56, y, font_id, "3");
		break;
	case 2:
		App->font->BlitText(x-56, y, font_id, "2");
		break;
	case 1:
		App->font->BlitText(x-56, y, font_id, "1");
		break;
	case 0:		
		//App->font->BlitText(x - 14, y, font_id, "0");				
		break;
	}
	/*switch (sixScore)
	{
	case 9:
		App->font->BlitText(x, y, font_id, "9");
		break;
	case 8:
		App->font->BlitText(x, y, font_id, "8");
		break;
	case 7:
		App->font->BlitText(x, y, font_id, "7");
		break;
	case 6:
		App->font->BlitText(x, y, font_id, "6");
		break;
	case 5:
		App->font->BlitText(x, y, font_id, "5");
		break;
	case 4:
		App->font->BlitText(x, y, font_id, "4");
		break;
	case 3:
		App->font->BlitText(x, y, font_id, "3");
		break;
	case 2:
		App->font->BlitText(x, y, font_id, "2");
		break;
	case 1:
		App->font->BlitText(x, y, font_id, "1");
		break;
	case 0:
		App->font->BlitText(x, y, font_id, "0");
		break;
	}*/
}