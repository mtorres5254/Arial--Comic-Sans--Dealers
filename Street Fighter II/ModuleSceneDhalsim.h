#ifndef __MODULESCENEDHALSIM_H__
#define __MODULESCENEDHALSIM_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"


struct SDL_Texture;

class ModuleSceneDhalsim: public Module
{
public:
	ModuleSceneDhalsim();
	~ModuleSceneDhalsim();

	bool Start();
	update_status Update();
	bool CleanUp();
	void roundpoints();
	void fadeto();

public:

	SDL_Texture* graphics = nullptr;

	SDL_Rect ground;
	SDL_Rect background;

	int PivotX = 0;
	int PivotY = 0;
	
	
	Animation rightelephant1;
	Animation rightelephant2;
	Animation rightelephant3;
	Animation leftelephant1;
	Animation leftelephant2;
	Animation leftelephant3;
	
	Mix_Music* music;

	float foreground_pos;
	bool forward;
	int Round;

	bool fight = false;
	bool newRound = true;

	bool Round1 = true;
	bool Round2 = false;
	bool Round3 = false;

};

#endif // __MODULESCENEDHALSIM_H__