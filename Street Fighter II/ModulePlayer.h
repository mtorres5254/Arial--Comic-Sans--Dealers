#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#include <string.h>
#include "p2Qeue.h"
#include "SDL\include\SDL.h"

#define JUMP_TIME 1500
#define PUNCH_TIME 150

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
	Animation crouch;
	Animation jump_neutral;
	Animation Crouch_punch;
	iPoint position;
	/*int PunchCount = 0;
	int KickCount = 0;
	int HadoukenCount = 0;
	bool moving = false;*/
	int JumpCount = 0;
	bool JumpMin = false;
	bool JumpMax = false;
	bool movef = false;
	bool moveb = false;
	
	Collider* colliderplayer;	

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
		ST_PUNCH_CROUCH
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
		IN_JUMP_FINISH,
		IN_PUNCH_FINISH
	};
	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;

	bool external_input(p2Qeue<ryu_inputs>&);

	void internal_input(p2Qeue<ryu_inputs>&);

	ryu_states process_fsm(p2Qeue<ryu_inputs>& inputs)
	{
		static ryu_states state = ST_IDLE;
		ryu_inputs last_input;

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
					// TODO: Add links
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_X: state = ST_PUNCH_FORWARD_JUMP; punch_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_JUMP_BACKWARD:
			{
				switch (last_input)
				{
					// TODO: Add Links
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_X: state = ST_PUNCH_BACKWARD_JUMP; punch_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_PUNCH_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
					// TODO: Add Links
				case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;

				}
			}
			break;

			case ST_PUNCH_FORWARD_JUMP:
			{
				switch (last_input)
				{
					// TODO: Add Links
				case IN_PUNCH_FINISH: state = ST_JUMP_FORWARD; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				}
			}
			break;

			case ST_PUNCH_BACKWARD_JUMP:
			{
				switch (last_input)
				{
					// TODO: Add Links
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
			}
		}

		return state;
	}
};

#endif