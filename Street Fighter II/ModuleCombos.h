#ifndef _MODULECOMBOS_H
#define _MODULECOMBOS_H

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"

#define LIGHTNINGKICK 35

class ModuleCombos : public Module
{
public:
	ModuleCombos();
	~ModuleCombos();
	
	bool Init();
	update_status Update();
	bool CleanUp();

	bool CheckPunchP1();
	bool CheckPunchP2();

	bool CheckLightingKickP1();
	bool CheckLightingKickP2();

public:
	int actual_frameP1LK = 0;
	int actual_frameP2LK = 0;

	int lightimgKickCount = 0;
	int lightimgKickCount2 = 0;
};

#endif // !_MODULECOMBOS_H
