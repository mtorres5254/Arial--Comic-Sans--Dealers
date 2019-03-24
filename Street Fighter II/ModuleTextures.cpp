#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{

	for (int i = 0; i < MAX_TEXTURES; i++) {
		textures[i] == nullptr;
	}
}

// Destructor
ModuleTextures::~ModuleTextures()
{}

// Called before render is available
bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	//Load("test.png");
	return ret;
}

// Called before q	uitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	// TODO 6: Free all textures
	for (int i = 0; i < MAX_TEXTURES; i++) {

		if (textures[i] != nullptr) {
			SDL_DestroyTexture(textures[i]);
		}
	}

	IMG_Quit();
	return true;
}


SDL_Texture* const ModuleTextures::Load(const char* path)
{

	LOG("Loading textures");
	SDL_Surface *surfimage =IMG_Load(path);	

	SDL_Texture *texture = SDL_CreateTextureFromSurface(App->render->renderer, surfimage);

	SDL_FreeSurface(surfimage);

	for (int i = 0; i < MAX_TEXTURES; i++) {

		if (textures[i] == nullptr) {			
			textures[i] = texture;
			i = MAX_TEXTURES;
		}		
		
	}
	
	return texture;
	
}
