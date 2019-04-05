#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

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

	//hadouken animation
	hadouken.PushBack({ 34,1545,70,90 });
	hadouken.PushBack({ 135,1551,85,84 });
	hadouken.PushBack({ 244,1552,90,83 });
	hadouken.PushBack({ 357,1557,106,78 });
	hadouken.speed = 0.085;



}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/ryu.png"); // arcade version
	position.x = 100; //Returns to its original position
	return ret;
}



// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	moving = false;

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &forward;
		position.x += speed;
		moving = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
		position.x -= speed;
		moving = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && moving == false)
	{
		current_animation = &punch;
		PunchCount = 1;
	}
	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN && moving == false)
	{
		current_animation = &hadouken;
		HadoukenCount = 1;
	}

	//Punch

	if (PunchCount < 15 && PunchCount != 0) {
		current_animation = &punch;
		PunchCount++;
	}
	if (PunchCount == 15) {
		current_animation = &punch;
		punch.current_frame = 0;
		PunchCount = 0;
	}

	//Hadouken

	if (HadoukenCount < 55 && HadoukenCount != 0) {
		current_animation = &hadouken;
		HadoukenCount++;
	}
	if (HadoukenCount == 55) {
		current_animation = &hadouken;
		App->particle->AddParticle(App->particle->hadouken, position.x + 55, position.y - 80);
		App->audio->PlayChunk(App->particle->hadouken.sound, 0);
		hadouken.current_frame = 0;
		HadoukenCount = 0;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}