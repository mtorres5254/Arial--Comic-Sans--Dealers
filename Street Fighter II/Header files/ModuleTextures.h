#ifndef __ModuleTextures_H__
#define __ModuleTextures_H__

#include "Header files/Module.h"
#include "Globals.h"

#define MAX_TEXTURES 50

struct SDL_Texture;
struct SDL_Surface;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	bool Init() override;
	bool CleanUp() override;

	SDL_Texture* const Load(const char* path);

public:
	SDL_Texture * textures[MAX_TEXTURES];
	SDL_Texture * textureAux;
	SDL_Surface * surfaces;
};

#endif