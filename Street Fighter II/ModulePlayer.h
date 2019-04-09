#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;
	Animation hadouken;
	iPoint position;
	int PunchCount = 0;
	int KickCount = 0;
	int HadoukenCount = 0;
	bool moving = false;
	bool movef = false;
	bool moveb = false;
	
	Collider* colliderplayer;	
};

#endif