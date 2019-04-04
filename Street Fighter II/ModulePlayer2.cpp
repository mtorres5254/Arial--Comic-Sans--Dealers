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
	position.x = 150;
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
	graphics = App->textures->Load("Assets/ryu2.png"); // arcade version
	position.x = 100; //Returns to its original position
	return ret;
}



// Update: draw background
update_status ModulePlayer2::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &forward;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN)
	{
		App->particle->AddParticle(App->particle->hadouken, position.x, position.y - 100);

	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}