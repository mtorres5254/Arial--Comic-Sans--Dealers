#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleSlowdown.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

ModuleSlowdown::ModuleSlowdown()
{
}

ModuleSlowdown::~ModuleSlowdown()
{}

// Load assets
bool ModuleSlowdown::Start()
{
	return true;
}

// Update: draw background
update_status ModuleSlowdown::PostUpdate()
{
	if (slowing_down)
	{
		UpdateSlowdown();
	}

	if (App->input->keyboard[SDL_SCANCODE_F9] == KEY_DOWN) {
		StartSlowdown(3000, 30);
	}

	return UPDATE_CONTINUE;
}
void ModuleSlowdown::StartSlowdown(int duration, int magnitude)
{
	slowdown_duration = duration;
	slowdown_magnitude = magnitude;
	slowdown_timer = SDL_GetTicks();
	slowing_down = true;
}

void ModuleSlowdown::UpdateSlowdown()
{
	if (SDL_GetTicks() - slowdown_timer < slowdown_duration) {
		SDL_Delay(slowdown_magnitude);
		LOG("DELAY");
	}
	else if (SDL_GetTicks() - slowdown_timer > slowdown_duration) {
		slowing_down = false;
	}
}