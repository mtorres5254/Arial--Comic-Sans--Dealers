#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 15

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneKen;
class ModuleSceneHonda;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleWelcomePage;
class Module;
class ModuleCongratsScreen;
class ModuleAudio;
class ModuleParticles;
class ModuleCollision;
class ModuleUI;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneKen* scene_ken;
	ModuleSceneHonda* scene_honda;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleWelcomePage * welcome_page;
	ModuleCongratsScreen* congrats_screen;
	ModuleAudio* audio;
	ModuleParticles* particle;
	ModuleCollision* collision;
	ModuleUI* UI;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__