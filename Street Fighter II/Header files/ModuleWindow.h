#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Header files/Module.h"
#include "SDL/include/SDL.h"

class ModuleWindow : public Module {
public:
	SDL_Window* Window = nullptr;

	bool Init() override;
	bool CleanUp() override;

};

#endif