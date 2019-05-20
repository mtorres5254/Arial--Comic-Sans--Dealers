#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleChunLi.h"
#include "ModuleParticles.h"
#include "ModuleChunLi2.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "p2Qeue.h"
#include "Application.h"
#include "ModuleSceneDhalsim.h"
#include "ModuleCombos.h"



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleChunLi2::ModuleChunLi2()
{}

ModuleChunLi2::~ModuleChunLi2()
{}

// Load assets
bool ModuleChunLi2::Start()
{

	bool ret = true;

	graphics = App->textures->Load("Assets/Images/ChunLi2.png"); // arcade version
	shadow = App->textures->Load("Assets/Images/shadow.png");
	position.x = 395;
	position.y = 220;

	
	// idle animation (arcade sprite sheet)


	const int idleCollider = 5;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 },{ 9,4,51,54 },{ 1,3,45,33 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	Module* idleCallBack[idleCollider] = { { this },{ this },{ this },{ this },{ this } };

	idle.PushBack1({ 290, 438, 72, 85 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	idle.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	idle.PushBack1({ 436, 436, 72, 87 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	idle.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	idle.speed = 0.1f;

	//Forward

	const int fwdcollider = 5;//Collider num for the idle animation
	SDL_Rect fwdhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE fwdCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	Module* fwdCallback[idleCollider] = { { this },{ this },{ this },{ this },{ this } };
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
	forward.speed = 0.15f;


	//Backward

	const int bwdcollider = 5;//Collider num for the idle animation
	SDL_Rect bwdhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE bcwCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	Module* bwdCallback[idleCollider] = { { this },{ this },{ this },{ this },{ this } };
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
	backward.speed = 0.2f;

	//Crouch

	const int crhcollider = 5;//Collider num for the crouch animation
	SDL_Rect crhhitbox[crhcollider] = { { 30, 48, 23, 19 },{ 17, 29, 22, 27 },{ 38, 29, 29, 24 },{ 0, 0, 40, 29 },{ 40, 0, 34, 32 } };
	COLLIDER_TYPE crchCollType[crhcollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE jumpCollType[jumpcollider] = { {COLLIDER_ENEMY},{COLLIDER_NONE},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE jumpfCollType1[jumpfcollider1] = { {COLLIDER_ENEMY}, };
	Module* jumpfCallback1[jumpfcollider1] = { {this} };


	jump_forward.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward.PushBack1({ 925,940,50,84 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward.PushBack1({ 1024,30,88,81 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1113,63,121,48 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1235,23,109,88 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1345,7,52,104 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
	jump_forward.PushBack1({ 1398,30,110,81 }, { 32, 25 }, jumpfcollider1, jumpfhitbox1, jumpfCollType1, jumpfCallback1, {});
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
	COLLIDER_TYPE punchCollType[punchcollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	Module* punchCallback[punchcollider] = { { this },{ this },{ this },{ this },{ this } };


	const int punchcollider2 = 6;
	SDL_Rect punchhitbox2[punchcollider2] = { { 0, 3, 44, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 25, 71, 31, 21 },{ 2, 37, 35, 41 }, {63,72,25,27} };
	COLLIDER_TYPE punchCollType2[punchcollider2] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY }, {COLLIDER_ENEMY_SHOT} };
	Module* punchCallback2[punchcollider2] = { { this },{ this },{ this },{ this },{ this }, {this} };
	punch.PushBack1({ 139, 533, 78, 87 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});
	punch.PushBack1({ 218, 531, 101, 89 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});
	punch.PushBack1({ 320, 524, 87, 96 }, { 32,2 }, punchcollider2, punchhitbox2, punchCollType2, punchCallback2, 2800);
	punch.PushBack1({ 218, 531, 101, 89 }, { 32, 2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});
	punch.PushBack1({ 139, 533, 78, 87 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});

	punch.speed = 0.3f;
	punch.loop = false;

	//kick

	const int kickcollider = 5;//Collider num for the idle animation
	SDL_Rect kickhitbox[kickcollider] = { { 0, 3, 44, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE kickCollType[kickcollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	Module* kickCallback[kickcollider] = { { this },{ this },{ this },{ this },{ this }};


	const int kickcollider2 = 6;
	SDL_Rect kickhitbox2[kickcollider2] = { { 0, 3, 44, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 }, {43,72,67,11} };
	COLLIDER_TYPE kickCollType2[kickcollider2] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY }, {COLLIDER_ENEMY_SHOT} };
	Module* kickCallback2[kickcollider2] = { { this },{ this },{ this },{ this },{ this }, {this} };

	kick.PushBack1({ 131,630 , 66, 89 }, { 32,2 },kickcollider, kickhitbox,kickCollType,kickCallback, {});
	kick.PushBack1({ 198, 626, 71, 93 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick.PushBack1({ 270, 622, 106,97 }, { 32,20 }, kickcollider2, kickhitbox2, kickCollType2, kickCallback2, 2800);
	kick.PushBack1({ 198, 626, 71, 93 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick.PushBack1({ 131,630 , 66, 89 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick.speed = 0.2f;

	//crouch punch

	const int crhpnchcollider = 5;//Collider num for the crouch punch animation
	SDL_Rect crhpnchhitbox[crhpnchcollider] = { { 30, 48, 23, 19 },{ 17, 29, 22, 27 },{ 38, 29, 29, 24 },{ 0, 0, 40, 29 },{ 40, 0, 34, 32 } };
	COLLIDER_TYPE crchpnchCollType[crhpnchcollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* crhpnchCallback[crhpnchcollider] = { {this},{this},{this},{this},{this} };

	const int crhpnchcollider2 = 6;
	SDL_Rect crhpnchhitbox2[crhpnchcollider2] = { { 30, 48, 23, 19 },{ 17, 29, 22, 27 },{ 38, 29, 29, 24 },{ 0, 0, 40, 29 },{ 40, 0, 34, 32 },{52, 38, 56, 12} };
	COLLIDER_TYPE crchpnchCollType2[crhpnchcollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY}, {COLLIDER_ENEMY_SHOT} };
	Module* crhpnchCallback2[crhpnchcollider2] = { {this},{this},{this},{this},{this} };


	Crouch_punch.PushBack1({ 368, 839, 71, 66 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_punch.PushBack1({ 518, 841, 107, 64 }, { 32, 2 }, crhpnchcollider2, crhpnchhitbox2, crchpnchCollType2, crhpnchCallback2, {2300});
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


	//Lightning kick
	const int lkcollider = 9;//Collider num for the idle animation
	SDL_Rect lkhitbox[lkcollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} , {91,66,31,15}, {57,19,71,39}, {90,42,51,25} , {48,4,83,29} };
	COLLIDER_TYPE lkCollType[lkcollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY}, {COLLIDER_ENEMY_SHOT }, {COLLIDER_ENEMY_SHOT }, {COLLIDER_ENEMY_SHOT }, {COLLIDER_ENEMY_SHOT } };
	Module* lkCallback[lkcollider] = { {this},{this},{this},{this},{this},{this},{this},{this},{this} };


	SDL_Rect lkhitbox1[lkcollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33}, {57,19,71,39} };
	SDL_Rect lkhitbox2[lkcollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33}, {90,42,51,25} };
	SDL_Rect lkhitbox3[lkcollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33}, {48,4,83,29} };



	//LightningKick.PushBack1({ 1475, 225, 61 , 100 }, { 32, 2 }, {}, {}, {}, {}, {});
	LightningKick.PushBack1({ 1537, 226, 107, 99 }, { 32, 2 }, lkcollider, lkhitbox, lkCollType, lkCallback, 2400);
	LightningKick.PushBack1({ 1645,222 , 123, 103 }, { 32, 2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	LightningKick.PushBack1({ 1769, 230, 119, 95 }, { 32, 2 }, lkcollider, lkhitbox, lkCollType, lkCallback, 2400);
	LightningKick.PushBack1({ 1889, 230, 136,95 }, { 32, 2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	LightningKick.PushBack1({ 1025, 355, 120, 93 }, { 32, 2 }, lkcollider, lkhitbox, lkCollType, lkCallback, 2400);
	LightningKick.PushBack1({ 1146, 353, 152, 95 }, { 32, 2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	LightningKick.PushBack1({ 1300, 355, 101, 93 }, { 32, 2 }, lkcollider, lkhitbox, lkCollType, lkCallback, 2400);
	LightningKick.speed = 0.3f;
	LightningKick.loop = true;

	//Start functions to reset player
	ResetPlayer();
	Death.Reset();
	DeathCount = 0;
	victorycount = 0;


	return ret;
}



bool ModuleChunLi2::CleanUp()
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


update_status ModuleChunLi2::Update()
{
	Animation* current_animation = &idle;
	p2Qeue<chunli_inputs> inputs;
	chunli_states current_state = ST_UNKNOWN;

	positionlimits();


	if (death == false) {
		while (external_input(inputs))
		{

			internal_input(inputs);

			state = process_fsm(inputs);


			if (state != current_state)
			{
				lifecondition(current_animation);			


				if (life > 0 && damage_received == false && App->chunli->life > 0 ) {


					switch (state)
					{
					case ST_IDLE:

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
						LightningKick.Reset();
						move = true;


						break;

					case ST_WALK_FORWARD:

						current_animation = &forward;
						punch.Reset();

						if(move)
						position.x += speedX;
						break;

					case ST_WALK_BACKWARD:

						current_animation = &backward;
						punch.Reset();

						if(move)
						position.x -= speedX;

						break;
					case ST_JUMP_NEUTRAL:

						current_animation = &jump_neutral;

						//Speed logic of jump

						if (SDL_GetTicks() - jump_timer <= JUMP_TIME2 / 4.5) {
							position.y -= 8;
						}

						if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 4.5 && SDL_GetTicks() - jump_timer < JUMP_TIME2 / 1.28) {
							if (SDL_GetTicks() - jump_timer < JUMP_TIME2 / 2) {
								position.y -= 4;
							}

							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 4;
							}
						}

						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.28) {
							position.y += 10;
						}

						break;

					case ST_JUMP_FORWARD:


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

					case ST_JUMP_BACKWARD:


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
					case ST_CROUCH:

						current_animation = &crouch;


						break;
					case ST_PUNCH_STANDING:

						current_animation = &punch;




						break;
					case ST_PUNCH_CROUCH:

						current_animation = &Crouch_punch;


						break;

					case ST_PUNCH_MEDIUM_CROUCH:

						current_animation = &Crouch_punch;

						break;

					case ST_PUNCH_HARD_CROUCH:

						current_animation = &Crouch_punch;

						break;

					case ST_KICK_CROUCH:

						current_animation = &Crouch_punch;

						break;
					case ST_KICK_MEDIUM_CROUCH:

						current_animation = &Crouch_punch;

						break;
					case ST_KICK_HARD_CROUCH:

						current_animation = &Crouch_punch;

						break;
					case ST_PUNCH_NEUTRAL_JUMP:

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
					case ST_PUNCH_FORWARD_JUMP:


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
					case ST_PUNCH_BACKWARD_JUMP:
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
					case ST_KICK_STANDING:
						current_animation = &kick;

						break;

					case ST_PUNCH_MEDIUM:
						current_animation = &kick;
						break;

					case ST_PUNCH_HARD:

						current_animation = &kick;
						break;

					case ST_KICK_MEDIUM_STANDING:

						current_animation = &kick;

						break;

					case ST_KICK_HARD_STANDING:

						current_animation = &kick;

						break;

					case ST_LIGHTNINGKICK:

						current_animation = &LightningKick;
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


void ModuleChunLi2::positionlimits() {

	if (position.y == 220) {
		speedX = 1;
		speedY = 1;
	}

	if (position.x -20<= App->scene_dhalsim->background.x - 12) {
		position.x = App->scene_dhalsim->background.x - 12+20;
	}

	if (position.x -40>= (App->scene_dhalsim->background.x + App->scene_dhalsim->background.w) -90 ) {
		position.x = (App->scene_dhalsim->background.x + App->scene_dhalsim->background.w)-90 +40;
	}
	
	if (abs(App->chunli->position.x - position.x) >= SCREEN_WIDTH - 10 && position.x>App->chunli->position.x) {
		App->chunli->position.x = position.x - SCREEN_WIDTH + 10;
		position.x = App->chunli->position.x + SCREEN_WIDTH - 10;		
	}

	if (abs(App->chunli->position.x - position.x) >= SCREEN_WIDTH - 130 && position.x < App->chunli->position.x) {
		
		App->chunli->position.x = position.x + SCREEN_WIDTH - 130;
		position.x = App->chunli->position.x - SCREEN_WIDTH + 130;
	}
}

void ModuleChunLi2::colliders_and_blit(Animation* current_animation) {

	PivotX = current_animation->pivot[(int)current_animation->current_frame].x;
	PivotY = current_animation->pivot[(int)current_animation->current_frame].y;
	dmg = current_animation->damage[(int)current_animation->current_frame];


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

		if (position.x > App->chunli->position.x)
			colliders[i] = App->collision->AddCollider({ position.x -(r.w-PivotX) - r.x , position.y - r.h +PivotY - r.y,r.w,r.h }, current_animation->type[i], current_animation->callback[i]);

		if (position.x < App->chunli->position.x)
			colliders[i] = App->collision->AddCollider({ position.x  -  PivotX + r.x , position.y + PivotY - r.h - r.y,r.w,r.h }, current_animation->type[i], current_animation->callback[i]);

	}
	r = current_animation->GetCurrentFrame();

	

	SDL_Rect shadowrect = { 6,8,71,15 };
	if (position.x < App->chunli->position.x) {
		//App->render->Blit(shadow, position.x - PivotX, 207, &shadowrect);
		App->render->Blit(graphics, position.x -PivotX, position.y - r.h, &r);
	}
	if (position.x > App->chunli->position.x) {
	//	App->render->Blit(shadow, position.x - (shadowrect.w + PivotX) +65, 207, &shadowrect);
		App->render->BlitSym(graphics, position.x-(r.w-PivotX), position.y  - r.h, &r);
	}
}

void ModuleChunLi2::OnCollision(Collider* c1, Collider* c2) {
	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER)
	{
		if (state == ST_IDLE) {
			if (position.x > App->chunli->position.x)
				position.x += 1;
			if (position.x < App->chunli->position.x)
				position.x -= 1;
		}

		if (state == ST_WALK_BACKWARD && App->chunli->state == ST_WALK_FORWARD2 
			|| state == ST_WALK_FORWARD && App->chunli->state == ST_WALK_BACKWARD2
			|| state == ST_WALK_BACKWARD && App->chunli->state ==  ST_CROUCH2
			|| state == ST_CROUCH && App->chunli->state== ST_WALK_FORWARD2 
			|| state == ST_WALK_FORWARD && App->chunli->state == ST_CROUCH2) {

			move = false;
		}

		
		else {
			move = true;
		}
		
	}


	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER && (state == ST_JUMP_BACKWARD || state == ST_JUMP_FORWARD || state == ST_JUMP_NEUTRAL)) {
				
		//speedX = -1;
	}


	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER_ATTACK)
	{
		int aux = life;
		if (!damage_received) {
			life = aux - App->chunli->dmg;
		}
		damage_received = true;

	}

}

bool ModuleChunLi2::external_input(p2Qeue<chunli_inputs>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;

	//Key up
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_UP) {
		inputs.Push(IN_CROUCH_UP);
		down = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_UP) {
		up = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_UP) {
		inputs.Push(IN_LEFT_UP);
		left = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_UP) {
		inputs.Push(IN_RIGHT_UP);
		right = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_3] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_4] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_5] == KEY_UP) {
		return false;
	}
	if (App->input->keyboard[SDL_SCANCODE_6] == KEY_UP) {
		return false;
	}

	//Key down

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_DOWN) {
		up = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_DOWN) {
		down = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_DOWN) {
		left = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_DOWN) {
		right = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_DOWN) {
		inputs.Push(IN_X);
	}
	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_DOWN) {
		inputs.Push(IN_C);
	}
	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_DOWN) {
		inputs.Push(IN_LIGHTINGKICK);
	}
	if (App->input->keyboard[SDL_SCANCODE_7] == KEY_DOWN) {
		inputs.Push(IN_1);
	}
	if (App->input->keyboard[SDL_SCANCODE_8] == KEY_DOWN) {
		inputs.Push(IN_2);
	}
	if (App->input->keyboard[SDL_SCANCODE_9] == KEY_DOWN) {
		inputs.Push(IN_3);
	}
	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN) {
		inputs.Push(IN_4);
	}




	//Controller
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_UP) {
		return false;
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_UP) {
		return false;
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_UP) {
		return false;
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_UP) {
		up = false;
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_UP) {
		inputs.Push(IN_CROUCH_UP);
		down = false;
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_UP) {
		inputs.Push(IN_LEFT_UP);
		left = false;
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_UP) {
		inputs.Push(IN_RIGHT_UP);
		right = false;
	}


	if (App->combo->CheckPunchP2() == true) {
		inputs.Push(IN_X);
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
		inputs.Push(IN_C);
	}
	if (App->combo->CheckLightingKickP2() == true) {
		inputs.Push(IN_LIGHTINGKICK);
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_DOWN) {
		up = true;
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_DOWN) {
		down = true;
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN) {
		left = true;
	}
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_DOWN) {
		right = true;
	}

	if (left && right)
		inputs.Push(IN_LEFT_AND_RIGHT);
	{
		if (left)
			inputs.Push(IN_LEFT_DOWN);
		if (right)
			inputs.Push(IN_RIGHT_DOWN);
	}

	if (up && down)
		inputs.Push(IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			inputs.Push(IN_CROUCH_DOWN);
		if (up)
			inputs.Push(IN_JUMP);
	}
	return true;
}

void ModuleChunLi2::internal_input(p2Qeue<chunli_inputs>& inputs)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
			position.y = 220;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME)
		{
			inputs.Push(IN_KICK_FINISH);
			kick_timer = 0;
		}
	}


	if (punch_neutral_jump_timer > 0)
	{
		if (SDL_GetTicks() - punch_neutral_jump_timer > PUNCH_NEUTRAL_JUMP_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_neutral_jump_timer = 0;
		}
	}
	if (punch_medium_timer > 0)
	{
		if (SDL_GetTicks() - punch_medium_timer > PUNCH_MEDIUM_TIME)
		{
			inputs.Push(IN_PUNCH_MEDIUM_FINISH);
			punch_medium_timer = 0;
		}
	}

	if (punch_hard_timer > 0)
	{
		if (SDL_GetTicks() - punch_hard_timer > PUNCH_HARD_TIME)
		{
			inputs.Push(IN_PUNCH_HARD_FINISH);
			punch_hard_timer = 0;
		}
	}

	if (kick_medium_timer > 0)
	{
		if (SDL_GetTicks() - kick_medium_timer > KICK_MEDIUM_TIME)
		{
			inputs.Push(IN_KICK_MEDIUM_FINISH);
			kick_medium_timer = 0;
		}
	}

	if (kick_hard_timer > 0)
	{
		if (SDL_GetTicks() - kick_hard_timer > KICK_HARD_TIME)
		{
			inputs.Push(IN_KICK_HARD_FINISH);
			kick_hard_timer = 0;
		}
	}
}

void ModuleChunLi2::ResetPlayer() {

	life = 1000;
	position.x = 410; 
	if (App->chunli->position.x != 180 || App->chunli->life != 1000) {
		ActiveDeath = 0;
		App->chunli->ResetPlayer();
		App->UI->time = 99;
		App->UI->Counter1 = 9;
		App->UI->Counter2 = 9;
	}
}

chunli_states ModuleChunLi2::process_fsm(p2Qeue<chunli_inputs>& inputs)
{
	static chunli_states state = ST_IDLE;
	chunli_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE2:
		{
			switch (last_input)
			{
			case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
			case IN_JUMP: state = ST_JUMP_NEUTRAL; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
			case IN_C: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
			case IN_LIGHTINGKICK: state = ST_LIGHTNINGKICK; hadouken_timer = SDL_GetTicks(); break;
			case IN_1: state = ST_PUNCH_MEDIUM; punch_medium_timer = SDL_GetTicks(); break;
			case IN_2: state = ST_PUNCH_HARD; punch_hard_timer = SDL_GetTicks(); break;
			case IN_3: state = ST_KICK_MEDIUM_STANDING; kick_medium_timer = SDL_GetTicks(); break;
			case IN_4: state = ST_KICK_HARD_STANDING; kick_hard_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_WALK_FORWARD:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_FORWARD; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
			case IN_C: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
			case IN_LIGHTINGKICK: state = ST_LIGHTNINGKICK; hadouken_timer = SDL_GetTicks(); break;
			case IN_1: state = ST_PUNCH_MEDIUM; punch_medium_timer = SDL_GetTicks(); break;
			case IN_2: state = ST_PUNCH_HARD; punch_hard_timer = SDL_GetTicks(); break;
			case IN_3: state = ST_KICK_MEDIUM_STANDING; kick_medium_timer = SDL_GetTicks(); break;
			case IN_4: state = ST_KICK_HARD_STANDING; kick_hard_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_WALK_BACKWARD:
		{
			switch (last_input)
			{
			case IN_LEFT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_BACKWARD; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
			case IN_C: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
			case IN_LIGHTINGKICK: state = ST_LIGHTNINGKICK; hadouken_timer = SDL_GetTicks(); break;
			case IN_1: state = ST_PUNCH_MEDIUM; punch_medium_timer = SDL_GetTicks(); break;
			case IN_2: state = ST_PUNCH_HARD; punch_hard_timer = SDL_GetTicks(); break;
			case IN_3: state = ST_KICK_MEDIUM_STANDING; kick_medium_timer = SDL_GetTicks(); break;
			case IN_4: state = ST_KICK_HARD_STANDING; kick_hard_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_NEUTRAL_JUMP; punch_neutral_jump_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_FORWARD_JUMP; punch_neutral_jump_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_BACKWARD_JUMP; punch_neutral_jump_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_JUMP_FORWARD; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_JUMP_BACKWARD; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_CROUCH:
		{
			switch (last_input)
			{
			case IN_CROUCH_UP: state = ST_IDLE; break;
			case IN_JUMP_AND_CROUCH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_CROUCH; punch_timer = SDL_GetTicks(); break;
			case IN_1: state = ST_PUNCH_MEDIUM_CROUCH; punch_hard_timer = SDL_GetTicks(); break;
			case IN_2: state = ST_PUNCH_HARD_CROUCH; punch_hard_timer = SDL_GetTicks(); break;
			case IN_3: state = ST_KICK_MEDIUM_CROUCH; punch_medium_timer = SDL_GetTicks(); break;
			case IN_4: state = ST_KICK_HARD_CROUCH; kick_hard_timer = SDL_GetTicks(); break;
			}
		}
		break;
		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH:
				if (IN_CROUCH_DOWN == true)
					state = ST_CROUCH;
				else
					state = ST_IDLE;
				break;
			}
		}
		break;
		case ST_PUNCH_MEDIUM_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_HARD_FINISH:
				if (IN_CROUCH_DOWN == true)
					state = ST_CROUCH;
				else
					state = ST_IDLE;
				break;
			}
		}
		break;
		case ST_PUNCH_HARD_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_HARD_FINISH:
				if (IN_CROUCH_DOWN == true)
					state = ST_CROUCH;
				else
					state = ST_IDLE;
				break;
			}
		}
		break;
		case ST_KICK_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_MEDIUM_FINISH:
				if (IN_CROUCH_DOWN == true)
					state = ST_CROUCH;
				else
					state = ST_IDLE;
				break;
			}
		}
		break;
		case ST_KICK_MEDIUM_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_MEDIUM_FINISH:
				if (IN_CROUCH_DOWN == true)
					state = ST_CROUCH;
				else
					state = ST_IDLE;
				break;
			}
		}
		break;
		case ST_KICK_HARD_CROUCH:
		{
			switch (last_input)
			{
			case IN_KICK_HARD_FINISH:
				if (IN_CROUCH_DOWN == true)
					state = ST_CROUCH;
				else
					state = ST_IDLE;
				break;
			}
		}
		break;
		case ST_KICK_STANDING:
		{
			switch (last_input)
			{
			case IN_KICK_FINISH: state = ST_IDLE; break;
			}
		}
		break;
		case ST_KICK_MEDIUM_STANDING:
		{
			switch (last_input)
			{
			case IN_KICK_MEDIUM_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_KICK_HARD_STANDING:
		{
			switch (last_input)
			{
			case IN_KICK_HARD_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_PUNCH_MEDIUM:
		{
			switch (last_input)
			{
			case IN_PUNCH_MEDIUM_FINISH: state = ST_IDLE; break;
			}

		}
		break;


		case ST_PUNCH_HARD:
		{
			switch (last_input)
			{
			case IN_PUNCH_HARD_FINISH: state = ST_IDLE; break;
			}

		}
		break;
		case ST_LIGHTNINGKICK:
		{
			switch (last_input)
			{
			case IN_LIGHTNINGKICK_FINISH: state = ST_IDLE; break;
			}
			break;
		}

		}
	}
	return state;
}

void ModuleChunLi2::lifecondition(Animation* current_animation) {


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