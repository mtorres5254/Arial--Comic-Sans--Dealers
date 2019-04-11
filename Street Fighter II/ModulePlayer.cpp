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
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;

	// walk backward animation
	backward.PushBack({ 542,127,61,91 });
	backward.PushBack({ 628,127,60,91 });
	backward.PushBack({ 713,127,58,91 });
	backward.PushBack({ 797,127,58,91 });
	backward.PushBack({ 883,127,57,91 });
	backward.PushBack({ 974,127,57,91 });
	backward.speed = 0.05f;

	//punch animation
	punch.PushBack({ 19,272,64,91 });
	punch.PushBack({ 108,272,91,91 });
	punch.PushBack({ 19,272,64,91 });
	punch.speed = 0.2f;

	//kick animation

	kick.PushBack({ 607,269,59,94 });
	kick.PushBack({ 689,267,66,92 });
	kick.PushBack({ 777,265,114,94 });
	kick.PushBack({ 689,267,66,92 });
	kick.speed = 0.2f;

	//hadouken animation
	hadouken.PushBack({ 34,1545,70,90 });
	hadouken.PushBack({ 135,1551,85,84 });
	hadouken.PushBack({ 244,1552,90,83 });
	hadouken.PushBack({ 357,1557,106,78 });
	hadouken.speed = 0.085;

	//crouch animation
	crouch.PushBack({ 32,1212,53,83 });
	crouch.PushBack({115 ,1227,57,69 });
	crouch.PushBack({ 197,1235, 61,61 });
	crouch.speed = 0.1f;
	crouch.loop = false;

	//jump animation
	jump_neutral.PushBack({ 17,847,55,85 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 177,805,49,89 });
	jump_neutral.PushBack({ 251,798,54,77 });
	jump_neutral.PushBack({ 327,813,48,70 });
	jump_neutral.PushBack({ 397,810,48,89 });
	jump_neutral.PushBack({ 464,819,55,109 });
	jump_neutral.speed = 0.1f;
	
	

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
	colliderplayer = App->collision->AddCollider({ position.x,position.y,60,-90 }, COLLIDER_PLAYER);
	colliderplayer->callback = this;
	

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
	
	
	/*
	moving = false;
	movef = false;
	moveb = false;

	//Punch

	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
	{
		//current_animation = &punch;
		PunchCount = 1;
	}

	if (PunchCount < 15 && PunchCount != 0) {
		current_animation = &punch;
		PunchCount++;
	}

	if (PunchCount == 15) {
		current_animation = &punch;
		punch.current_frame = 0;
		PunchCount = 0;
	}

	//Kick

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN)
	{
		KickCount = 1;
	}

	if (KickCount < 25 && KickCount != 0) {
		current_animation = &kick;
		KickCount++;
	}

	if (KickCount == 25) {
		current_animation = &kick;
		kick.current_frame = 0;
		KickCount = 0;
	}

	//Hadouken

	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN){	
		
		current_animation = &hadouken;
		HadoukenCount = 1;
	}

	// Movement
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && (PunchCount == 0 && HadoukenCount == 0 && KickCount==0))
	{
		movef = true;
	}
	if(movef == true)
	{
		current_animation = &forward;
		position.x += speed;
		moving = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && (PunchCount == 0 && HadoukenCount==0 && KickCount == 0 ))
	{
		moveb = true;
	}
	if (moveb == true)
	{
		current_animation = &backward;
		position.x -= speed;
		moving = true;
	}
	
	//Hadouken

	if (HadoukenCount < 55 && HadoukenCount != 0) {
		
		current_animation = &hadouken;
		HadoukenCount++;
	}
	if (HadoukenCount == 55) {
		current_animation = &hadouken;
		App->particle->AddParticle(App->particle->hadouken, position.x + 55, position.y - 80, COLLIDER_PLAYER_SHOT);
		App->audio->PlayChunk(App->particle->hadouken.sound, 0);
		hadouken.current_frame = 0;
		HadoukenCount = 0;
	}*/

	Animation* current_animation = &idle;
	p2Qeue<ryu_inputs> inputs;
	ryu_states current_state = ST_UNKNOWN;
	
	int speed = 1;

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
			
				break;
			case ST_WALK_FORWARD:
				current_animation = &forward;
				position.x += speed;
			
				break;
			case ST_WALK_BACKWARD:
				current_animation = &backward;
				position.x -= speed;
				
				break;
			case ST_JUMP_NEUTRAL:
				current_animation = &jump_neutral;				
				
				break;
			case ST_JUMP_FORWARD:
			
				break;
			case ST_JUMP_BACKWARD:
				
				break;
			case ST_CROUCH:
				current_animation = &crouch;
				break;
			case ST_PUNCH_CROUCH:
				
				break;
			case ST_PUNCH_STANDING:
				current_animation = &punch;
			
				break;
			case ST_PUNCH_NEUTRAL_JUMP:
				
				break;
			case ST_PUNCH_FORWARD_JUMP:
				
				break;
			case ST_PUNCH_BACKWARD_JUMP:
				
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
		moveb = false;
		movef = false;
		LOG("colision detected");
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
			case SDLK_p:
				return false;
				break;
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
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_p:
				inputs.Push(IN_X);
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
}
