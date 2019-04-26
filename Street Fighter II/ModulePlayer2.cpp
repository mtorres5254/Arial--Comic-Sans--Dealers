#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	position.x = 300;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 786, 12, 58, 92 });
	idle.PushBack({ 876, 11, 53, 93 });
	idle.PushBack({ 968, 14, 59, 90 });
	idle.PushBack({ 1057, 15, 60, 89 });
	idle.PushBack({ 1145, 14, 59, 90 });
	idle.speed = 0.175f;

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 729, 131, 50, 89 });
	forward.PushBack({ 805, 128, 54, 91 });
	forward.PushBack({ 889, 128, 63, 90 });
	forward.PushBack({ 985, 128, 64, 92 });
	forward.PushBack({ 1073, 131, 60, 88 });
	forward.PushBack({ 1149, 136, 53, 83 });
	forward.speed = 0.15f;

	// walk backward animation
	backward.PushBack({ 180, 129, 57, 89 });
	backward.PushBack({ 270, 128, 58, 91 });
	backward.PushBack({ 356, 127, 58, 90 });
	backward.PushBack({ 441, 128, 57, 90 });
	backward.PushBack({ 524, 129, 59, 90 });
	backward.PushBack({ 608, 131, 61, 87 });
	backward.speed = 0.1f;

	//punch animation
	punch.PushBack({ 1128,272,64,91 });
	punch.PushBack({ 1011,272,92,91 });
	punch.PushBack({ 1128,272,64,91 });
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
	jump_neutral.PushBack({ 1139,847,55,85 });
	jump_neutral.PushBack({ 1055,823,56,104 });
	jump_neutral.PushBack({ 1055,823,56,104 });
	jump_neutral.PushBack({ 1055,823,56,104 });
	jump_neutral.PushBack({ 1055,823,56,104 });
	jump_neutral.PushBack({ 1055,823,56,104 });
	jump_neutral.PushBack({ 1055,823,56,104 });
	jump_neutral.PushBack({ 1055,823,56,104 });
	jump_neutral.PushBack({ 985,805,50,89 });
	jump_neutral.PushBack({ 985,805,50,89 });
	jump_neutral.PushBack({ 985,805,50,89 });
	jump_neutral.PushBack({ 985,805,50,89 });
	jump_neutral.PushBack({ 906,798,54,77 });
	jump_neutral.PushBack({ 836,813,48,70 });
	jump_neutral.loop = false;
	jump_neutral.speed = 0.175f;

	//neutral jump falling animation

	falling.PushBack({ 766,810,48,89 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.PushBack({ 692,819,55,109 });
	falling.loop = false;
	falling.speed = 0.175f;


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
	jump_forward.PushBack({ 562,823,55,103 });
	jump_forward.PushBack({ 562,823,55,103 });
	jump_forward.PushBack({ 562,823,55,103 });
	jump_forward.PushBack({ 562,823,55,103 });
	jump_forward.PushBack({ 562,823,55,103 });
	jump_forward.PushBack({ 562,823,55,103 });
	jump_forward.PushBack({ 481,813,61,78 });
	jump_forward.PushBack({ 363,811,104,42 });
	jump_forward.PushBack({ 292,791,53,82 });
	jump_forward.PushBack({ 162,808,122,44 });
	jump_forward.PushBack({ 76,806,71,87 });
	jump_forward.PushBack({ 7,802,55,109 });
	jump_forward.loop = false;
	jump_forward.speed = 0.175f;

	//Jump backwards animation
	jump_backwards.PushBack({ 76,806,71,87 });
	jump_backwards.PushBack({ 76,806,71,87 });
	jump_backwards.PushBack({ 76,806,71,87 });
	jump_backwards.PushBack({ 76,806,71,87 });
	jump_backwards.PushBack({ 76,806,71,87 });
	jump_backwards.PushBack({ 76,806,71,87 });
	jump_backwards.PushBack({ 162,808,122,44 });
	jump_backwards.PushBack({ 292,791,53,82 });
	jump_backwards.PushBack({ 363,811,104,42 });
	jump_backwards.PushBack({ 481,813,61,78 });
	jump_backwards.PushBack({ 562,823,55,103 });
	jump_backwards.loop = false;
	jump_backwards.speed = 0.175f;

	//Jump neutral punch
	jump_neutral_punch.PushBack({ 29,987,52,69 });
	jump_neutral_punch.PushBack({ 97,985,81,71 });
	jump_neutral_punch.speed = 0.1f;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/ryu2.png"); // arcade version
	position.x = 300; //Returns to its original position

	//Add a collider to the player
	colliderplayer = App->collision->AddCollider({ position.x + 7 ,position.y - 90,45,90 }, COLLIDER_ENEMY, App->player2);

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
	Animation* current_animation = &idle;
	p2Qeue<ryu2_inputs> inputs;
	ryu2_states current_state = ST_UNKNOWN;

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {
		if (GodMode == false) {
			App->collision->DeleteCollider(colliderplayer);

			GodMode = true;
		}
		else if (GodMode == true) {
			colliderplayer = App->collision->AddCollider({ position.x + 7 ,position.y - 90,45,90 }, COLLIDER_ENEMY, App->player2);

			GodMode = false;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) { //Treu-re abans d'entregar
		life = life - 200;
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
					current_animation = &backward;
					if (position.x < 825)
					{
						position.x += speed;
						if (-((position.x - 60) * 2) <= App->render->camera.x - SCREEN_WIDTH)
						{
							if (App->render->camera.x > -1004)
							{
								App->render->camera.x -= speed * 2;
							}
						}
					}
					crouch.Reset();
					kick.Reset();
					punch.Reset();
					hadouken_pose.Reset();
					HadoukenCount = 0;
					ActiveHadouken = 0;
					break;
				case ST_WALK_BACKWARD:
					if (moveb == true) {
						current_animation = &forward;
						if (position.x > 0)
						{
							position.x -= (0.6 *speed);
							if (-(position.x * 2) >= App->render->camera.x - 5)
							{
								if (App->render->camera.x < 0)
								{
									App->render->camera.x += speed * 2;
								}
							}
						}
						crouch.Reset();
						kick.Reset();
						punch.Reset();
						hadouken_pose.Reset();
						HadoukenCount = 0;
						ActiveHadouken = 0;
					}
					else if (moveb == false) {
						moveb = true;
					}
					break;
				case ST_JUMP_NEUTRAL:
					JumpCount = 1;
					if (JumpCount == 1) {
						if (position.y == 220) {
							JumpMax = false;
							JumpMin = true;
						}
						if (position.y <= 110) {
							JumpMin = false;
							JumpMax = true;
						}

						if (JumpMin == true) {
							falling.Reset();
							position.y -= speed * 2;
							current_animation = &jump_neutral;
						}
						if (JumpMax == true) {
							jump_neutral.Reset();
							position.y += speed * 3.2;
							current_animation = &falling;
						}

					}
					break;
				case ST_JUMP_FORWARD:
					if (position.x < 825)
					{
						position.x += speed;
						if (-((position.x - 60) * 2) <= App->render->camera.x - SCREEN_WIDTH && App->input->camMoving == false)
						{
							if (App->render->camera.x > -1004)
							{
								App->render->camera.x -= speed * 2;
							}
						}
					}
					JumpCount = 1;
					if (JumpCount == 1) {
						if (position.y == 220) {
							JumpMax = false;
							JumpMin = true;
						}
						if (position.y <= 110) {
							JumpMin = false;
							JumpMax = true;
						}

						if (JumpMin == true) {
							falling.Reset();
							position.y -= (speed * 2);
							current_animation = &jump_backwards;
						}
						if (JumpMax == true) {
							jump_backwards.Reset();
							position.y += (speed * 3.2);
							current_animation = &falling;
						}
					}
					break;
				case ST_JUMP_BACKWARD:
					if (position.x > 0)
					{
						position.x -= (0.6 *speed);
						if (-(position.x * 2) >= App->render->camera.x - 5)
						{
							if (App->render->camera.x < 0)
							{
								App->render->camera.x += speed * 2;
							}
						}
					}
					JumpCount = 1;
					if (JumpCount == 1) {
						if (position.y == 220) {
							JumpMax = false;
							JumpMin = true;
						}
						if (position.y <= 110) {
							JumpMin = false;
							JumpMax = true;
						}

						if (JumpMin == true) {
							falling.Reset();
							position.y -= (speed * 2);
							current_animation = &jump_forward;
						}
						if (JumpMax == true) {
							jump_forward.Reset();
							position.y += (speed * 3.2);
							current_animation = &falling;
						}
					}
					break;
				case ST_CROUCH:
					current_animation = &crouch;
					break;
				case ST_PUNCH_STANDING:
					current_animation = &punch;
					punchcollider = App->collision->AddCollider({ position.x - 20, position.y - 79, 51, 13 }, COLLIDER_ENEMY_SHOT, App->player2, 25);
					App->collision->DeleteCollider(punchcollider);
					break;
				case ST_PUNCH_CROUCH:
					current_animation = &Crouch_punch;
					crouchpunchcollider = App->collision->AddCollider({ position.x + 48, position.y - 49, 48, 10 }, COLLIDER_ENEMY_SHOT, App->player2, 25);
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
					kickcollider = App->collision->AddCollider({ position.x + 45, position.y - 92, 70, 27 }, COLLIDER_ENEMY_SHOT, App->player2, 50);
					App->collision->DeleteCollider(kickcollider);
					break;
				case ST_HADOUKEN:
					current_animation = &hadouken_pose;
					if (HadoukenCount < 35) {
						HadoukenCount++;
					}
					if (HadoukenCount == 35 && ActiveHadouken == 0) {
						App->particle->AddParticle(App->particle->hadoukenSym, position.x + 65, position.y - 70, COLLIDER_ENEMY_SHOT, 0);
						App->audio->PlayChunk(App->particle->hadoukenSym.sound, 0);
						HadoukenCount = 0;
						ActiveHadouken = 1;
					}
				case ST_RECEIVED_PUNCH:
					current_animation = &ReceivedPunch;
					if (ReceivedPunch.current_frame == 3) {
						break;
					}
					break;
				}
			}

			if (life < 0) {
				life = 0;
			}
			if (life == 0)
			{
				current_animation = &Death;
				App->audio->PlayChunk(deathSound, 0);
				ResetPlayer();
			}

			current_state = state;

			healthbar = life * 0.153;

			// Draw everything --------------------------------------

			SDL_Rect r = current_animation->GetCurrentFrame();
			App->render->Blit(graphics, position.x, position.y - r.h, &r);

			//Update collider position to player position
			colliderplayer->SetPos(position.x + 7, position.y - 90);

			return UPDATE_CONTINUE;
		}
	}

}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {
	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER)
	{
		moveb = false;
	}
	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER_ATTACK) {
		int aux = life;
		life = aux - c2->damage;
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
	for (int a = 0; a < max; ++a)
	{
		event = App->input->eventList.front();
		App->input->eventList.pop_front();
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_DOWN://Crouch
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_UP://Jump
				up = false;
				break;
			case SDLK_LEFT://Left
				inputs.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_RIGHT://Right
				inputs.Push(IN_RIGHT_UP);
				right = false;
				break;
			case SDLK_b:
				return false;
				break;
			case SDLK_n:
				return false;
				break;
			case SDLK_m:
				return false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_b:
				inputs.Push(IN_P);
				break;
			case SDLK_n:
				inputs.Push(IN_K);
				break;
			case SDLK_m:
				inputs.Push(IN_H);
				break;
			case SDLK_UP:
				up = true;
				break;
			case SDLK_DOWN:
				down = true;
				break;
			case SDLK_LEFT:
				left = true;
				break;
			case SDLK_RIGHT:
				right = true;
				break;
			}
		}
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

void ModulePlayer2::ResetPlayer() {
	life = 1000;
	position.x = 300; //Returns to its original position
	if (App->player->position.x != 100 || App->player->life != 1000) {
		App->player->ResetPlayer();
	}
}

