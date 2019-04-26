/*#ifndef __MODULEWINSCENE_H__
#define __MODULEWINSCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleWinScene : public Module
{
public:
	ModuleWinScene();
	~ModuleWinScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Mix_Music* music;

	SDL_Rect Y,O,U,W,I,N;
};

#endif // __MODULEWINSCENE_H__*/