#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleUI.h"

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

update_status ModuleUI:: Update(){
	
	//Logic

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
	
	return UPDATE_CONTINUE;
}

