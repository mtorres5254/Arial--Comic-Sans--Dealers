#include "Header files/Globals.h"
#include "Header files/Application.h"
#include "Header files/ModuleWindow.h"
#include "Header files/ModuleRenderer.h"

#include "SDL/include/SDL.h"

bool ModuleRenderer::Init() {
	render = SDL_CreateRenderer(App->win->Window, -1, VSYNC);
	return true;
}
update_status ModuleRenderer::PreUpdate() {
	SDL_RenderClear(render);
	return update_status::UPDATE_CONTINUE;
}
update_status ModuleRenderer::PostUpdate() {
	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	SDL_RenderPresent(render);
	return update_status::UPDATE_CONTINUE;
}
bool ModuleRenderer::CleanUp() {
	SDL_DestroyRenderer(render);

	return true;
}
