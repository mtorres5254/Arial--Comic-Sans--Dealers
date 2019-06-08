#ifndef _MODULECONTINUE_H_
#define _MODULECONTINUE_H_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"

class ModuleContinue : public Module
{
public:
	ModuleContinue();
	~ModuleContinue();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	
	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Mix_Music* music;

	Animation numbers;
	Animation ChunLi;

private:
	
};

#endif // _MODULECONTINUE_H_