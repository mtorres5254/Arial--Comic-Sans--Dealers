#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneKen.h"
#include "ModuleSceneHonda.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomePage.h"
#include "ModuleCongratsScreen.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleLoseScene.h"
#include "ModuleSceneRyu.h"
<<<<<<< HEAD
#include "ModuleWinScene.h"
#include "ModuleFont.h"
=======
>>>>>>> parent of 9429e03... Working on win scene

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	modules[5] = congrats_screen = new ModuleCongratsScreen();
	modules[6] = scene_honda = new ModuleSceneHonda();
	modules[7] = scene_ken = new ModuleSceneKen();
	modules[8] = scene_ryu = new ModuleSceneRyu();
	modules[9] = player = new ModulePlayer();	
	modules[10] = player2 = new ModulePlayer2();
	modules[11] = fade = new ModuleFadeToBlack();
	modules[12] = welcome_page = new ModuleWelcomePage();
	modules[13] = particle = new ModuleParticles();
	modules[14] = collision = new ModuleCollision();
	modules[15] = UI = new ModuleUI();
	modules[16] = lose_scene = new ModuleLoseScene();
<<<<<<< HEAD
	modules[17] = win_scene = new ModuleWinScene();
	modules[18] = font = new ModuleFont();
=======
>>>>>>> parent of 9429e03... Working on win scene
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	player2->Disable();
	// Disable the map that you do not start with
	scene_honda->Disable();
	scene_ken->Disable();
	scene_ryu->Disable();
	lose_scene->Disable();
	congrats_screen->Disable();
	collision->Disable();
	UI->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}