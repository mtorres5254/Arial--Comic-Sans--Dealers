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
#define PUNCH_MEDIUM_TIME2 200
#define PUNCH_HARD_TIME2 500

#define KICK_TIME2 200
#define KICK_MEDIUM_TIME2 400
#define KICK_HARD_TIME2 500


#define PUNCH_NEUTRAL_JUMP_TIME2 850
#define HADOUKEN_TIME2 1200
#define DMG_TIME2 200
#define idleForce 5

#define WHIRLWINDKICK_TIME2 1500



#define MAX_FRAME_COLLIDERS 6

struct SDL_Texture;



enum chunli_states2
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
	ST_PUNCH_MEDIUM_CROUCH2,
	ST_PUNCH_HARD_CROUCH2,
	ST_KICK_CROUCH2,
	ST_KICK_MEDIUM_CROUCH2,
	ST_KICK_HARD_CROUCH2,
	ST_KICK_STANDING2,
	ST_KICK_MEDIUM_STANDING2,
	ST_KICK_HARD_STANDING2,
	ST_LIGHTNINGKICK2,
	ST_RECEIVED_PUNCH2,
	ST_PUNCH_MEDIUM2,
	ST_PUNCH_HARD2,

	ST_PUNCH_MEDIUM_NEUTRAL_JUMP2,
	ST_PUNCH_HARD_NEUTRAL_JUMP2,

	ST_KICK_NEUTRAL_JUMP2,
	ST_KICK_MEDIUM_NEUTRAL_JUMP2,
	ST_KICK_HARD_NEUTRAL_JUMP2,

	ST_PUNCH_MEDIUM_FORWARD_JUMP2,
	ST_PUNCH_HARD_FORWARD_JUMP2,

	ST_PUNCH_MEDIUM_BACKWARD_JUMP2,
	ST_PUNCH_HARD_BACKWARD_JUMP2,

	ST_KICK_FORWARD_JUMP2,
	ST_KICK_MEDIUM_FORWARD_JUMP2,
	ST_KICK_HARD_FORWARD_JUMP2,

	ST_KICK_BACKWARD_JUMP2,
	ST_KICK_MEDIUM_BACKWARD_JUMP2,
	ST_KICK_HARD_BACKWARD_JUMP2,

	ST_DAMAGE2,
	ST_DAMAGE_HARD2,
	ST_DAMAGE_FALL2,
	ST_DAMAGE_AIR2,
	ST_DAMAGE_CROUCH2,

	ST_BLOCK2,
	ST_BLOCK_CROUCH2,

	ST_WHIRLWIND2,
	ST_VICTORY2,
	ST_VICTORY2_2,

	ST_LOSE2,

};

enum chunli_inputs2
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
	IN_DAMAGE2,
	IN_DAMAGE_HARD2,
	IN_DAMAGE_FALL2,
	IN_DAMAGE_AIR2,
	IN_DAMAGE_CROUCH2,

	IN_X2,
	IN_C2,
	IN_1_2,
	IN_2_2,
	IN_3_2,
	IN_4_2,
	
	IN_LIGHTINGKICK2,

	IN_JUMP_FINISH2,
	IN_PUNCH_FINISH2,
	IN_PUNCH_MEDIUM_FINISH2,
	IN_PUNCH_HARD_FINISH2,
	IN_KICK_FINISH2,
	IN_KICK_MEDIUM_FINISH2,
	IN_KICK_HARD_FINISH2,
	IN_LIGHTNINGKICK_FINISH2,
	IN_RECEIVED_PUNCH2,

	IN_DAMAGE_FINISH2,

	IN_WHIRLWINDKICK2,
	IN_WHIRLWINDKICK2_FINISH2,

	IN_BLOCK2,
	IN_BLOCK_CROUCH2,

	IN_BLOCK_FINISH2,

	IN_VICTORY2,
	IN_VICTORY_FINISH2,
	IN_VICTORY2_2,
	IN_VICTORY2_FINISH_2,

	IN_LOSE2,
	IN_LOSE_FINISH2,
};

struct MoveBooleans {
	bool left = false;
	bool right = false;
	bool down = false;
	bool up = false;
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
	void internal_input(p2Qeue<chunli_inputs2>&);
	bool external_input(p2Qeue<chunli_inputs2>&);
	chunli_states2 process_fsm(p2Qeue<chunli_inputs2>& inputs);
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

	SDL_Texture* graphics = nullptr;
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

	Animation win1;
	Animation win2;

	Animation Death;
	Animation damage;
	Animation damage2;
	Animation damage3;
	Animation damage4;
	Animation damage5;
	Animation victory;
	Animation victory1;
	iPoint position;

	Mix_Chunk* LightningKick_effect;
	Mix_Chunk* WhirlwindKick_effect;

	Mix_Chunk* light_damage;
	Mix_Chunk* medium_damage;
	Mix_Chunk* high_damage;
	Mix_Chunk* wind;

	Mix_Chunk* win_sound;
	Mix_Chunk* death_sound;

	bool DeathSoundPlayed = false;
	bool WinSoundPlayed = false;

	Collider* colliders[MAX_COLLIDERS];

	int acumvictory = 0;
	bool GodMode = false;
	int win=0;
	bool lose = false;

	bool death = false;
	bool onAir = false;

	int PivotX = 0;
	int PivotY = 0;
	int dmg = 0;

	bool leftLimit = false;
	bool RightLimit = false;

	int DeathCount = 0;
	int ActiveDeath = 0;
	int victorycount = 0;
	int speedX = 1;
	int speedY = 1;
	int acumdamage = 0;
	int jumpHeight = 0;
	int speed = 1;
	int damage_received = 0;
	int hit_started = 0;
	int hit_conected = 0;
	int block_damage = 0;
	bool jumpactive = 0;
	bool active = false;
	int life = 1000;
	int healthbar;

	bool crouchAttack = false;
	bool move = true;
	bool whirlwindMove = false;
	int lkcounter = 0;
	int wkcounter = 0;
	chunli_states2 state;


	Uint32 punch_hard_timer = 0;
	Uint32 punch_medium_timer = 0;
	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 kick_medium_timer = 0;
	Uint32 kick_hard_timer = 0;
	Uint32 hadouken_timer = 0;
	Uint32 punch_neutral_jump_timer = 0;
	Uint32 dmg_timer = 0;
	Uint32 dmg_hard_timer = 0;
	Uint32 dmg_fall_timer = 0;
	Uint32 block_timer = 0;
	Uint32 whirlwind_timer = 0;
	Uint32 victory_timer = 0;
	Uint32 victory2_timer = 0;
	Uint32 lose_timer = 0;

	bool left = false;
	bool left1 = false;
	bool left2 = false;
	bool right = false;
	bool right1 = false;
	bool right2 = false;

};

#endif