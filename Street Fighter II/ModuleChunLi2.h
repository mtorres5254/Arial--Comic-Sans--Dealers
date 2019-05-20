#ifndef _MODULECHUNLI2_H
#define _MODULECHUNLI2_H

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
#define HADOUKEN_TIME2 1200

#define MAX_FRAME_COLLIDERS 6

struct SDL_Texture;



enum chunli_states
{
	ST_UNKNOWN,

	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,
	ST_JUMP_NEUTRAL,
	ST_JUMP_FORWARD,
	ST_JUMP_BACKWARD,
	ST_CROUCH,
	ST_PUNCH_STANDING,
	ST_PUNCH_NEUTRAL_JUMP,
	ST_PUNCH_FORWARD_JUMP,
	ST_PUNCH_BACKWARD_JUMP,
	ST_PUNCH_CROUCH,
	ST_KICK_STANDING,
	ST_LIGHTNINGKICK,
	ST_RECEIVED_PUNCH,
};

enum chunli_inputs
{
	IN_LEFT_DOWN,
	IN_LEFT_UP,
	IN_RIGHT_DOWN,
	IN_RIGHT_UP,
	IN_LEFT_AND_RIGHT,
	IN_JUMP,
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	IN_JUMP_AND_CROUCH,
	IN_X,
	IN_C,
	IN_LIGHTINGKICK,
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH,
	IN_KICK_FINISH,
	IN_LIGHTNINGKICK_FINISH,
	IN_RECEIVED_PUNCH,
};
class ModuleChunLi2 : public Module
{
public:
	ModuleChunLi2();
	~ModuleChunLi2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void internal_input(p2Qeue<chunli_inputs>&);
	bool external_input(p2Qeue<chunli_inputs>&);
	chunli_states process_fsm(p2Qeue<chunli_inputs>& inputs);
	void ResetPlayer();
	void lifecondition(Animation*);
	void colliders_and_blit(Animation*);
	void positionlimits();

public:

	SDL_Texture * graphics = nullptr;
	SDL_Texture* shadow = nullptr;

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

	Animation LightningKick;
	Collider* colliders[MAX_COLLIDERS];

	int acumvictory = 0;

	bool death = false;

	int PivotX = 0; 
	int PivotY = 0;
	int dmg = 0;

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

	bool move = true;

	chunli_states state;

	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 hadouken_timer = 0;
	Uint32 punch_neutral_jump_timer = 0;


};

#endif
