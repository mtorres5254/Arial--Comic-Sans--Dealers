#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleChunLi2.h"
#include "ModuleParticles.h"
#include "ModuleChunLi.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "p2Qeue.h"
#include "Application.h"
#include "ModuleSceneDhalsim.h"



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleChunLi::ModuleChunLi()
 {}

ModuleChunLi::~ModuleChunLi()
{}

// Load assets
bool ModuleChunLi::Start()
{
	
	bool ret = true;

	graphics = App->textures->Load("Assets/Images/ChunLi.png"); // arcade version
	
	position.x = 180;
	position.y = 220;

	// idle animation (arcade sprite sheet)


	const int idleCollider = 5;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE idleCollType[idleCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* idleCallBack[idleCollider] = { {this},{this},{this},{this},{this} };

	idle.PushBack1({ 290, 438, 72, 85 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	idle.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	idle.PushBack1({ 436, 436, 72, 87 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	idle.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	idle.speed = 0.1f;

	//Forward

	const int fwdcollider = 5;//Collider num for the idle animation
	SDL_Rect fwdhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE fwdCollType[idleCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* fwdCallback[idleCollider] = { {this},{this},{this},{this},{this} };
	forward.PushBack1({ 652,437, 73, 86 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 726, 434, 63, 89 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 790, 433, 60, 90 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 851, 432, 63, 91 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 915, 433, 64, 90 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 0, 531, 64, 89 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 66, 532, 72, 88 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 0, 531, 64, 89 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 915, 433, 64, 90 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 851, 432, 63, 91 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 790, 433, 60, 90 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.PushBack1({ 726, 434, 63, 89 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback, {});
	forward.speed = 0.2f;
	

	//Backward

	const int bwdcollider = 5;//Collider num for the backwards animation
	SDL_Rect bwdhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE bcwCollType[idleCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* bwdCallback[idleCollider] = { {this},{this},{this},{this},{this} };
	backward.PushBack1({ 652,437, 73, 86 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 726, 434, 63, 89 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 790, 433, 60, 90 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 851, 432, 63, 91 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 915, 433, 64, 90 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 0, 531, 64, 89 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 66, 532, 72, 88 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 0, 531, 64, 89 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 915, 433, 64, 90 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 851, 432, 63, 91 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 790, 433, 60, 90 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.PushBack1({ 726, 434, 63, 89 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback, {});
	backward.speed = 0.15f;

	//Crouch
	const int crhcollider = 5;//Collider num for the crouch animation
	SDL_Rect crhhitbox[crhcollider] = { { 30, 48, 23, 19 },{ 17, 29, 22, 27 },{ 38, 29, 29, 24 },{ 0, 0, 40, 29 },{ 40, 0, 34, 32 } };
	COLLIDER_TYPE crchCollType[crhcollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crhCallback[crhcollider] = { {this},{this},{this},{this},{this} };
	crouch.PushBack1({ 934, 742 , 74, 81 }, { 32, 2 }, crhcollider, crhhitbox, crchCollType, crhCallback, {});
	crouch.PushBack1({ 0, 833, 73, 72 }, { 32, 2 }, crhcollider, crhhitbox, crchCollType, crhCallback, {});
	crouch.PushBack1({ 74, 839, 72, 66 }, { 32, 2 }, crhcollider, crhhitbox, crchCollType, crhCallback, {});
	crouch.PushBack1({ 147, 839, 72, 65 }, { 32, 2 }, crhcollider, crhhitbox, crchCollType, crhCallback, {});
	crouch.speed = 0.3f;
	crouch.loop = false;

	//Jump 

	const int jumpcollider = 5;//Collider num for the idle animation
	SDL_Rect jumphitbox[jumpcollider] = { { 5, 53, 37, 19 },{ 2, 4, 51, 54 },{ 9, 55, 37, 39 },{ 20, 86, 31, 21 },{ 8, 68, 31, 27 } };
	COLLIDER_TYPE jumpCollType[jumpcollider] = { {COLLIDER_PLAYER},{COLLIDER_NONE},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpCallback[jumpcollider] = { {this},{this},{this},{this},{this} };

	jump_neutral.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral.PushBack1({ 1804, 27, 50, 84 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral.PushBack1({ 1855, 36, 52, 75 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral.PushBack1({ 1908, 46, 57, 65 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral.PushBack1({ 1908, 46, 57, 65 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral.PushBack1({ 1908, 46, 57, 65 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral.PushBack1({ 1855, 36, 52, 75 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral.PushBack1({ 1804, 27, 50, 84 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});

	jump_neutral.speed = 0.21f;
	jump_neutral.loop = false;

	//jump forward

	const int jumpfcollider1 = 1;//Collider num for the idle animation
	SDL_Rect jumpfhitbox1[jumpfcollider1] = { { 32, 55, 37, 39 } };
	COLLIDER_TYPE jumpfCollType1[jumpfcollider1] = { {COLLIDER_PLAYER}, };
	Module* jumpfCallback1[jumpfcollider1] = { {this} };


	jump_forward.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward.PushBack1({ 925,940,50,84 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward.PushBack1({ 1024,30,88,81 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1113,63,121,48 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1235,23,109,88 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1345,7,52,104 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1398,30,110,81 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});;
	jump_forward.PushBack1({ 1509,45,119,66 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1629,35,95,76 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward.speed = 0.19f;
	jump_forward.loop = true;

	//jump backward

	jump_backwards.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backwards.PushBack1({ 925,940,50,84 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backwards.PushBack1({ 1629,35,95,76 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_backwards.PushBack1({ 1509,45,119,66 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_backwards.PushBack1({ 1398,30,110,81 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_backwards.PushBack1({ 1345,7,52,104 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_backwards.PushBack1({ 1235,23,109,88 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_backwards.PushBack1({ 1113,63,121,48 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_backwards.PushBack1({ 1024,30,88,81 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_backwards.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backwards.speed = 0.19f;
	jump_backwards.loop = true;


	//Punch animation
	const int punchcollider = 5;//Collider num for the punch animation
	SDL_Rect punchhitbox[punchcollider] = { { 0, 3, 44, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 25, 71, 31, 21 },{ 2, 7, 35, 41 } };
	COLLIDER_TYPE punchCollType[punchcollider] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER } };
	Module* punchCallback[punchcollider] = { { this },{ this },{ this },{ this },{ this } };


	const int punchcollider2 = 6;
	SDL_Rect punchhitbox2[punchcollider2] = { { 0, 3, 44, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 25, 71, 31, 21 },{ 2, 37, 35, 41 }, {63,72,25,27} };
	COLLIDER_TYPE punchCollType2[punchcollider2] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER }, {COLLIDER_PLAYER_ATTACK} };
	Module* punchCallback2[punchcollider2] = { { this },{ this },{ this },{ this },{ this }, {this} };
	punch.PushBack1({ 139, 533, 78, 87 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});
	punch.PushBack1({ 218, 531, 101, 89 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});
	punch.PushBack1({ 320, 524, 87, 96 }, {32,2 }, punchcollider2, punchhitbox2, punchCollType2, punchCallback2, {});
	punch.PushBack1({ 218, 531, 101, 89 }, { 32, 2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});
	punch.PushBack1({ 139, 533, 78, 87 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});

	punch.speed = 0.3f;
	punch.loop = false;

	//kick

	const int kickcollider = 5;//Collider num for the kick animation
	SDL_Rect kickhitbox[kickcollider] = { { 0, 3, 44, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE kickCollType[kickcollider] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER } };
	Module* kickCallback[kickcollider] = { { this },{ this },{ this },{ this },{ this } };


	const int kickcollider2 = 6;
	SDL_Rect kickhitbox2[kickcollider2] = { { 0, 3, 44, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 }, {43,55,67,11} };
	COLLIDER_TYPE kickCollType2[kickcollider2] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER }, {COLLIDER_PLAYER_ATTACK} };
	Module* kickCallback2[kickcollider2] = { { this },{ this },{ this },{ this },{ this }, {this} };

	kick.PushBack1({ 131,630 , 66, 89 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick.PushBack1({ 198, 626, 71, 93 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick.PushBack1({ 270, 622, 106,97 }, { 32,2 }, kickcollider2, kickhitbox2, kickCollType2, kickCallback2, {});
	kick.PushBack1({ 198, 626, 71, 93 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick.PushBack1({ 131,630 , 66, 89 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick.speed = 0.2f;

	//crouch punch
	const int crhpnchcollider = 5;//Collider num for the crouch punch animation
	SDL_Rect crhpnchhitbox[crhpnchcollider] = { { 30, 48, 23, 19 },{ 17, 29, 22, 27 },{ 38, 29, 29, 24 },{ 0, 0, 40, 29 },{ 40, 0, 34, 32 } };
	COLLIDER_TYPE crchpnchCollType[crhpnchcollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crhpnchCallback[crhpnchcollider] = { {this},{this},{this},{this},{this} };
	
	const int crhpnchcollider2 = 6;
	SDL_Rect crhpnchhitbox2[crhpnchcollider2] = { { 30, 48, 23, 19 },{ 17, 29, 22, 27 },{ 38, 29, 29, 24 },{ 0, 0, 40, 29 },{ 40, 0, 34, 32 },{52, 38, 56, 12}};
	COLLIDER_TYPE crchpnchCollType2[crhpnchcollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER}, {COLLIDER_PLAYER_ATTACK} };
	Module* crhpnchCallback2[crhpnchcollider2] = { {this},{this},{this},{this},{this} };
	
	
	Crouch_punch.PushBack1({ 368, 839, 71, 66 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_punch.PushBack1({ 518, 841, 107, 64 }, { 32, 2 }, crhpnchcollider2, crhpnchhitbox2, crchpnchCollType2, crhpnchCallback2, {});
	Crouch_punch.PushBack1({ 440, 839, 77, 66 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_punch.speed = 0.13f;
	Crouch_punch.loop = true;

	//punch neutral jump

	jump_neutral_punch.PushBack({ 1966, 22, 66,89 });
	jump_neutral_punch.PushBack({ 1024, 131,53 ,90 });
	jump_neutral_punch.PushBack({ 1078, 146, 85, 75 });
	jump_neutral_punch.PushBack({ 1164, 144, 87, 77 });

	jump_neutral_punch.speed = 0.4f;
	jump_neutral_punch.loop = false;

	//punch forward jump

	jump_forward_punch.PushBack({ 1252, 147, 53, 74 });
	jump_forward_punch.PushBack({ 1306, 146, 59,75 });
	jump_forward_punch.PushBack({ 1366, 144,83, 77 });
	jump_forward_punch.speed = 0.2f;
	jump_forward_punch.loop = false;

	//punch backward jump
	jump_backward_punch.PushBack({ 1252, 147, 53, 74 });
	jump_backward_punch.PushBack({ 1306, 146, 59,75 });
	jump_backward_punch.PushBack({ 1366, 144,83, 77 });
	jump_backward_punch.speed = 0.2f;
	jump_backward_punch.loop = false;	
	

	//damage animation 

	const int dmgCollider = 5;//Collider num for the idle animation
	SDL_Rect dmgHitbox[dmgCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE dmgCollType[dmgCollider] = { {COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE} };
	Module* dmgCallBack[dmgCollider] = { {this},{this},{this},{this},{this} };

	damage.PushBack1({ 1307,465,72,80 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage.PushBack1({ 1385, 458, 79, 87}, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage.PushBack1({ 1465, 458, 76, 87}, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage.PushBack1({ 1542, 462, 72, 83}, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage.speed = 0.2f;
	
		
	//Start functions to reset player
	ResetPlayer();
	Death.Reset();
	DeathCount = 0;
	victorycount = 0;

	return ret;
}

bool ModuleChunLi::CleanUp()
{
	LOG("Unloading Player textures");

	App->textures->Unload(graphics);

	for (int i = 0; i < MAX_COLLIDERS; i++)
	{
		if (colliders[i] != nullptr) {
			colliders[i]->to_delete = true;
			colliders[i] = nullptr;
		}
	}

	return true;
}


update_status ModuleChunLi::Update()
{
	Animation* current_animation = &idle;
	p2Qeue<ryu_inputs2> inputs;
	ryu_states2 current_state = ST_UNKNOWN2;
	
	positionlimits();
	   

	if (death == false) {
		while (external_input(inputs))
		{

			internal_input(inputs);

			state = process_fsm(inputs);


			if (state != current_state)
			{
				lifecondition(current_animation);

				if (damage_received == true) {


	
					current_animation = &damage;

					//if (SDL_GetTicks() - dmg_timer = DMG_TIME2) {
						//damage_received = false;
					//}

				}
			

				if (life > 0 && damage_received == false && App->chunli2->life > 0) {


					switch (state)
					{
					case ST_IDLE2:
						
						current_animation = &idle;
						crouch.Reset();
						jump_neutral.Reset();
						jump_forward.Reset();
						jump_backwards.Reset();
						punch.Reset();
						jump_neutral_punch.Reset();
						jump_backward_punch.Reset();
						jump_forward_punch.Reset();
						Crouch_punch.Reset();	
						kick.Reset();
						

						break;

					case ST_WALK_FORWARD2:

						current_animation = &forward;
						punch.Reset();
						position.x += speedX;
						break;

					case ST_WALK_BACKWARD2:

						current_animation = &backward;
						punch.Reset();
						position.x -= speedX;

						break;
					case ST_JUMP_NEUTRAL2:						
						
						current_animation = &jump_neutral;											

						//Speed logic of jump

						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2/4.5) {
							position.y -= 8;
						}

						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 4.5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.28) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 4;
							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y +=4;
							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2/1.28) {
							position.y += 10;
						}

						break;

					case ST_JUMP_FORWARD2:

			
						current_animation = &jump_forward;
						position.x += (3 * speedX);

						
						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 5) {
							position.y -= 9;
							
						}
						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.25) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 5;
								
							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 7;
							
							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.25) {
							position.y += 8;
						}

						break;

					case ST_JUMP_BACKWARD2:


						current_animation = &jump_backwards;
						position.x -= (3 * speedX);


						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 5) {
							position.y -= 9;

						}
						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.25) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 5;

							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 7;

							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.25) {
							position.y += 8;
						}
						break;
					case ST_CROUCH2:

						current_animation = &crouch;
						
						
						break;
					case ST_PUNCH_STANDING2:
						
						current_animation = &punch;

		

						
						break;
					case ST_PUNCH_CROUCH2:

						current_animation = &Crouch_punch;
						
						
						break;
					case ST_PUNCH_NEUTRAL_JUMP2:

						current_animation = &jump_neutral_punch;

						
						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 4.5) {
							position.y -= 8;
						}

						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 4.5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.28) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 3;
							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 3;
							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.28) {
							position.y += 10;
						}

						
						if (SDL_GetTicks() - punch_neutral_jump_timer > PUNCH_NEUTRAL_JUMP_TIME2) {
							jump_neutral_punch.Reset();
							jump_neutral.current_frame = 9;			
							
						}
						
						

						break;
					case ST_PUNCH_FORWARD_JUMP2:

					
						current_animation = &jump_forward_punch;

						position.x += 3;

						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 5) {
							position.y -= 8;

						}
						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.25) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 3;

							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 3;

							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.25) {
							position.y += 8;
						}

						if (SDL_GetTicks() - punch_neutral_jump_timer == PUNCH_NEUTRAL_JUMP_TIME2) {
							jump_forward_punch.Reset();
							
						}

						break;
					case ST_PUNCH_BACKWARD_JUMP2:
						current_animation = &jump_backward_punch;

						position.x -= 3;


						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 5) {
							position.y -= 8;

						}
						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.25) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 3;
							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 3;
							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.25) {
							position.y += 8;
						}

						break;
					case ST_KICK_STANDING2:
						current_animation = &kick;

						break;
					case ST_HADOUKEN2:


						break;
					}

				}
				current_state = state;

				colliders_and_blit(current_animation);
				

				return UPDATE_CONTINUE;
			}
		}
	}
}

void ModuleChunLi::positionlimits() {

	if (position.y == 220) {
		speedX = 1;
		speedY = 1;
	}
	if (position.x+32 <= App->scene_dhalsim->background.x - 12) {
		position.x = App->scene_dhalsim->background.x - 12 -32;
	}

	if (position.x-32 >= (App->scene_dhalsim->background.x + App->scene_dhalsim->background.w) - 90) {
		position.x = (App->scene_dhalsim->background.x + App->scene_dhalsim->background.w) - 90 +32;
	}
	
	if (abs(App->chunli2->position.x - position.x) >= SCREEN_WIDTH-20 && position.x<App->chunli2->position.x) {
		App->chunli2->position.x = position.x + SCREEN_WIDTH - 20;
		position.x = App->chunli2->position.x -SCREEN_WIDTH + 20;		
		
	}
	
	if (abs(App->chunli2->position.x - position.x) >= SCREEN_WIDTH - 20 && position.x > App->chunli2->position.x) {

		App->chunli2->position.x = position.x - SCREEN_WIDTH + 20;
		position.x = App->chunli2->position.x + SCREEN_WIDTH - 20;
	}

}

void ModuleChunLi::colliders_and_blit(Animation* current_animation) {

	PivotX = current_animation->pivot[(int)current_animation->current_frame].x;
	PivotY = current_animation->pivot[(int)current_animation->current_frame].y;

	
	for (int i = 0; i < MAX_COLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colliders[i] != nullptr)
			colliders[i]->to_delete = true;
	}


	SDL_Rect r;
	int max_hitboxes = current_animation->maxcolliders[(int)current_animation->current_frame];

	for (int i = 0; i < max_hitboxes; i++)
	{
		r = current_animation->hitbox[i];

		if (position.x < App->chunli2->position.x)
		colliders[i] = App->collision->AddCollider({ position.x + PivotX + r.x , position.y + PivotY- r.h - r.y,r.w,r.h }, current_animation->type[i], current_animation->callback[i]);

		if (position.x > App->chunli2->position.x)
			colliders[i] = App->collision->AddCollider({ position.x - (r.w - PivotX) - r.x , position.y - r.h + PivotY - r.y,r.w,r.h }, current_animation->type[i], current_animation->callback[i]);
	}
	r = current_animation->GetCurrentFrame();


	if (position.x < App->chunli2->position.x) {
		App->render->Blit(graphics, position.x + PivotX, position.y - r.h, &r);
	}
	if (position.x > App->chunli2->position.x) {
		App->render->BlitSym(graphics, position.x - (r.w - PivotX), position.y - r.h, &r);
	}
}

void ModuleChunLi::OnCollision(Collider* c1, Collider* c2) {


	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY && state == ST_IDLE2)
	{		
		if (position.x < App->chunli2->position.x)
			position.x -= 1;

		else if (position.x > App->chunli2->position.x)
			position.x += 1;

	}

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY && state == ST_WALK_FORWARD2)
	{
		if (position.x < App->chunli2->position.x)
			position.x -= 1;

		else if (position.x > App->chunli2->position.x)
			position.x += 1;
	
	}

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY && (state == ST_JUMP_BACKWARD2 || state == ST_JUMP_FORWARD2 || state == ST_JUMP_NEUTRAL2)) {
		//speedX = -1;

	}
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT)
	{
		int aux = life;
		if (!damage_received) {
			life = aux - App->chunli2->dmg;
		}		
		damage_received = true;
		
	}

}

bool ModuleChunLi::external_input(p2Qeue<ryu_inputs2>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;

	//Key up
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_UP) {
		inputs.Push(IN_CROUCH_UP2);
		down = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_UP) {
		up = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_UP) {
		inputs.Push(IN_LEFT_UP2);
		left = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_UP) {
		inputs.Push(IN_RIGHT_UP2);
		right = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_V] == KEY_UP) {
		return false;
	}

	//Key down
	
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_DOWN) {
		up = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_DOWN) {
		down = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_DOWN) {
		left = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_DOWN) {
		right = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_DOWN) {
		inputs.Push(IN_X2);
	}
	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_DOWN) {
		inputs.Push(IN_C2);
	}
	if (App->input->keyboard[SDL_SCANCODE_V] == KEY_DOWN) {
		inputs.Push(IN_V2);
	}



	//Controller
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_UP) { //Teoricament i si deu vol, aixi funcionaria. Esperem que si, recordar provar-ho
		return false;
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_UP) {
		return false;
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_UP) {
		return false;
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_UP) {
		up = false;
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_UP) {
		inputs.Push(IN_CROUCH_UP2);
		down = false;
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_UP) {
		inputs.Push(IN_LEFT_UP2);
		left = false;
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_UP) {
		inputs.Push(IN_RIGHT_UP2);
		right = false;
	}


	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		inputs.Push(IN_X2);
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
		inputs.Push(IN_C2);
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
		inputs.Push(IN_V2);
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_DOWN) {
		up = true;
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_DOWN) {
		down = true;
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN) {
		left = true;
	}
	if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT]                          == KEY_DOWN) {
		right = true;
	}
	

	if (left && right)
		inputs.Push(IN_LEFT_AND_RIGHT2);
	{
		if (left)
			inputs.Push(IN_LEFT_DOWN2);
		if (right)
			inputs.Push(IN_RIGHT_DOWN2);
	}

	if (up && down)
		inputs.Push(IN_JUMP_AND_CROUCH2);
	else
	{
		if (down)
			inputs.Push(IN_CROUCH_DOWN2);
		if (up)
			inputs.Push(IN_JUMP2);
	}
	return true;
}

void ModuleChunLi::internal_input(p2Qeue<ryu_inputs2>& inputs)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME2)
		{
			inputs.Push(IN_JUMP_FINISH2);
			jump_timer = 0;
			position.y = 220;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME2)
		{
			inputs.Push(IN_PUNCH_FINISH2);
			punch_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME2)
		{
			inputs.Push(IN_KICK_FINISH2);
			kick_timer = 0;
		}
	}

	if (hadouken_timer > 0)
	{
		if (SDL_GetTicks() - hadouken_timer > HADOUKEN_TIME2)
		{
			inputs.Push(IN_HADOUKEN_FINISH2);
			hadouken_timer = 0;
		}
	}

	if (punch_neutral_jump_timer > 0)
	{
		if (SDL_GetTicks() - punch_neutral_jump_timer > PUNCH_NEUTRAL_JUMP_TIME2)
		{
			inputs.Push(IN_PUNCH_FINISH2);
			punch_neutral_jump_timer = 0;
		}
	}
}

void ModuleChunLi::ResetPlayer() {

	life = 1000;
	position.x = 180; //Returns to its original position
	if (App->chunli2->position.x != 300 || App->chunli2->life != 1000) {
		ActiveDeath = 0;
		App->chunli2->ResetPlayer();
		App->UI->time = 99;
		App->UI->Counter1 = 9;
		App->UI->Counter2 = 9;
		App->scene_dhalsim->newRound = true;
	}
}

ryu_states2 ModuleChunLi:: process_fsm(p2Qeue<ryu_inputs2>& inputs)
{
	static ryu_states2 state = ST_IDLE2;
	ryu_inputs2 last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE2:
		{
			switch (last_input)
			{
			case IN_RIGHT_DOWN2: state = ST_WALK_FORWARD2; break;
			case IN_LEFT_DOWN2: state = ST_WALK_BACKWARD2; break;
			case IN_JUMP2: state = ST_JUMP_NEUTRAL2; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; break;
			case IN_X2: state = ST_PUNCH_STANDING2; punch_timer = SDL_GetTicks();  break;
			case IN_C2: state = ST_KICK_STANDING2; kick_timer = SDL_GetTicks(); break;
			case IN_V2: state = ST_HADOUKEN2; hadouken_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_WALK_FORWARD2:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP2: state = ST_IDLE2; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE2; break;
			case IN_JUMP2: state = ST_JUMP_FORWARD2; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; break;
			case IN_X2: state = ST_PUNCH_STANDING2; punch_timer = SDL_GetTicks();  break;
			case IN_C2: state = ST_KICK_STANDING2; kick_timer = SDL_GetTicks(); break;
			case IN_V2: state = ST_HADOUKEN2; hadouken_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_WALK_BACKWARD2:
		{
			switch (last_input)
			{
			case IN_LEFT_UP2: state = ST_IDLE2; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE2; break;
			case IN_JUMP2: state = ST_JUMP_BACKWARD2; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; break;
			case IN_X2: state = ST_PUNCH_STANDING2; punch_timer = SDL_GetTicks();  break;
			case IN_C2: state = ST_KICK_STANDING2; kick_timer = SDL_GetTicks(); break;
			case IN_V2: state = ST_HADOUKEN2; hadouken_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL2:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_NEUTRAL_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_FORWARD2:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_FORWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_BACKWARD2:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_BACKWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_JUMP_NEUTRAL2; break;
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_JUMP_FORWARD2; break;
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			}
		}
		break;

		case ST_PUNCH_BACKWARD_JUMP2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_JUMP_BACKWARD2; break;
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			}
		}
		break;

		case ST_PUNCH_STANDING2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE2; break;
			}
		}
		break;

		case ST_CROUCH2:
		{
			switch (last_input)
			{
			case IN_CROUCH_UP2: state = ST_IDLE2; break;
			case IN_JUMP_AND_CROUCH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_CROUCH2; punch_timer = SDL_GetTicks(); break;
			}
		}
		break;
		case ST_PUNCH_CROUCH2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
					state = ST_CROUCH2;
				else
					state = ST_IDLE2;
				break;
			}
		}
		break;
		case ST_KICK_STANDING2:
		{
			switch (last_input)
			{
			case IN_KICK_FINISH2: state = ST_IDLE2; break;
			}
		}
		break;
		case ST_HADOUKEN2:
		{
			switch (last_input)
			{
			case IN_HADOUKEN_FINISH2: state = ST_IDLE2; break;
			}
			break;
		}

		}
	}
	return state;
}

void ModuleChunLi::lifecondition(Animation* current_animation) {


	healthbar = life * 0.153;
	   
	if (life < 0) {
		life = 0;
	}


	if (App->chunli2->life == 0 && App->UI->victorycount == 0) {

		if (acumvictory < 75) {
			current_animation = &victory;
			acumvictory++;
		}
		if (acumvictory == 75) {
			victory.Reset();
			acumvictory = 0;
		}
	}
	if (App->chunli2->life == 0 && App->UI->victorycount == 1) {

		if (acumvictory < 75) {
			current_animation = &victory1;
			acumvictory++;
		}
		if (acumvictory == 75) {
			victory1.Reset();
			acumvictory = 0;
		}
	}


	if (life == 0)
	{
		current_animation = &Death;

		if (position.y < 220) {
			position.y += speedY;
		}

		if (DeathCount == 1) {

			victorycount++;
			App->UI->time = 99;
			App->UI->Counter1 = 9;
			App->UI->Counter2 = 9;
		}
		if (DeathCount < 80)
			DeathCount++;
		if (DeathCount == 80 && ActiveDeath == 0) {
			DeathCount = 0;
			Death.Reset();
			App->render->camera.x = 0;

			ActiveDeath = 1;
			ResetPlayer();

		}

		if (damage_received == true) {

			current_animation = &damage;
			if (life == 0) {
				damage_received = false;
			}
		

		}

		//ResetPlayer();
	}

	if (damage_received == true) {


		if (life == 0) {
			damage_received = false;
		}
		if (acumdamage == 1) {


		}
		if (acumdamage >= 0 && acumdamage < 60 && life > 0) {


			current_animation = &damage;
			acumdamage++;
		}

		if (acumdamage == 60 && life > 0) {

			acumdamage = 0;

			damage.Reset();

			damage_received = false;


		}

	}
}