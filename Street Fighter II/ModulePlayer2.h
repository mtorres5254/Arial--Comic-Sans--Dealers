#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include <string.h>
#include "p2Qeue.h"

#include "SDL\include\SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define JUMP_TIME 1500
#define PUNCH_TIME 150
#define KICK_TIME 400
#define HADOUKEN_TIME 1500


struct SDL_Texture;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void ResetPlayer();

public:

	SDL_Texture* graphics = nullptr;
	Mix_Chunk* deathSound;
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
	Animation neutral_falling;
	Animation Crouch_punch;
	Animation jump_neutral_punch;
	Animation Death;
	iPoint position;
	int HadoukenCount = 0;
	int ActiveHadouken = 0;
	int JumpCount = 0;
	bool JumpMin = false;
	bool JumpMax = false;
	bool movef = true;
	bool moveb = true;
	bool death = false;
	bool GodMode = false;


	int life = 1000;
	int healthbar;
	
private:
	Collider * colliderplayer;
	Collider* punchcollider;
	Collider* crouchpunchcollider;
	Collider* kickcollider;


	enum ryu2_states
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
	};

	enum ryu2_inputs
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
		IN_P,
		IN_K,
		IN_H,
		IN_JUMP_FINISH,
		IN_PUNCH_FINISH,
		IN_KICK_FINISH,
		IN_HADOUKEN_FINISH,
	};

	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 hadouken_timer = 0;

	bool external_input(p2Qeue<ryu2_inputs>&);

	void internal_input(p2Qeue<ryu2_inputs>&);

	ryu2_states process_fsm(p2Qeue<ryu2_inputs>& inputs)
	{
		static ryu2_states state = ST_IDLE;
		ryu2_inputs last_input;

		while (inputs.Pop(last_input))
		{
			switch (state)
			{
			case ST_IDLE:
			{
				switch (last_input)
				{
				case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
				case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
				case IN_JUMP: state = ST_JUMP_NEUTRAL; jump_timer = SDL_GetTicks();  break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_P: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
				case IN_K: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
				case IN_H: state = ST_HADOUKEN; hadouken_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_WALK_FORWARD:
			{
				switch (last_input)
				{
				case IN_RIGHT_UP: state = ST_IDLE; break;
				case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
				case IN_JUMP: state = ST_JUMP_FORWARD; jump_timer = SDL_GetTicks();  break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_P: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
				case IN_K: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
				case IN_H: state = ST_HADOUKEN; hadouken_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_WALK_BACKWARD:
			{
				switch (last_input)
				{
				case IN_LEFT_UP: state = ST_IDLE; break;
				case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
				case IN_JUMP: state = ST_JUMP_BACKWARD; jump_timer = SDL_GetTicks();  break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_P: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
				case IN_K: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
				case IN_H: state = ST_HADOUKEN; hadouken_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_JUMP_NEUTRAL:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_P: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_JUMP_FORWARD:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_P: state = ST_PUNCH_FORWARD_JUMP; punch_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_JUMP_BACKWARD:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_P: state = ST_PUNCH_BACKWARD_JUMP; punch_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_PUNCH_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				}
			}
			break;

			case ST_PUNCH_FORWARD_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_FORWARD; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				}
			}
			break;

			case ST_PUNCH_BACKWARD_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_BACKWARD; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				}
			}
			break;

			case ST_PUNCH_STANDING:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_IDLE; break;
				}
			}
			break;

			case ST_CROUCH:
			{
				switch (last_input)
				{
				case IN_CROUCH_UP: state = ST_IDLE; break;
				case IN_JUMP_AND_CROUCH: state = ST_IDLE; break;
				case IN_P: state = ST_PUNCH_CROUCH; punch_timer = SDL_GetTicks(); break;
				}
			}
			break;
			case ST_PUNCH_CROUCH:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH:
					if (IN_CROUCH_DOWN == true)
						state = ST_CROUCH;
					else
						state = ST_IDLE;
					break;
				}
			}
			break;
			case ST_KICK_STANDING:
			{
				switch (last_input)
				{
				case IN_KICK_FINISH: state = ST_IDLE; break;
				}
			}
			break;
			case ST_HADOUKEN:
			{
				switch (last_input)
				{
				case IN_HADOUKEN_FINISH: state = ST_IDLE; break;
				}
				break;
			}

			}
		}
		return state;
	}
};

#endif