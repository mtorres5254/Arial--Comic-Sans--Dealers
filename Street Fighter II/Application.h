#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

<<<<<<< HEAD
#define NUM_MODULES 19
=======
#define NUM_MODULES 17
>>>>>>> parent of 9429e03... Working on win scene

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneKen;
class ModuleSceneHonda;
class ModuleLoseScene;
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
class ModuleSceneRyu;
<<<<<<< HEAD
class ModuleWinScene;
class ModuleFont;

=======
>>>>>>> parent of 9429e03... Working on win scene

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
	ModuleLoseScene* lose_scene;
	ModuleSceneRyu* scene_ryu;
<<<<<<< HEAD
	ModuleWinScene* win_scene;
	ModuleFont* font;

=======
>>>>>>> parent of 9429e03... Working on win scene

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