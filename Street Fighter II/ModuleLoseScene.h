#ifndef __MODULELOSESCENE_H__
#define __MODULELOSESCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

class ModuleLoseScene : public Module {
public:

	ModuleLoseScene();
	~ModuleLoseScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Mix_Chunk* music;

private:
	int timer;
};

#endif