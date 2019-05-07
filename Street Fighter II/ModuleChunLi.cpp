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

	//Forward
	forward.PushBack({ 788, 341, 78,84 });
	forward.PushBack({ 867, 338, 71, 87});
	forward.PushBack({ 939, 337, 63, 87});
	forward.PushBack({ 0, 434, 62, 89});
	forward.PushBack({ 63, 435, 67, 88});
	forward.PushBack({ 131, 436, 76, 87});
	forward.PushBack({ 208, 437, 81, 86});
	forward.PushBack({ 131, 436, 76, 87 });
	forward.PushBack({ 63, 435, 67, 88 });
	forward.PushBack({ 0, 434, 62, 89 });
	forward.PushBack({ 939, 337, 63, 87 });
	forward.PushBack({ 867, 338, 71, 87 });
	forward.speed = 0.2f;
	
	//Backward

	backward.PushBack({ 652,437, 73, 86});
	backward.PushBack({ 726, 434, 63, 89 });
	backward.PushBack({ 790, 433, 60, 90});
	backward.PushBack({ 851, 432, 63, 91});
	backward.PushBack({ 915, 433, 64, 90});
	backward.PushBack({ 0, 531, 64, 89});
	backward.PushBack({ 66, 532, 72, 88});
	backward.PushBack({ 0, 531, 64, 89 });
	backward.PushBack({ 915, 433, 64, 90 });
	backward.PushBack({ 851, 432, 63, 91 });
	backward.PushBack({ 790, 433, 60, 90 });
	backward.PushBack({ 726, 434, 63, 89 });
	backward.speed = 0.15f;

	//Crouch

	crouch.PushBack({ 934,742 , 74, 81});
	crouch.PushBack({ 0, 833, 73, 72});
	crouch.PushBack({ 74, 839, 72, 66});
	crouch.PushBack({ 147, 839, 72, 65});
	crouch.speed = 0.3f;
	crouch.loop = false;

	//Jump 

	jump_neutral.PushBack({ 1756, 1, 47,110 });
	jump_neutral.PushBack({ 1804, 27, 50, 84});
	jump_neutral.PushBack({ 1855, 36, 52, 75});
	jump_neutral.PushBack({ 1908, 46, 57, 65});
	jump_neutral.speed = 0.2f;

	//jump forward
	jump_forward.PushBack({ 925,940,50,84 });
	jump_forward.PushBack({ 1024,30,88,81 });
	jump_forward.PushBack({ 1113,63,121,48 });
	jump_forward.PushBack({ 1235,23,109,88 });
	jump_forward.PushBack({ 1345,7,52,104 });
	jump_forward.PushBack({ 1398,30,110,81 });
	jump_forward.PushBack({ 1509,45,119,66 });
	jump_forward.PushBack({ 1629,35,95,76 });	
	jump_forward.speed = 0.1f;

	//jump backward

	jump_backwards.PushBack({ 925,940,50,84 });
	jump_backwards.PushBack({ 1629,35,95,76 });
	jump_backwards.PushBack({ 1509,45,119,66 });
	jump_backwards.PushBack({ 1345,7,52,104 });
	jump_backwards.PushBack({ 1235,23,109,88 });
	jump_backwards.PushBack({ 1113,63,121,48 });
	jump_backwards.PushBack({ 1024,30,88,81 });
	jump_backwards.speed = 0.1f;
		
	//Punch animation

	punch.PushBack({ 139, 533, 78, 87});
	punch.PushBack({ 218, 531, 101, 89});
	punch.PushBack({ 320, 524, 87, 96});
	punch.PushBack({ 218, 531, 101, 89 });
	punch.PushBack({ 139, 533, 78, 87 });
	punch.speed = 0.2f;

	//kick

	kick.PushBack({ 131,630 , 66, 89});
	kick.PushBack({ 198, 626, 71, 93});
	kick.PushBack({ 270, 622, 106,97 });
	kick.PushBack({ 198, 626, 71, 93 });
	kick.PushBack({ 131,630 , 66, 89 });
	kick.speed = 0.2f;
		
	//crouch punch

	Crouch_punch.PushBack({ 368, 839, 71, 66});
	Crouch_punch.PushBack({ 440, 839, 77, 66});
	Crouch_punch.PushBack({ 518, 841, 107, 64});
	Crouch_punch.PushBack({ 440, 839, 77, 66 });
	Crouch_punch.PushBack({ 368, 839, 71, 66 });
	Crouch_punch.speed = 0.2f;

	//punch neutral jump

	jump_neutral_punch.PushBack({ 1966, 22, 66,89 });
	jump_neutral_punch.PushBack({ 1024, 131,53 ,90 });
	jump_neutral_punch.PushBack({ 1078, 146, 85, 75});
	jump_neutral_punch.PushBack({ 1164, 144, 87, 77});
	jump_neutral_punch.speed = 0.2f;

	//punch forward jump
	
	jump_forward_punch.PushBack({ 1252, 147, 53, 74 });
	jump_forward_punch.PushBack({ 1306, 146, 59,75 });
	jump_forward_punch.PushBack({ 1366, 144,83, 77});
	jump_forward_punch.speed = 0.2f;

	//punch backward jump
	jump_backward_punch.PushBack({ 1252, 147, 53, 74 });
	jump_backward_punch.PushBack({ 1306, 146, 59,75 });
	jump_backward_punch.PushBack({ 1366, 144,83, 77 });
	jump_backward_punch.speed = 0.2f;

}

ModuleChunLi::~ModuleChunLi()
{}

// Load assets
bool ModuleChunLi::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/ChunLi.png"); // arcade version
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
	p2Qeue<chunli_inputs> inputs;
	chunli_states current_state = ST_UNKNOWN;

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
						break;
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

bool ModuleChunLi::external_input(p2Qeue<chunli_inputs>& inputs)
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

void ModuleChunLi::internal_input(p2Qeue<chunli_inputs>& inputs)
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