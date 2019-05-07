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



struct SDL_Texture;

class ModuleChunLi : public Module
{
public:
	ModuleChunLi();
	~ModuleChunLi();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void ResetPlayer();

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

	bool damage_received = false;

	int life = 1000;
	int healthbar;

private:

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
		ST_HADOUKEN,
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
		IN_V,
		IN_JUMP_FINISH,
		IN_PUNCH_FINISH,
		IN_KICK_FINISH,
		IN_HADOUKEN_FINISH,
		IN_RECEIVED_PUNCH,
	};

	

	chunli_states state;

	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 hadouken_timer = 0;



	bool external_input(p2Qeue<chunli_inputs>&);

	void internal_input(p2Qeue<chunli_inputs>&);

	chunli_states process_fsm(p2Qeue<chunli_inputs>& inputs)
	{
		static chunli_states state = ST_IDLE;
		chunli_inputs last_input;

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
				case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
				case IN_C: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
				case IN_V: state = ST_HADOUKEN; hadouken_timer = SDL_GetTicks(); break;
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
				case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
				case IN_C: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
				case IN_V: state = ST_HADOUKEN; hadouken_timer = SDL_GetTicks(); break;
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
				case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
				case IN_C: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
				case IN_V: state = ST_HADOUKEN; hadouken_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_JUMP_NEUTRAL:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_X: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_JUMP_FORWARD:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_X: state = ST_PUNCH_FORWARD_JUMP; punch_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_JUMP_BACKWARD:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_X: state = ST_PUNCH_BACKWARD_JUMP; punch_timer = SDL_GetTicks(); break;
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
				case IN_X: state = ST_PUNCH_CROUCH; punch_timer = SDL_GetTicks(); break;
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