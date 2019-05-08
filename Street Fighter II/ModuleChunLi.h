#ifndef _MODULECHUNLI_H
#define _MODULECHUNLI_H

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include <string.h>
#include "p2Qeue.h"
#include "SDL\include\SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"



#define JUMP_TIME2 850
#define PUNCH_TIME2 150
#define PUNCH_NEUTRAL_JUMP_TIME2 850
#define KICK_TIME2 400
#define HADOUKEN_TIME2 1000
struct SDL_Texture;



enum ryu_states2
{
	ST_UNKNOWN2,

	ST_IDLE2,
	ST_WALK_FORWARD2,
	ST_WALK_BACKWARD2,
	ST_JUMP_NEUTRAL2,
	ST_JUMP_FORWARD2,
	ST_JUMP_BACKWARD2,
	ST_CROUCH2,
	ST_PUNCH_STANDING2,
	ST_PUNCH_NEUTRAL_JUMP2,
	ST_PUNCH_FORWARD_JUMP2,
	ST_PUNCH_BACKWARD_JUMP2,
	ST_PUNCH_CROUCH2,
	ST_KICK_STANDING2,
	ST_HADOUKEN2,
	ST_RECEIVED_PUNCH2,
};

enum ryu_inputs2
{
	IN_LEFT_DOWN2,
	IN_LEFT_UP2,
	IN_RIGHT_DOWN2,
	IN_RIGHT_UP2,
	IN_LEFT_AND_RIGHT2,
	IN_JUMP2,
	IN_CROUCH_UP2,
	IN_CROUCH_DOWN2,
	IN_JUMP_AND_CROUCH2,
	IN_X2,
	IN_C2,
	IN_V2,
	IN_JUMP_FINISH2,
	IN_PUNCH_FINISH2,
	IN_KICK_FINISH2,
	IN_HADOUKEN_FINISH2,
	IN_RECEIVED_PUNCH2,
};
class ModuleChunLi : public Module
{
public:
	ModuleChunLi();
	~ModuleChunLi();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void internal_input(p2Qeue<ryu_inputs2>&);
	bool external_input(p2Qeue<ryu_inputs2>&);
	ryu_states2 process_fsm(p2Qeue<ryu_inputs2>& inputs);
	void ResetPlayer();
	void lifecondition(Animation*);

public:

	SDL_Texture* graphics = nullptr;
	
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;

	Animation crouch;
	Animation jump_neutral;
	Animation jump_backwards;
	Animation jump_forward;

	Animation Crouch_punch;
	Animation jump_neutral_punch;
	Animation jump_forward_punch;
	Animation jump_backward_punch;
	
	Animation Death;
	Animation damage;
	Animation victory;
	Animation victory1;
	iPoint position;

	Collider* colliderchunli;
	int acumvictory = 0;
		
	bool death = false;

	int DeathCount = 0;
	int ActiveDeath = 0;
	int victorycount = 0;
	int speedX = 1;
	int speedY = 1;
	int acumdamage = 0;
	int jumpHeight = 0;
	int speed = 1;
	bool damage_received = false;
	bool jumpactive = 0;
	bool prueba = false;
	int life = 1000;
	int healthbar;

	ryu_states2 state;

	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 hadouken_timer = 0;
	Uint32 punch_neutral_jump_timer = 0;

	
};

#endif