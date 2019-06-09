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

	SDL_Rect background;


	bool done1 = false;
	bool done2 = false;
	bool done3 = false;
	bool done4 = false;
	bool done5 = false;
	bool done6 = false;
	bool done7 = false;
	bool done8 = false;
	bool done9 = false;
	bool done10 = false;
	bool done11 = false;
	int font_id;
	int timer = 0;
	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Mix_Music* music;
	Mix_Chunk* number1;
	Mix_Chunk* number2;
	Mix_Chunk* number3;
	Mix_Chunk* number4;
	Mix_Chunk* number5;
	Mix_Chunk* number6;
	Mix_Chunk* number7;
	Mix_Chunk* number8;
	Mix_Chunk* number9;
	Mix_Chunk* continuechange;
	Mix_Chunk* scream;
	Mix_Chunk* gameover;
	int redscreen = 0;
    int stop = false;
	Animation numbers;
	Animation ChunLi;

private:
	
};

#endif // _MODULECONTINUE_H_