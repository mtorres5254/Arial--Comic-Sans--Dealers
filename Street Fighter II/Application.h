#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 20

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleLoseScene;
class ModuleChunLi;
class ModuleFadeToBlack;
class ModuleWelcomePage;
class Module;
class ModuleCongratsScreen;
class ModuleAudio;
class ModuleParticles;
class ModuleCollision;
class ModuleUI;
class ModuleFont;
class ModuleSceneDhalsim;
class ModuleRender;
class ModuleChunLi2;
class ModuleCombos;
class ModuleSlowdown;
class ModuleCharacterSelection;
class ModuleContinue;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneDhalsim * scene_dhalsim;
	ModuleChunLi* chunli;
	ModuleFadeToBlack* fade;
	ModuleWelcomePage * welcome_page;
	ModuleCongratsScreen* congrats_screen;
	ModuleAudio* audio;
	ModuleParticles* particle;
	ModuleCollision* collision;
	ModuleUI* UI;
	ModuleLoseScene* lose_scene;
	ModuleChunLi2* chunli2;
	ModuleFont* font;
	ModuleCombos* combo;
	ModuleSlowdown* slow;
	ModuleCharacterSelection* selectionScene;
	ModuleContinue* continu;

	int plyDistance;
	bool intro;

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