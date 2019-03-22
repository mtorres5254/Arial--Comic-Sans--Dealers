#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Header files/Globals.h"
#include "Header files/Module.h"

#define NUM_MODULES 2

class ModuleWindow;
class ModuleRenderer;

class Application
{
public:
	
	Module* modules[NUM_MODULES];
	ModuleWindow* win;
	ModuleRenderer* rend;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

extern Application* App;

#endif 