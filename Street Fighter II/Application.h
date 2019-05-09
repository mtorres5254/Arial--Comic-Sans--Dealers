#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 20

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneKen;
class ModuleSceneHonda;
class ModuleLoseScene;
class ModulePlayer;
class ModulePlayer2;
class ModuleChunLi;
class ModuleFadeToBlack;
class ModuleWelcomePage;
class Module;
class ModuleCongratsScreen;
class ModuleAudio;
class ModuleParticles;
class ModuleCollision;
class ModuleUI;
class ModuleSceneRyu;
class ModuleFont;
class ModuleSceneDhalsim;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneKen* scene_ken;
	ModuleSceneRyu* scene_ryu;
	ModuleSceneDhalsim * scene_dhalsim;
	ModuleSceneHonda* scene_honda;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleChunLi* chunli;
	ModuleFadeToBlack* fade;
	ModuleWelcomePage * welcome_page;
	ModuleCongratsScreen* congrats_screen;
	ModuleAudio* audio;
	ModuleParticles* particle;
	ModuleCollision* collision;
	ModuleUI* UI;
	ModuleLoseScene* lose_scene;
	
	ModuleFont* font;

	int plyDistance;

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