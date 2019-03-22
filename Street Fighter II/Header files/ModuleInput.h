#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Header files/Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"

typedef unsigned char Uint8;

class ModuleInput : public Module
{
public:
	SDL_Event event;


	bool Init();
	update_status Update();
	bool CleanUp();
};

#endif // __ModuleInput_H__
