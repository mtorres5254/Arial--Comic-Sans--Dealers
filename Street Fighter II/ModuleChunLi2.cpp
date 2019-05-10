#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleChunLi.h"
#include "ModuleParticles.h"
#include "ModuleChunLi2.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "p2Qeue.h"
#include "Application.h"



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleChunLi2::ModuleChunLi2()
{}

ModuleChunLi2::~ModuleChunLi2()
{}

// Load assets
bool ModuleChunLi2::Start()
{

	bool ret = true;

	graphics = App->textures->Load("Assets/Images/ChunLi.png"); // arcade version

	position.x = 375;
	position.y = 220;

	// idle animation (arcade sprite sheet)


	const int idleCollider = 5;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 },{ 9,4,51,54 },{ 1,3,45,33 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	Module* idleCallBack[idleCollider] = { { this },{ this },{ this },{ this },{ this } };

	idle.PushBack1({ 290, 438, 72, 85 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack1({ 363, 437, 72, 86 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack1({ 436, 436, 72, 87 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack1({ 363, 437, 72, 86 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.speed = 0.1f;

	//Forward

	const int fwdcollider = 5;//Collider num for the idle animation
	SDL_Rect fwdhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE fwdCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	Module* fwdCallback[idleCollider] = { { this },{ this },{ this },{ this },{ this } };
	forward.PushBack1({ 652,437, 73, 86 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 726, 434, 63, 89 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 790, 433, 60, 90 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 851, 432, 63, 91 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 915, 433, 64, 90 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 0, 531, 64, 89 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 66, 532, 72, 88 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 0, 531, 64, 89 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 915, 433, 64, 90 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 851, 432, 63, 91 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 790, 433, 60, 90 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.PushBack1({ 726, 434, 63, 89 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	forward.speed = 0.2f;


	//Backward

	const int bwdcollider = 5;//Collider num for the idle animation
	SDL_Rect bwdhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE bcwCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	Module* bwdCallback[idleCollider] = { { this },{ this },{ this },{ this },{ this } };
	backward.PushBack1({ 652,437, 73, 86 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 726, 434, 63, 89 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 790, 433, 60, 90 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 851, 432, 63, 91 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 915, 433, 64, 90 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 0, 531, 64, 89 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 66, 532, 72, 88 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 0, 531, 64, 89 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 915, 433, 64, 90 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 851, 432, 63, 91 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 790, 433, 60, 90 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.PushBack1({ 726, 434, 63, 89 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	backward.speed = 0.15f;

	//Crouch

	crouch.PushBack({ 934,742 , 74, 81 });
	crouch.PushBack({ 0, 833, 73, 72 });
	crouch.PushBack({ 74, 839, 72, 66 });
	crouch.PushBack({ 147, 839, 72, 65 });
	crouch.speed = 0.3f;
	crouch.loop = false;

	//Jump 

	jump_neutral.PushBack({ 1756, 1, 47, 110 });
	jump_neutral.PushBack({ 1804, 27, 50, 84 });
	jump_neutral.PushBack({ 1855, 36, 52, 75 });
	jump_neutral.PushBack({ 1908, 46, 57, 65 });
	jump_neutral.PushBack({ 1908, 46, 57, 65 });
	jump_neutral.PushBack({ 1908, 46, 57, 65 });
	jump_neutral.PushBack({ 1855, 36, 52, 75 });
	jump_neutral.PushBack({ 1804, 27, 50, 84 });
	jump_neutral.PushBack({ 1756, 1, 47, 110 });

	jump_neutral.speed = 0.21f;
	jump_neutral.loop = false;

	//jump forward

	jump_forward.PushBack({ 1756, 1, 47, 110 });
	jump_forward.PushBack({ 925,940,50,84 });
	jump_forward.PushBack({ 1024,30,88,81 });
	jump_forward.PushBack({ 1113,63,121,48 });
	jump_forward.PushBack({ 1235,23,109,88 });
	jump_forward.PushBack({ 1345,7,52,104 });
	jump_forward.PushBack({ 1398,30,110,81 });
	jump_forward.PushBack({ 1509,45,119,66 });
	jump_forward.PushBack({ 1629,35,95,76 });
	jump_forward.PushBack({ 1756, 1, 47, 110 });
	jump_forward.speed = 0.19f;
	jump_forward.loop = true;

	//jump backward

	jump_backwards.PushBack({ 1756, 1, 47, 110 });
	jump_backwards.PushBack({ 925,940,50,84 });
	jump_backwards.PushBack({ 1629,35,95,76 });
	jump_backwards.PushBack({ 1509,45,119,66 });
	jump_backwards.PushBack({ 1398,30,110,81 });
	jump_backwards.PushBack({ 1345,7,52,104 });
	jump_backwards.PushBack({ 1235,23,109,88 });
	jump_backwards.PushBack({ 1113,63,121,48 });
	jump_backwards.PushBack({ 1024,30,88,81 });
	jump_backwards.PushBack({ 1756, 1, 47, 110 });
	jump_backwards.speed = 0.19f;
	jump_backwards.loop = true;


	//Punch animation

	punch.PushBack({ 139, 533, 78, 87 });
	punch.PushBack({ 218, 531, 101, 89 });
	punch.PushBack({ 320, 524, 87, 96 });
	punch.PushBack({ 218, 531, 101, 89 });
	punch.PushBack({ 139, 533, 78, 87 });

	punch.speed = 0.3f;
	punch.loop = false;

	//kick

	kick.PushBack({ 131,630 , 66, 89 });
	kick.PushBack({ 198, 626, 71, 93 });
	kick.PushBack({ 270, 622, 106,97 });
	kick.PushBack({ 198, 626, 71, 93 });
	kick.PushBack({ 131,630 , 66, 89 });
	kick.speed = 0.2f;

	//crouch punch

	Crouch_punch.PushBack({ 368, 839, 71, 66 });
	Crouch_punch.PushBack({ 440, 839, 77, 66 });
	Crouch_punch.PushBack({ 518, 841, 107, 64 });
	Crouch_punch.PushBack({ 518, 841, 107, 64 });
	Crouch_punch.PushBack({ 518, 841, 107, 64 });
	Crouch_punch.PushBack({ 440, 839, 77, 66 });
	Crouch_punch.PushBack({ 368, 839, 71, 66 });
	Crouch_punch.speed = 0.275f;
	Crouch_punch.loop = true;

	//punch neutral jump

	jump_neutral_punch.PushBack({ 1966, 22, 66,89 });
	jump_neutral_punch.PushBack({ 1024, 131,53 ,90 });
	jump_neutral_punch.PushBack({ 1078, 146, 85, 75 });
	jump_neutral_punch.PushBack({ 1164, 144, 87, 77 });

	jump_neutral_punch.speed = 0.4f;
	jump_neutral_punch.loop = false;

	//punch forward jump

	jump_forward_punch.PushBack({ 1252, 147, 53, 74 });
	jump_forward_punch.PushBack({ 1306, 146, 59,75 });
	jump_forward_punch.PushBack({ 1366, 144,83, 77 });
	jump_forward_punch.speed = 0.2f;
	jump_forward_punch.loop = false;

	//punch backward jump
	jump_backward_punch.PushBack({ 1252, 147, 53, 74 });
	jump_backward_punch.PushBack({ 1306, 146, 59,75 });
	jump_backward_punch.PushBack({ 1366, 144,83, 77 });
	jump_backward_punch.speed = 0.2f;
	jump_backward_punch.loop = false;


	//Start functions to reset player
	ResetPlayer();
	Death.Reset();
	DeathCount = 0;
	victorycount = 0;


	return ret;
}



bool ModuleChunLi2::CleanUp()
{
	LOG("Unloading Player textures");

	App->textures->Unload(graphics);

	return true;
}


update_status ModuleChunLi2::PreUpdate()
{

	for (int i = 0; i < MAX_COLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colliders[i] != nullptr) {
			colliders[i]->to_delete = true;
			colliders[i] = nullptr;
		}
	}
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleChunLi2::Update()
{
	Animation* current_animation = &idle;
	p2Qeue<ryu_inputs> inputs;
	ryu_states current_state = ST_UNKNOWN;

	if (position.y == 220) {
		speedX = 1;
		speedY = 1;
	}


	if (death == false) {
		while (external_input(inputs))
		{

			internal_input(inputs);

			state = process_fsm(inputs);


			if (state != current_state)
			{
				lifecondition(current_animation);			


				if (life > 0 && damage_received == false && App->chunli->life > 0) {


					switch (state)
					{
					case ST_IDLE:

						current_animation = &idle;
						crouch.Reset();
						jump_neutral.Reset();
						jump_forward.Reset();
						jump_backwards.Reset();
						punch.Reset();
						jump_neutral_punch.Reset();
						jump_backward_punch.Reset();
						jump_forward_punch.Reset();
						Crouch_punch.Reset();



						break;

					case ST_WALK_FORWARD:

						current_animation = &forward;
						punch.Reset();
						position.x++;
						break;

					case ST_WALK_BACKWARD:

						current_animation = &backward;
						punch.Reset();
						position.x--;

						break;
					case ST_JUMP_NEUTRAL:

						current_animation = &jump_neutral;

						//Speed logic of jump

						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 4.5) {
							position.y -= 8;
						}

						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 4.5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.28) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 4;
							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 4;
							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.28) {
							position.y += 10;
						}

						break;

					case ST_JUMP_FORWARD:


						current_animation = &jump_forward;
						position.x += 3;


						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 5) {
							position.y -= 9;

						}
						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.25) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 5;

							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 7;

							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.25) {
							position.y += 8;
						}

						break;

					case ST_JUMP_BACKWARD:


						current_animation = &jump_backwards;
						position.x -= 3;


						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 5) {
							position.y -= 9;

						}
						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.25) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 5;

							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 7;

							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.25) {
							position.y += 8;
						}
						break;
					case ST_CROUCH:

						current_animation = &crouch;


						break;
					case ST_PUNCH_STANDING:

						current_animation = &punch;




						break;
					case ST_PUNCH_CROUCH:

						current_animation = &Crouch_punch;


						break;
					case ST_PUNCH_NEUTRAL_JUMP:

						current_animation = &jump_neutral_punch;


						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 4.5) {
							position.y -= 8;
						}

						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 4.5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.28) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 3;
							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 3;
							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.28) {
							position.y += 10;
						}


						if (SDL_GetTicks() - punch_neutral_jump_timer > PUNCH_NEUTRAL_JUMP_TIME2) {
							jump_neutral_punch.Reset();
							jump_neutral.current_frame = 9;

						}



						break;
					case ST_PUNCH_FORWARD_JUMP:


						current_animation = &jump_forward_punch;

						position.x += 3;

						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 5) {
							position.y -= 8;

						}
						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.25) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 3;

							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 3;

							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.25) {
							position.y += 8;
						}

						if (SDL_GetTicks() - punch_neutral_jump_timer == PUNCH_NEUTRAL_JUMP_TIME2) {
							jump_forward_punch.Reset();

						}

						break;
					case ST_PUNCH_BACKWARD_JUMP:
						current_animation = &jump_backward_punch;

						position.x -= 3;


						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 5) {
							position.y -= 8;

						}
						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.25) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 3;
							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 3;
							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.25) {
							position.y += 8;
						}

						break;
					case ST_KICK_STANDING:
						current_animation = &kick;

						break;
					case ST_HADOUKEN:


						break;
					}

				}
				current_state = state;

				colliders_and_blit(current_animation);

				return UPDATE_CONTINUE;
			}
		}
	}
}

void ModuleChunLi2::colliders_and_blit(Animation* current_animation) {

	for (int i = 0; i < MAX_COLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colliders[i] != nullptr)
			colliders[i]->to_delete = true;
	}


	SDL_Rect r;
	int max_hitboxes = current_animation->maxcolliders[(int)current_animation->current_frame];

	for (int i = 0; i < max_hitboxes; i++)
	{
		r = current_animation->hitbox[i];

		colliders[i] = App->collision->AddCollider({ position.x + r.x , position.y - r.h - r.y,r.w,r.h }, current_animation->type[i], current_animation->callback[i]);


	}
	r = current_animation->GetCurrentFrame();


	if (position.x < App->chunli->position.x) {
		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}
	if (position.x > App->chunli->position.x) {
		App->render->BlitSym(graphics, position.x, position.y - r.h, &r);
	}
}

void ModuleChunLi2::OnCollision(Collider* c1, Collider* c2) {
	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER && (state == ST_WALK_FORWARD || state == ST_WALK_BACKWARD || state == ST_IDLE))
	{
		speedX = 0;
	}
	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER && (state == ST_JUMP_BACKWARD || state == ST_JUMP_FORWARD || state == ST_JUMP_NEUTRAL)) {
		speedX = -1;

	}
	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER_ATTACK)
	{
		int aux = life;
		life = aux - c2->damage;
		damage_received = true;

	}

}

bool ModuleChunLi2::external_input(p2Qeue<ryu_inputs>& inputs)
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
			case SDLK_DOWN:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_UP:
				up = false;
				break;
			case SDLK_LEFT:
				inputs.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_RIGHT:
				inputs.Push(IN_RIGHT_UP);
				right = false;
				break;
			case SDLK_j:
				return false;
				break;
			case SDLK_k:
				return false;
				break;
			case SDLK_l:
				return false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_j:
				inputs.Push(IN_X);
				break;
			case SDLK_k:
				inputs.Push(IN_C);
				break;
			case SDLK_l:
				inputs.Push(IN_V);
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

void ModuleChunLi2::internal_input(p2Qeue<ryu_inputs>& inputs)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME2)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
			position.y = 220;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME2)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME2)
		{
			inputs.Push(IN_KICK_FINISH);
			kick_timer = 0;
		}
	}

	if (hadouken_timer > 0)
	{
		if (SDL_GetTicks() - hadouken_timer > HADOUKEN_TIME2)
		{
			inputs.Push(IN_HADOUKEN_FINISH);
			hadouken_timer = 0;
		}
	}

	if (punch_neutral_jump_timer > 0)
	{
		if (SDL_GetTicks() - punch_neutral_jump_timer > PUNCH_NEUTRAL_JUMP_TIME2)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_neutral_jump_timer = 0;
		}
	}
}

void ModuleChunLi2::ResetPlayer() {

	life = 1000;
	position.x = 375; 
	if (App->chunli->position.x != 100 || App->chunli->life != 1000) {
		ActiveDeath = 0;
		//App->chunli->ResetPlayer();
		App->UI->time = 99;
		App->UI->Counter1 = 9;
		App->UI->Counter2 = 9;
	}
}

ryu_states ModuleChunLi2::process_fsm(p2Qeue<ryu_inputs>& inputs)
{
	static ryu_states state = ST_IDLE;
	ryu_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE2:
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
			case IN_X: state = ST_PUNCH_NEUTRAL_JUMP; punch_neutral_jump_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_FORWARD_JUMP; punch_neutral_jump_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_BACKWARD_JUMP; punch_neutral_jump_timer = SDL_GetTicks(); break;
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

void ModuleChunLi2::lifecondition(Animation* current_animation) {


	healthbar = life * 0.153;

	if (life < 0) {
		life = 0;
	}


	if (App->chunli->life == 0 && App->UI->victorycount == 0) {

		if (acumvictory < 75) {
			current_animation = &victory;
			acumvictory++;
		}
		if (acumvictory == 75) {
			victory.Reset();
			acumvictory = 0;
		}
	}
	if (App->chunli->life == 0 && App->UI->victorycount == 1) {

		if (acumvictory < 75) {
			current_animation = &victory1;
			acumvictory++;
		}
		if (acumvictory == 75) {
			victory1.Reset();
			acumvictory = 0;
		}
	}


	if (life == 0)
	{
		current_animation = &Death;

		if (position.y < 220) {
			position.y += speedY;
		}

		if (DeathCount == 1) {

			victorycount++;
			App->UI->time = 99;
			App->UI->Counter1 = 9;
			App->UI->Counter2 = 9;
		}
		if (DeathCount < 80)
			DeathCount++;
		if (DeathCount == 80 && ActiveDeath == 0) {
			DeathCount = 0;
			Death.Reset();
			App->render->camera.x = 0;

			ActiveDeath = 1;
			ResetPlayer();

		}

		if (damage_received == true) {


			if (life == 0) {
				damage_received = false;
			}
			if (acumdamage == 1) {


			}
			if (acumdamage >= 0 && acumdamage < 60 && life > 0) {


				current_animation = &damage;
				acumdamage++;
			}

			if (acumdamage == 60 && life > 0) {

				acumdamage = 0;

				damage.Reset();

				damage_received = false;


			}

		}

		//ResetPlayer();
	}

	if (damage_received == true) {


		if (life == 0) {
			damage_received = false;
		}
		if (acumdamage == 1) {


		}
		if (acumdamage >= 0 && acumdamage < 60 && life > 0) {


			current_animation = &damage;
			acumdamage++;
		}

		if (acumdamage == 60 && life > 0) {

			acumdamage = 0;

			damage.Reset();

			damage_received = false;


		}

	}
}