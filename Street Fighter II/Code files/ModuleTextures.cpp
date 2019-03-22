#include "Header files/Globals.h"
#include "Header files/Application.h"
#include "Header files/ModuleRenderer.h"
#include "Header files/ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() {
	for (int i = 0; i < MAX_TEXTURES; i++) {
		textures[i] = nullptr;
	}
}

bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;
	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (int i = MAX_TEXTURES; i > 0; i--) {
		SDL_DestroyTexture(textures[i]);
	}

	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	surfaces = IMG_Load(path);
	textureAux = SDL_CreateTextureFromSurface(App->rend->render, surfaces);
	SDL_FreeSurface(surfaces);

	return textureAux;
}

