#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneKen.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleSceneHonda.h"
#include "ModuleAudio.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleLoseScene.h"

ModuleLoseScene::ModuleLoseScene() {

}

ModuleLoseScene::~ModuleLoseScene() {

}

bool ModuleLoseScene::Start() {

	return true;
}

bool ModuleLoseScene::CleanUp() {

	return true;
}

update_status ModuleLoseScene::Update() {

	return UPDATE_CONTINUE;
}