#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModulePlayer2.h"



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({7, 14, 60, 90});
	idle.PushBack({95, 15, 60, 89});
	idle.PushBack({184, 14, 60, 90});
	idle.PushBack({276, 11, 60, 93});
	idle.PushBack({366, 12, 60, 92});
	idle.speed = 0.175f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.15f;

	// walk backward animation
	backward.PushBack({ 542,127,61,91 });
	backward.PushBack({ 628,127,60,91 });
	backward.PushBack({ 713,127,58,91 });
	backward.PushBack({ 797,127,58,91 });
	backward.PushBack({ 883,127,57,91 });
	backward.PushBack({ 974,127,57,91 });
	backward.speed = 0.1f;

	//punch animation
	punch.PushBack({ 19,272,64,91 });
	punch.PushBack({ 108,272,92,91 });
	punch.PushBack({ 19,272,64,91 });
	punch.speed = 0.2f;

	//kick animation

	kick.PushBack({ 606,269,60,90 });
	kick.PushBack({ 689,267,66,92 });
	kick.PushBack({ 777,265,114,94 });
	kick.PushBack({ 689,267,66,92 });
	kick.speed = 0.175f;

	//hadouken animation
	hadouken_pose.PushBack({ 34,1545,74,90 });
	hadouken_pose.PushBack({ 135,1551,85,83 });
	hadouken_pose.PushBack({ 244,1552,91,83 });
	hadouken_pose.PushBack({ 357,1558,106,77 });
	hadouken_pose.speed = 0.1f;
	hadouken_pose.loop = false;

	//crouch animation
	crouch.PushBack({ 32,1212,53,83 });
	crouch.PushBack({ 115,1227,57,69 });
	crouch.PushBack({ 197,1235,61,61 });
	crouch.loop = false;
	crouch.speed = 0.3f;

	//neutral jump animation
	jump_neutral.PushBack({ 17,847,55,85 });
	jump_neutral.PushBack({ 17,847,55,85 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 177,805,50,89 });
	jump_neutral.PushBack({ 251,798,54,77 });
	jump_neutral.PushBack({ 327,813,48,70 });
	jump_neutral.loop = false;
	jump_neutral.speed = 0.175f;

	//neutral jump falling animation

	neutral_falling.PushBack({ 397,810,48,89 });
	neutral_falling.PushBack({ 464,819,55,109 });
	neutral_falling.PushBack({ 464,819,55,109 });
	neutral_falling.PushBack({ 464,819,55,109 });
	neutral_falling.PushBack({ 464,819,55,109 });
	neutral_falling.PushBack({ 464,819,55,109 });
	neutral_falling.PushBack({ 464,819,55,109 });
	neutral_falling.PushBack({ 464,819,55,109 });
	neutral_falling.PushBack({ 17,847,55,85 });
	neutral_falling.loop = false;
	neutral_falling.speed = 0.175f;
	

	//crouch punch
	Crouch_punch.PushBack({ 24,1344,69,61 });
	Crouch_punch.PushBack({ 118,1344,95,61 });
	Crouch_punch.speed = 0.2f;

	//death animation
	Death.PushBack({ 350,2233,124,48 });
	Death.PushBack({ 849,2246,123,41 });
	Death.PushBack({ 985,2265,127,31 });
	Death.loop = false;
	Death.speed = 0.05f;

	//Jump forward animation
	jump_forward.PushBack({ 594,823,55,103 });
	jump_forward.PushBack({ 669,813,61,78 });
	jump_forward.PushBack({ 744,811,104,42 });
	jump_forward.PushBack({ 864,791,53,82 });
	jump_forward.PushBack({ 927,808,122,44 });
	jump_forward.PushBack({ 1064,806,71,87 });
	jump_forward.PushBack({ 1149,802,55,109 });
	jump_forward.speed = 0.175f;

	//Jump backwards animation
	jump_backwards.PushBack({ 1149,802,55,109 });
	jump_backwards.PushBack({ 1064,806,71,87 });
	jump_backwards.PushBack({ 927,808,122,44 });
	jump_backwards.PushBack({ 864,791,53,82 });
	jump_backwards.PushBack({ 744,811,104,42 });
	jump_backwards.PushBack({ 669,813,61,78 });
	jump_backwards.PushBack({ 594,823,55,103 });
	jump_backwards.speed = 0.175f;

	//Jump neutral punch
	jump_neutral_punch.PushBack({ 29,987,52,69 });
	jump_neutral_punch.PushBack({ 97,985,81,71 });
	jump_neutral_punch.speed = 0.1f;



	//Sounds
	//deathSound = App->audio->LoadChunk("Game/Assets/Sound/ryu-death.wav");

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/ryu.png"); // arcade version
	position.x = 100; //Returns to its original position
	
	//Add a collider to the player
	colliderplayer = App->collision->AddCollider({ position.x,position.y,60,-90 }, COLLIDER_PLAYER,App->player);
	
	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player textures");

	App->textures->Unload(graphics);

	return true;
}



// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;
	p2Qeue<ryu_inputs> inputs;
	ryu_states current_state = ST_UNKNOWN;
	
	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {
		if (GodMode == false) {
			App->collision->DeleteCollider(colliderplayer);

			GodMode = true;
		}
		else if (GodMode == true) {
			colliderplayer = App->collision->AddCollider({ position.x,position.y,60,-90 }, COLLIDER_PLAYER, this);

			GodMode = false;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {
		life = 0;
	}

	if (life == 0) {
		inputs.Push(IN_DEATH);
	}


		while (external_input(inputs))
		{

			internal_input(inputs);

			ryu_states state = process_fsm(inputs);

			if (state != current_state)
			{
				switch (state)
				{
				case ST_IDLE:
					current_animation = &idle;
					forward.Reset();
					backward.Reset();
					crouch.Reset();
					kick.Reset();
					punch.Reset();
					hadouken_pose.Reset();
					HadoukenCount = 0;
					ActiveHadouken = 0;
					break;
				case ST_WALK_FORWARD:
					if (position.x < 825)
					{
						position.x += speed;
						if (-((position.x - 60)*2) <= App->render->camera.x - SCREEN_WIDTH)
						{
							if (App->render->camera.x > -1004)
							{
								App->render->camera.x -= 5;
							}
							//LOG("Cam posx: %d", camera.x);
							LOG("Cam posxMax: %d",App->render->camera.x - SCREEN_WIDTH);
						}
						
					}
					//LOG("Player posx: %d", position.x);
					current_animation = &forward;
					crouch.Reset();
					kick.Reset();
					punch.Reset();
					hadouken_pose.Reset();
					HadoukenCount = 0;
					ActiveHadouken = 0;													
					break;
				case ST_WALK_BACKWARD:
					current_animation = &backward;
					if (position.x > 0)
					{
						position.x -= (0.6 *speed);
						if (-(position.x*2) >= App->render->camera.x-5)
						{
							if (App->render->camera.x < 0)
							{
								App->render->camera.x += 5;
							}
						}						
						//LOG("Player posx: %d",-position.x);
					}		
					crouch.Reset();
					kick.Reset();
					punch.Reset();
					hadouken_pose.Reset();
					HadoukenCount = 0;
					ActiveHadouken = 0;
					break;
				case ST_JUMP_NEUTRAL:
					JumpCount = 1;
					if (JumpCount == 1) {
						if (position.y == 220) {
							JumpMax = false;
							JumpMin = true;
						}
						if (position.y == 174) {
							JumpMin = false;
							JumpMax = true;
						}

						if (JumpMin == true) {
							neutral_falling.Reset();
							position.y -= speed;
							current_animation = &jump_neutral;
						}
						if (JumpMax == true) {
							jump_neutral.Reset();
							position.y += speed;
							current_animation = &neutral_falling;
						}

					}
					break;
				case ST_JUMP_FORWARD:

					current_animation = &jump_forward;
					break;
				case ST_JUMP_BACKWARD:
					
					current_animation = &jump_backwards;
					break;
				case ST_CROUCH:
					current_animation = &crouch;
					break;
				case ST_PUNCH_STANDING:
					current_animation = &punch;
					punchcollider = App->collision->AddCollider({ position.x + 41, position.y - 79, 51, 13 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->collision->DeleteCollider(punchcollider);
					break;
				case ST_PUNCH_CROUCH:
					current_animation = &Crouch_punch;
					crouchpunchcollider = App->collision->AddCollider({ position.x + 48, position.y - 49, 48, 10 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->collision->DeleteCollider(crouchpunchcollider);
					break;
				case ST_PUNCH_NEUTRAL_JUMP:

					current_animation = &jump_neutral_punch;
					break;
				case ST_PUNCH_FORWARD_JUMP:

					break;
				case ST_PUNCH_BACKWARD_JUMP:

					break;
				case ST_KICK_STANDING:
					current_animation = &kick;
					kickcollider = App->collision->AddCollider({ position.x + 45, position.y - 92, 70, 27 }, COLLIDER_PLAYER_ATTACK, this);
					App->collision->DeleteCollider(kickcollider);
					break;
				case ST_HADOUKEN:
					current_animation = &hadouken_pose;
					if (HadoukenCount < 35) {
						HadoukenCount++;
					}
					if (HadoukenCount == 35 && ActiveHadouken == 0) {
						App->particle->AddParticle(App->particle->hadouken, position.x + 65, position.y - 70, COLLIDER_PLAYER_ATTACK, 0);
						App->audio->PlayChunk(App->particle->hadouken.sound, 0);
						HadoukenCount = 0;
						ActiveHadouken = 1;
					}
					break;
				case ST_DEATH:
					current_animation = &Death;
					App->audio->PlayChunk(deathSound, 0);
					break;
				}
			}

			current_state = state;

			// Draw everything --------------------------------------

			SDL_Rect r = current_animation->GetCurrentFrame();
			App->render->Blit(graphics, position.x, position.y - r.h, &r);

			//Update collider position to player position
			colliderplayer->SetPos(position.x, position.y);

			return UPDATE_CONTINUE;
		}
	}
	

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
		//LOG("colision detected");
		if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY) 
		{
			movef = false;
		}
}

bool ModulePlayer::external_input(p2Qeue<ryu_inputs>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;

	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_s:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_w:
				up = false;
				break;
			case SDLK_a:
				inputs.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_d:
				inputs.Push(IN_RIGHT_UP);
				right = false;
				break;
			case SDLK_p:
				return false;
				break;
			case SDLK_k:
				return false;
				break;
			case SDLK_h:
				return false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_p:
				inputs.Push(IN_P);
				break;
			case SDLK_k:
				inputs.Push(IN_K);
				break;
			case SDLK_h:
				inputs.Push(IN_H);
				break;
			case SDLK_w:
				up = true;
				break;
			case SDLK_s:
				down = true;
				break;
			case SDLK_a:
				left = true;
				break;
			case SDLK_d:
				right = true;
				break;
			}
		}
	}

	if (left && right)
		inputs.Push(IN_LEFT_AND_RIGHT);
	{
		if (left)
			inputs.Push(IN_LEFT_DOWN);
		if (right)
			inputs.Push(IN_RIGHT_DOWN);
	}

	if (up && down)
		inputs.Push(IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			inputs.Push(IN_CROUCH_DOWN);
		if (up)
			inputs.Push(IN_JUMP);
	}

	return true;
}

void ModulePlayer::internal_input(p2Qeue<ryu_inputs>& inputs)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
			position.y = 220;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME)
		{
			inputs.Push(IN_KICK_FINISH);
			kick_timer = 0;
		}
	}

	if (hadouken_timer > 0)
	{
		if (SDL_GetTicks() - hadouken_timer > HADOUKEN_TIME)
		{
			inputs.Push(IN_HADOUKEN_FINISH);
			hadouken_timer = 0;
		}
	}
}
