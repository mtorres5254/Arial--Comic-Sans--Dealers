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



#define JUMP_TIME 850

#define PUNCH_TIME 150
#define PUNCH_MEDIUM_TIME 200
#define PUNCH_HARD_TIME 500

#define KICK_TIME 200
#define KICK_MEDIUM_TIME 400
#define KICK_HARD_TIME 500


#define PUNCH_NEUTRAL_JUMP_TIME 850
#define HADOUKEN_TIME 1200
#define DMG_TIME 200

#define MAX_FRAME_COLLIDERS 6
#define idleForce 5

#define WHIRLWINDKICK_TIME 1500

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
	ST_PUNCH_MEDIUM_CROUCH,
	ST_PUNCH_HARD_CROUCH,
	ST_KICK_CROUCH,
	ST_KICK_MEDIUM_CROUCH,
	ST_KICK_HARD_CROUCH,
	ST_KICK_STANDING,
	ST_KICK_MEDIUM_STANDING,
	ST_KICK_HARD_STANDING,
	ST_LIGHTNINGKICK,
	ST_RECEIVED_PUNCH,
	ST_PUNCH_MEDIUM,
	ST_PUNCH_HARD,

	ST_PUNCH_MEDIUM_NEUTRAL_JUMP,
	ST_PUNCH_HARD_NEUTRAL_JUMP,

	ST_KICK_NEUTRAL_JUMP,
	ST_KICK_MEDIUM_NEUTRAL_JUMP,
	ST_KICK_HARD_NEUTRAL_JUMP,

	ST_PUNCH_MEDIUM_FORWARD_JUMP,
	ST_PUNCH_HARD_FORWARD_JUMP,

	ST_PUNCH_MEDIUM_BACKWARD_JUMP,
	ST_PUNCH_HARD_BACKWARD_JUMP,

	ST_KICK_FORWARD_JUMP,
	ST_KICK_MEDIUM_FORWARD_JUMP,
	ST_KICK_HARD_FORWARD_JUMP,

	ST_KICK_BACKWARD_JUMP,
	ST_KICK_MEDIUM_BACKWARD_JUMP,
	ST_KICK_HARD_BACKWARD_JUMP,

	ST_DAMAGE,
	ST_DAMAGE_HARD,
	ST_DAMAGE_FALL,
	ST_DAMAGE_AIR,
	ST_DAMAGE_CROUCH,

	ST_BLOCK,
	ST_BLOCK_CROUCH,

	ST_WHIRLWIND,
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
	IN_DAMAGE,
	IN_DAMAGE_HARD,
	IN_DAMAGE_FALL,
	IN_DAMAGE_AIR,
	IN_DAMAGE_CROUCH,

	IN_X,
	IN_C,
	IN_1,
	IN_2,
	IN_3,
	IN_4,

	IN_LIGHTINGKICK,
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH,
	IN_PUNCH_MEDIUM_FINISH,
	IN_PUNCH_HARD_FINISH,
	IN_KICK_FINISH,
	IN_KICK_MEDIUM_FINISH,
	IN_KICK_HARD_FINISH,
	IN_LIGHTNINGKICK_FINISH,
	IN_RECEIVED_PUNCH,
	IN_DAMAGE_FINISH,

	IN_BLOCK,
	IN_BLOCK_CROUCH,

	IN_BLOCK_FINISH,

	IN_WHIRLWINDKICK,
	IN_WHIRLWINDKICK_FINISH,
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
	void resetanimations();
	void debugcommands();
	void jump_neutral_logic();
	void jump_forward_logic();
	void jump_backward_logic();

public:

	SDL_Texture * graphics = nullptr;
	SDL_Texture* shadow = nullptr;

	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation punch_medium;
	Animation punch_hard;

	Animation kick;
	Animation kick_medium;
	Animation kick_hard;

	Animation crouch;
	Animation jump_neutral;

	Animation jump_backwards;
	Animation jump_forward;

	Animation Crouch_punch;
	Animation Crouch_medium_punch;
	Animation Crouch_hard_punch;

	Animation Crouch_kick;
	Animation Crouch_medium_kick;
	Animation Crouch_hard_kick;

	Animation jump_neutral_punch;
	Animation jump_neutral_punch_medium;
	Animation jump_neutral_punch_hard;

	Animation jump_neutral_kick;
	Animation jump_neutral_kick_medium;
	Animation jump_neutral_kick_hard;


	Animation jump_forward_punch;
	Animation jump_forward_punch_medium;
	Animation jump_forward_punch_hard;

	Animation jump_forward_kick;
	Animation jump_forward_kick_medium;
	Animation jump_forward_kick_hard;

	Animation jump_backward_punch;
	Animation jump_backward_punch_medium;
	Animation jump_backward_punch_hard;

	Animation jump_backward_kick;
	Animation jump_backward_kick_medium;
	Animation jump_backward_kick_hard;

	Animation block_standing;
	Animation block_crouch;

	Animation LightningKick_startup;
	Animation LightningKick;
	Animation WhirlwindKick;
	Animation Death;
	Animation damage;
	Animation damage2;
	Animation damage3;
	Animation damage4;
	Animation damage5;
	Animation victory;
	Animation victory1;
	iPoint position;
	Collider* colliders[MAX_COLLIDERS];

	Mix_Chunk* LightningKick_effect;
	Mix_Chunk* WhirlwindKick_effect;
	Mix_Chunk* light_damage;
	Mix_Chunk* medium_damage;
	Mix_Chunk* high_damage;

	int acumvictory = 0;
	bool GodMode = false;

	bool death = false;
	bool leftLimit = false;
	bool RightLimit = false;

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
	int damage_received = 0;
	int hit_conected = 0;
	int block_damage = 0;
	bool jumpactive = 0;
	bool prueba = false;
	int life = 1000;
	int healthbar;
	int wkcounter = 0;

	bool move = true;
	bool whirlwindMove = false;

	chunli_states state;

	Uint32 punch_hard_timer = 0;
	Uint32 punch_medium_timer = 0;
	Uint32 kick_medium_timer = 0;
	Uint32 kick_hard_timer = 0;
	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 hadouken_timer = 0;
	Uint32 punch_neutral_jump_timer = 0;
	Uint32 dmg_timer = 0;
	Uint32 dmg_hard_timer = 0;
	Uint32 dmg_fall_timer = 0;
	Uint32 block_timer = 0;
	Uint32 whirlwind_timer = 0;

	private:
		bool left = false;
		bool right = false;
		bool down = false;
		bool up = false;
		int force = 0;

};

#endif
