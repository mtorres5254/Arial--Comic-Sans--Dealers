#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleUI.h"
#include "ModuleSceneKen.h"


ModuleUI::ModuleUI() {

	//HealthBar1
	HealthBar1.x = 43;
	HealthBar1.y=	24;
	HealthBar1.w = 153;
	HealthBar1.h = 19;

	RedBar1.x = 43;
	RedBar1.y = 54;
	RedBar1.w = 153;
	RedBar1.h = 19;

	//HealthBar2
	HealthBar2.x = 284;
	HealthBar2.y = 24;
	HealthBar2.w = 153;
	HealthBar2.h = 19;

	RedBar2.x = 284;
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
	RoundBar2.x = 216 ;
	RoundBar2.y = 39;
	RoundBar2.w = 17;
	RoundBar2.h = 20;
	
	KOanim.PushBack({205,18,27,24});
	KOanim.PushBack({205,56,27,24});
	KOanim.speed = 0.1f;

	//Num 0
	num0.x = 306;
	num0.y = 276;
	num0.w = 12;
	num0.h = 19;
	//Num 1
	num1.x = 306;
	num1.y = 247;
	num1.w = 12;
	num1.h = 19;
	//Num 2
	num2.x = 306;
	num2.y = 217;
	num2.w = 12;
	num2.h = 19;
	//Num 3
	num3.x = 306;
	num3.y = 188;
	num3.w = 12;
	num3.h = 19;
	//Num 4
	num4.x = 306;
	num4.y = 159;
	num4.w = 12;
	num4.h = 19;
	//Num 5
	num5.x = 306;
	num5.y = 129;
	num5.w = 12;
	num5.h = 19;
	//Num 6
	num6.x = 306;
	num6.y = 100;
	num6.w = 12;
	num6.h = 19;
	//Num 7
	num7.x = 306;
	num7.y = 72;
	num7.w = 12;
	num7.h = 19;
	//Num 8
	num8.x = 306;
	num8.y = 47;
	num8.w = 12;
	num8.h = 19;
	//Num 9
	num9.x = 306;
	num9.y = 13;
	num9.w = 12;
	num9.h = 19;
}

ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
	LOG("Loading UI textures");
	App->font->Enable();
	bool ret = true;

	graphics1 = App->textures->Load("Assets/Images/Battle_HUD.png"); 
	graphics2 = App->textures->Load("Assets/Images/Battle_HUD2.png");
	
	return ret;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading UI graphics");

	App->textures->Unload(graphics1);
	App->textures->Unload(graphics2);

	return true;
}

update_status ModuleUI:: Update()
{
	//Logic
	switch (App->scene_ken->countbig)
	{
	case 0: break;
	case 1: break;
	case 2: break;
	case 3: break;
	case 4: break;
	case 5: break;
	case 6: break;
	case 7: break;
	case 8: break;
	case 9: break;
	}
	HealthBar1.w = App->player->healthbar;
	HealthBar2.w = App->player2->healthbar;

	//Render
	App->font->BlitText(SCREEN_WIDTH / 2, 100, 1, "hola");

	App->render->Blit(graphics1, SCREEN_WIDTH / 2 - RedBar1.w - KObar.w / 2, 20, &RedBar1, false);
	App->render->Blit(graphics1, SCREEN_WIDTH / 2 - HealthBar1.w - KObar.w / 2, 20, &HealthBar1, false);
	App->render->Blit(graphics2, SCREEN_WIDTH / 2 + KObar.w / 2, 20, &RedBar2, false);
	App->render->Blit(graphics2, SCREEN_WIDTH / 2 + KObar.w / 2, 20, &HealthBar2, false);

	if (App->player->life > 250 && App->player2->life > 250) {
		App->render->Blit(graphics1, SCREEN_WIDTH / 2 - (KObar.w / 2), 15, &KObar, false);
	}
	else {
		App->render->Blit(graphics1, SCREEN_WIDTH / 2 - (KObar.w / 2), 15, &KOanim.GetCurrentFrame(), false);
	}

	if (App->player2->victorycount == 1 || App->player2->victorycount == 2) {
		App->render->Blit(graphics1, (SCREEN_WIDTH / 2)-153-(KObar.w/2)-20, 20, &RoundBar1, false);
	}

	if (App->player->victorycount == 1 || App->player->victorycount == 2) {
		App->render->Blit(graphics2, (SCREEN_WIDTH / 2) + 153 + (KObar.w / 2) , 20, &RoundBar2, false);
	}
	
	
	return UPDATE_CONTINUE;
}

