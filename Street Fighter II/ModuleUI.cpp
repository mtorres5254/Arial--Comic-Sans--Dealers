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
	font_Rounds = App->font->Load("Assets/Images/font_round.png", "r123", 2);

	timenow = SDL_GetTicks();
	time = 99;
	Counter1 = 9; //unit
	Counter2 = 9; //tens
	
	scoreP1 = 000000;
	scoreP2 = 000000;

	return ret;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading UI graphics");

	App->textures->Unload(graphics1);

	App->font->UnLoad(font_id);
	App->font->UnLoad(font_Rounds);

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

void ModuleUI::Result() {
	switch (Resultinfo)
	{
	case 1:
		App->font->BlitText(SCREEN_WIDTH / 2 - 45, 85, font_id, "p1 wins");
		break;
	case 2:
		App->font->BlitText(SCREEN_WIDTH / 2 - 45, 85, font_id, "p2 wins");
		break;
	default:
		App->font->BlitText(SCREEN_WIDTH / 2 - 45, 85, font_id, " ");
		Resultinfo = -1;
		break;
	}

}

