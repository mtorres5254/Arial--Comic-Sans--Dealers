#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleChunLi.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleChunLi::ModuleChunLi()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 290, 438, 72, 85 });
	idle.PushBack({ 363, 437, 72, 86 });
	idle.PushBack({ 436, 436, 72, 87 });
	idle.PushBack({ 363, 437, 72, 86 });
	idle.speed = 0.1f;
}

ModuleChunLi::~ModuleChunLi()
{}

// Load assets
bool ModuleChunLi::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/Chun-Li1.png"); // arcade version
	position.x = 100; //Returns to its original position

	//Sounds
	

	//Start functions to reset player
	ResetPlayer();
	Death.Reset();
	DeathCount = 0;
	victorycount = 0;

	//Add a collider to the player
	colliderchunli = App->collision->AddCollider({ position.x + 7 ,position.y - 90,45,90 }, COLLIDER_PLAYER, App->player);

	return ret;
}

bool ModuleChunLi::CleanUp()
{
	LOG("Unloading Player textures");

	App->textures->Unload(graphics);

	return true;
}



// Update: draw background
update_status ModuleChunLi::Update()
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

				healthbar = life * 0.153;


				if (life < 0) {
					life = 0;
				}

				if (App->player2->life == 0 && App->UI->victorycount == 0) {

					if (acumvictory < 75) {
						current_animation = &victory;
						acumvictory++;
					}
					if (acumvictory == 75) {
						victory.Reset();
						acumvictory = 0;
					}
				}
				if (App->player2->life == 0 && App->UI->victorycount == 1) {

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

				else  if (life > 0 && damage_received == false && App->player2->life > 0) {


					switch (state)
					{
					case ST_IDLE:
						current_animation = &idle;

						break;

					case ST_WALK_FORWARD:

						current_animation = &forward;

						break;

					case ST_WALK_BACKWARD:

						current_animation = &backward;

						break;
					case ST_JUMP_NEUTRAL:


						current_animation = &jump_neutral;


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

					case ST_PUNCH_CROUCH:
						current_animation = &Crouch_punch;

						break;
					case ST_PUNCH_NEUTRAL_JUMP:
						current_animation = &jump_neutral_punch;

						break;
					case ST_PUNCH_FORWARD_JUMP:


						current_animation = &jump_forward_punch;

						break;
					case ST_PUNCH_BACKWARD_JUMP:
						current_animation = &jump_backward_punch;

						break;
					case ST_KICK_STANDING:
						current_animation = &kick;

						break;
					case ST_HADOUKEN:


						break;
					}

				}
				current_state = state;


				// Draw everything --------------------------------------

				SDL_Rect r = current_animation->GetCurrentFrame();
				if (position.x < App->player2->position.x) {
					App->render->Blit(graphics, position.x, position.y - r.h, &r);
				}
				if (position.x > App->player2->position.x) {
					App->render->BlitSym(graphics, position.x, position.y - r.h, &r);
				}
				//Update collider position to player position


				return UPDATE_CONTINUE;
			}
		}
	}
}



void ModuleChunLi::OnCollision(Collider* c1, Collider* c2) {
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY && (state == ST_WALK_FORWARD || state == ST_WALK_BACKWARD || state == ST_IDLE))
	{
		
	}
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY && (state == ST_JUMP_BACKWARD || state == ST_JUMP_FORWARD || state == ST_JUMP_NEUTRAL)) {
		speedX = -1;

	}
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT)
	{
		int aux = life;
		life = aux - c2->damage;
		damage_received = true;

	}

}

bool ModuleChunLi::external_input(p2Qeue<ryu_inputs>& inputs)
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
			case SDLK_x:
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
			case SDLK_x:
				inputs.Push(IN_X);
				break;
			case SDLK_c:
				inputs.Push(IN_C);
				break;
			case SDLK_v:
				inputs.Push(IN_V);
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

void ModuleChunLi::internal_input(p2Qeue<ryu_inputs>& inputs)
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

void ModuleChunLi::ResetPlayer() {

	life = 1000;
	position.x = 100; //Returns to its original position
	if (App->player2->position.x != 300 || App->player2->life != 1000) {
		ActiveDeath = 0;
		App->player2->ResetPlayer();
		App->UI->time = 99;
		App->UI->Counter1 = 9;
		App->UI->Counter2 = 9;
	}
}