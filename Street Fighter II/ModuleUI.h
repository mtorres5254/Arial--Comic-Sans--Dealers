#ifndef _MODULEUI_H
#define _MODULEUI_H

#include "Module.h"
#include "Animation.h"
#include "ModuleFont.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL_mixer/include/SDL_mixer.h"

#define SECOND 1000

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

	void Counter();
	void Round(int);
	void GamepadDebug();

public:

	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;

	SDL_Rect HealthBar1;
	SDL_Rect RedBar1;
	SDL_Rect HealthBar2;
	SDL_Rect RedBar2;
	SDL_Rect KObar;
	SDL_Rect RoundBar1;
	SDL_Rect RoundBar2;

	Animation KOanim;

	int victorycount=0;
	int victorycount1 = 0;
	int font_id;
	int font_Rounds;
	int time;
	int Counter1;
	int Counter2;
	int timenow;

	bool GamepadInfo = false;

	Mix_Chunk* VoiceRound;
	Mix_Chunk* Voice1;
	Mix_Chunk* Voice2;
	Mix_Chunk* Voice3;
	Mix_Chunk* VoiceFight;

	
};

#endif // !_MODULEUI_H

