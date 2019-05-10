#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomePage.h"
#include "ModuleCongratsScreen.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleLoseScene.h"
#include "ModuleWinScene.h"
#include "ModuleChunLi.h"
#include "ModuleChunLi2.h"
#include "ModuleFont.h"
#include "ModuleSceneDhalsim.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	modules[5] = congrats_screen = new ModuleCongratsScreen();
	modules[6] = scene_dhalsim = new ModuleSceneDhalsim();
	modules[7] = chunli = new ModuleChunLi();
	modules[8] = chunli2 = new ModuleChunLi2();
	modules[9] = fade = new ModuleFadeToBlack();
	modules[10] = welcome_page = new ModuleWelcomePage();
	modules[11] = particle = new ModuleParticles();
	modules[12] = collision = new ModuleCollision();
	modules[13] = UI = new ModuleUI();
	modules[14] = lose_scene = new ModuleLoseScene();
	modules[15] = font = new ModuleFont();
	
	
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
	chunli->Disable();
	chunli2->Disable();
	// Disable the map that you do not start with
	scene_dhalsim->Disable();
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
	plyDistance = (chunli2->position.x + 60) - chunli->position.x;
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