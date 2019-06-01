#ifndef _MODULESCORE_H
#define _MODULESCORE_H

#include "Module.h"
#include "ModuleFont.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL_mixer/include/SDL_mixer.h"
class ModuleScore : public Module
{
public:

	ModuleScore();
	~ModuleScore();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	int PointsP1, PointsP2;

}

#endif 