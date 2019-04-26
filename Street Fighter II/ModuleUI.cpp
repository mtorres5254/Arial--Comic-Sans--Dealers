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

	//HealthBar2
	HealthBar2.x = 284;
	HealthBar2.y = 24;
	HealthBar2.w = 153;
	HealthBar2.h = 19;

	//KOBar

	KObar.x = 205;
	KObar.y = 18;
	KObar.w = 27;
	KObar.h = 24;

}

ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
	LOG("Loading UI textures");
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
	App->UI->Disable();

	return true;
}

update_status ModuleUI:: Update(){
	
	//Logic

	HealthBar1.w = App->player->healthbar;
	HealthBar2.w = App->player2->healthbar;

	//Render
	App->render->Blit(graphics1, SCREEN_WIDTH/2-HealthBar1.w -KObar.w/2, 20, &HealthBar1, false);
	App->render->Blit(graphics2, SCREEN_WIDTH/2 + KObar.w/2, 20, &HealthBar2, false);
	App->render->Blit(graphics1, SCREEN_WIDTH/2 - (KObar.w / 2), 15, &KObar, false);

	
	return UPDATE_CONTINUE;
}

