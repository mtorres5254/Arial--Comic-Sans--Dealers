#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Header files/Module.h"
#include "SDL/include/SDL.h"

class ModuleRenderer : public Module {
public:
	SDL_Renderer* render = nullptr;
	
	bool Init() override;
	update_status PreUpdate() override;
	update_status PostUpdate() override;
	bool CleanUp() override;
};

#endif