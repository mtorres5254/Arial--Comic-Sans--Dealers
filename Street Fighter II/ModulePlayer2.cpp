#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	position.x = 300;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 7, 14, 60, 90 });
	idle.PushBack({ 95, 15, 60, 89 });
	idle.PushBack({ 184, 14, 60, 90 });
	idle.PushBack({ 276, 11, 60, 93 });
	idle.PushBack({ 366, 12, 60, 92 });
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({ 78, 131, 60, 88 });
	forward.PushBack({ 162, 128, 64, 92 });
	forward.PushBack({ 259, 128, 63, 90 });
	forward.PushBack({ 352, 128, 54, 91 });
	forward.PushBack({ 432, 131, 50, 89 });
	forward.speed = 0.1f;

	//punch animation
	punch.PushBack({ 19,272,64,91 });
	punch.PushBack({ 108,272,91,91 });
	//punch.PushBack({ 19,272,64,91 });
	punch.speed = 0.05f;

	// walk backward animation
	backward.PushBack({ 542,127,61,91 });
	backward.PushBack({ 628,127,60,91 });
	backward.PushBack({ 713,127,58,91 });
	backward.PushBack({ 797,127,58,91 });
	backward.PushBack({ 883,127,57,91 });
	backward.PushBack({ 974,127,57,91 });
	backward.speed = 0.05f;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/ryu.png"); // arcade version
	position.x = 300; //Returns to its original position

	//Add a collider to the player
	colliderplayer2 = App->collision->AddCollider({ position.x,position.y,60,-90 }, COLLIDER_ENEMY);
	colliderplayer2->callback = App->player2;

	return ret;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading Player textures");

	App->textures->Unload(graphics);

	return true;
}



// Update: draw background
update_status ModulePlayer2::Update()
{
	/*Animation* current_animation = &idle;

	int speed = 1;
	

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	//Update collider position to player position

	colliderplayer2->SetPos(position.x, position.y);
	OnCollision(colliderplayer2, App->particle->hadouken.collider);

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;*/


	//////////////////////////////////
	Animation* current_animation = &idle;
	p2Qeue<ryu2_inputs> inputs;
	ryu2_states current_state = ST_UNKNOWN;

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN) {
		/*if (GodMode == false) {
			App->collision->DeleteCollider(colliderplayer);

			GodMode = true;
		}
		else if (GodMode == true) {
			colliderplayer = App->collision->AddCollider({ position.x,position.y,60,-90 }, COLLIDER_PLAYER, this);

			GodMode = false;
		}*/
		//LOG("Detected");
	}

	/*if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {
		life = 0;
	}*/

	if (life == 0) {
		current_animation = &Death;
		death = true;
	}

	if (death == false) {
		while (external_input(inputs))
		{

			internal_input(inputs);

			ryu2_states state = process_fsm(inputs);

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
						if (-((position.x - 60) * 2) <= App->render->camera.x - SCREEN_WIDTH)
						{
							if (App->render->camera.x > -1004)
							{
								App->render->camera.x -= speed*2;
							}
							//LOG("Cam posx: %d", camera.x);
							//LOG("Cam posxMax: %d", App->render->camera.x - SCREEN_WIDTH);
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
						if (-(position.x * 2) >= App->render->camera.x - 5)
						{
							if (App->render->camera.x < 0)
							{
								App->render->camera.x += speed*2;
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
					punchcollider = App->collision->AddCollider({ position.x + 41, position.y - 79, 51, 13 }, COLLIDER_ENEMY_SHOT, this);
					App->collision->DeleteCollider(punchcollider);
					break;
				case ST_PUNCH_CROUCH:
					current_animation = &Crouch_punch;
					crouchpunchcollider = App->collision->AddCollider({ position.x + 48, position.y - 49, 48, 10 }, COLLIDER_ENEMY_SHOT, this);
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
					kickcollider = App->collision->AddCollider({ position.x + 45, position.y - 92, 70, 27 }, COLLIDER_ENEMY_SHOT, this);
					App->collision->DeleteCollider(kickcollider);
					break;
				case ST_HADOUKEN:
					current_animation = &hadouken_pose;
					if (HadoukenCount < 35) {
						HadoukenCount++;
					}
					if (HadoukenCount == 35 && ActiveHadouken == 0) {
						App->particle->AddParticle(App->particle->hadouken, position.x + 65, position.y - 70, COLLIDER_ENEMY_SHOT, 0);
						App->audio->PlayChunk(App->particle->hadouken.sound, 0);
						HadoukenCount = 0;
						ActiveHadouken = 1;
					}

					break;
				}
			}

			current_state = state;

			// Draw everything --------------------------------------

			SDL_Rect r = current_animation->GetCurrentFrame();
			App->render->Blit(graphics, position.x, position.y - r.h, &r);

			//Update collider position to player position
			colliderplayer2->SetPos(position.x, position.y);

			return UPDATE_CONTINUE;
		}
	}

}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {
	//LOG("colision detected");
	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER)
	{
		movef = false;
	}
}

bool ModulePlayer2::external_input(p2Qeue<ryu2_inputs>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;

	SDL_Event event;
	int max = App->input->eventList.size();
	//while (SDL_PollEvent(&event) != 0) //Always find no events to poll why?
	for (int a = 0; a < max; ++a)
	{
		event = App->input->eventList.front();
		App->input->eventList.pop_front();
		//LOG("Events detected"); // Never enters
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_3://Crouch
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_4://Jump
				up = false;
				break;
			case SDLK_1://Left
				inputs.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_2://Right
				inputs.Push(IN_RIGHT_UP);
				right = false;
				break;
			case SDLK_0:
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
		/*if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_0:
				inputs.Push(IN_P);
				break;
			case SDLK_k:
				inputs.Push(IN_K);
				break;
			case SDLK_h:
				inputs.Push(IN_H);
				break;
			case SDLK_4:
				up = true;
				break;
			case SDLK_3:
				down = true;
				break;
			case SDLK_1:
				left = true;
				break;
			case SDLK_2:
				right = true;
				break;
			}
		}*/
		App->input->eventList.push_back(event);
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

void ModulePlayer2::internal_input(p2Qeue<ryu2_inputs>& inputs)
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
