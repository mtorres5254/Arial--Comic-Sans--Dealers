#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"
#include "ModuleChunLi.h"
#include "ModuleChunLi2.h"
#include "ModuleScore.h"
#include "ModuleInput.h"
#include "ModuleSceneDhalsim.h"
#include <string.h>


ModuleScore::ModuleScore()
{
}

bool ModuleScore::Start()
{
}

ModuleScore::~ModuleScore()
{}

bool ModuleScore::CleanUp()
{
	LOG("Unloading UI graphics");

	//App->textures->Unload(graphics1);

	return true;
}

update_status ModuleScore::Update()
{
}