#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

#define roundTime 99
#define smallSecs 9
#define bigSecs 9


struct SDL_Texture;

class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen();
	~ModuleSceneKen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;	
	
	SDL_Rect ground;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation flag;
	Animation girl;
	Mix_Music* music;

	float foreground_pos;
	bool forward;
	
	int countbig,countsmall,countdown;

private:
	float  time, timenow;
};

#endif // __MODULESCENEKEN_H__