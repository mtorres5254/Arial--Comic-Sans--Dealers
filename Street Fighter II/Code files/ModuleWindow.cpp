#include "Header files/Globals.h"
#include "Header files/Application.h"
#include "Header files/ModuleWindow.h"
#include "SDL/include/SDL.h"


bool ModuleWindow::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG("%s", SDL_GetError());
	}
	Window = SDL_CreateWindow("ApeteProject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, OPENGL);
	return true;
}
bool ModuleWindow::CleanUp() {
	SDL_DestroyWindow(Window);
	SDL_Quit();
	return true;
}


