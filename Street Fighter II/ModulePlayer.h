#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include <string.h>
#include "p2Qeue.h"
#include "SDL\include\SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define JUMP_TIME 850
#define PUNCH_TIME 150
#define KICK_TIME 400
#define HADOUKEN_TIME 1000

struct SDL_Texture;

enum ryu_states
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
	ST_HADOUKEN,
	ST_RECEIVED_PUNCH,
};

enum ryu_inputs
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
	IN_V,
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH,
	IN_KICK_FINISH,
	IN_HADOUKEN_FINISH,
	IN_RECEIVED_PUNCH,
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	bool external_input(p2Qeue<ryu_inputs>&);
	void internal_input(p2Qeue<ryu_inputs>&);
	ryu_states process_fsm(p2Qeue<ryu_inputs>& inputs);
	void ResetPlayer();

public:

	SDL_Texture* graphics = nullptr;
	Mix_Chunk* deathSound;
	Mix_Chunk* ugh;
	Mix_Chunk* hit;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;
	Animation hadouken_pose;
	Animation crouch;
	Animation jump_neutral;
	Animation jump_backwards;
	Animation jump_forward;
	Animation falling;
	Animation Crouch_punch;
	Animation jump_neutral_punch;
	Animation jump_forward_punch;
	Animation jump_backward_punch;
	Animation ReceivedPunch;
	Animation Death;
	Animation damage;
	Animation victory;
	Animation victory1;
	iPoint position;

	int acumvictory = 0;
	int HadoukenCount = 0;
	int ActiveHadouken = 0;
	int JumpCount = 0;
	bool JumpMin = false;
	bool JumpMax = false;
	bool movef = true;
	bool moveb = true;
	bool GodMode = false;
	bool punchCol = false;
	bool CrPunchCol = false;
	bool kickCol = false;
	bool colliderErese = false;
	bool colliderErese2 = false;
	bool colliderErese3 = false;
	bool HaveCollider = true;
	bool death = false;

	int DeathCount = 0;
	int ActiveDeath = 0;
	int victorycount =0;
	int speedX = 1;
	int speedY = 1;
	int acumdamage = 0;

	bool damage_received = false;

	int life = 1000;
	int healthbar;

private:

	

	Collider* colliderplayer;
	Collider* punchcollider;
	Collider* crouchpunchcollider;
	Collider* kickcollider;
	
	ryu_states state;

	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 hadouken_timer = 0;



	

	
};

#endif