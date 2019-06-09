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
#include "ModuleCombos.h"
#include "ModuleSlowdown.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLoseScene.h"



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleChunLi::ModuleChunLi()
 {
	

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
	punch.PushBack1({ 320, 524, 87, 96 }, { 32,2 }, punchcollider2, punchhitbox2, punchCollType2, punchCallback2, 4);
	punch.PushBack1({ 218, 531, 101, 89 }, { 32, 2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});
	punch.PushBack1({ 139, 533, 78, 87 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, {});

	punch.speed = 0.3f;
	punch.loop = false;


	// Medium punch animation

	const int punchmcollider = 5;
	SDL_Rect punchmhitbox[punchmcollider] = { { 29, 3, 75, 37 },{ 47, 35, 39, 33 },{59, 64, 31, 21 }, {62,55,81,13} };
	COLLIDER_TYPE punchmCollType[punchmcollider] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER }, {COLLIDER_PLAYER_ATTACK} };
	Module* punchmCallback[punchmcollider] = { { this },{ this },{ this }, {this} };

	punch_medium.PushBack1({ 408, 536, 101, 84 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, 12);
	punch_medium.PushBack1({ 510, 539, 119, 81 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, 12);
	punch_medium.PushBack1({ 630,539, 143,81 }, { 32,2 }, punchmcollider, punchmhitbox, punchmCollType, punchmCallback, 12);
	punch_medium.PushBack1({ 630,539, 143,81 }, { 32,2 }, punchmcollider, punchmhitbox, punchmCollType, punchmCallback, 12);
	punch_medium.PushBack1({ 630,539, 143,81 }, { 32,2 }, punchmcollider, punchmhitbox, punchmCollType, punchmCallback, 12);
	punch_medium.PushBack1({ 510, 539, 119, 81 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, 12);
	punch_medium.PushBack1({ 408, 536, 101, 84 }, { 32,2 }, punchmcollider, punchmhitbox, punchmCollType, punchmCallback, 12);

	punch_medium.speed = 0.3f;
	punch_medium.loop = false;


	//Hard punch animation 	

	const int punchhcollider2 = 5;
	SDL_Rect punchhhitbox2[punchhcollider2] = { { 16,3,37,71 },{	28,3,75,37 },{46,35,39,33}, {52,38,35,45},{	60,69,85,13 } };
	COLLIDER_TYPE punchhCollType2[punchhcollider2] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER }, {COLLIDER_PLAYER}, {COLLIDER_PLAYER_ATTACK} };
	Module* punchhCallback2[punchhcollider2] = { { this },{ this },{ this }, {this}, {this} };

	punch_hard.PushBack1({ 774, 536, 101, 84 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, 16);
	punch_hard.PushBack1({ 876, 541, 119, 79 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, 16);
	punch_hard.PushBack1({ 0, 643, 130, 76 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, 16);
	punch_hard.PushBack1({ 0, 643, 130, 76 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, 16);
	punch_hard.PushBack1({ 876, 541, 119, 79 }, { 32,2 }, punchcollider, punchhitbox, punchCollType, punchCallback, 16);
	punch_hard.PushBack1({ 774, 536, 101, 84 }, { 32,2 }, punchhcollider2, punchhhitbox2, punchhCollType2, punchhCallback2, 16);
	punch_hard.speed = 0.2f;
	punch_hard.loop = false;


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
	kick.PushBack1({ 270, 622, 106,97 }, { 32,2 }, kickcollider2, kickhitbox2, kickCollType2, kickCallback2, 8);
	kick.PushBack1({ 198, 626, 71, 93 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick.PushBack1({ 131,630 , 66, 89 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick.speed = 0.2f;

	//kick medium

	const int kickcollider3 = 6;
	SDL_Rect kickhitbox3[kickcollider3] = { { 0, 3, 44, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 }, {54,70,81,19} };
	COLLIDER_TYPE kickCollType3[kickcollider3] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER }, {COLLIDER_PLAYER_ATTACK} };
	Module* kickCallback3[kickcollider3] = { { this },{ this },{ this },{ this },{ this }, {this} };

	kick_medium.PushBack1({ 131,630 , 66, 89 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick_medium.PushBack1({ 198, 626, 71, 93 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick_medium.PushBack1({ 377,624,109,95 }, { 32,2 }, kickcollider3, kickhitbox3, kickCollType3, kickCallback3, 12);
	kick_medium.PushBack1({ 377,624,109,95 }, { 32,2 }, kickcollider3, kickhitbox3, kickCollType3, kickCallback3, 12);
	kick_medium.PushBack1({ 377,624,109,95 }, { 32,2 }, kickcollider3, kickhitbox3, kickCollType3, kickCallback3, 12);
	kick_medium.PushBack1({ 198, 626, 71, 93 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick_medium.PushBack1({ 131,630 , 66, 89 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick_medium.speed = 0.3f;
	kick_medium.loop = false;


	//kick hard

	const int kickcollider4 = 6;
	SDL_Rect kickhitbox4[kickcollider4] = { { 0, 3, 44, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 38, 66, 77, 33 },{ 2, 37, 35, 41 }, {65,80,79,27} };
	COLLIDER_TYPE kickCollType4[kickcollider4] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER }, {COLLIDER_PLAYER_ATTACK} };
	Module* kickCallback4[kickcollider4] = { { this },{ this },{ this },{ this },{ this }, {this} };

	kick_hard.PushBack1({ 487,641 , 64, 79 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick_hard.PushBack1({ 552, 627, 70, 92 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick_hard.PushBack1({ 623,629,82,90 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick_hard.PushBack1({ 706,622,123,97 }, { 32,2 }, kickcollider4, kickhitbox4, kickCollType4, kickCallback4, 16);

	kick_hard.PushBack1({ 830,636,102,83 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});
	kick_hard.PushBack1({ 933, 638, 70, 81 }, { 32,2 }, kickcollider, kickhitbox, kickCollType, kickCallback, {});

	kick_hard.speed = 0.15f;
	kick_hard.loop = false;


	//crouch punch
	const int crhpnchcollider = 5;//Collider num for the crouch punch animation
	SDL_Rect crhpnchhitbox[crhpnchcollider] = { { 30, 48, 23, 19 },{ 17, 29, 22, 27 },{ 38, 29, 29, 24 },{ 0, 0, 40, 29 },{ 40, 0, 34, 32 } };
	COLLIDER_TYPE crchpnchCollType[crhpnchcollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crhpnchCallback[crhpnchcollider] = { {this},{this},{this},{this},{this} };

	const int crhpnchcollider2 = 6;
	SDL_Rect crhpnchhitbox2[crhpnchcollider2] = { { 30, 48, 23, 19 },{ 17, 29, 22, 27 },{ 38, 29, 29, 24 },{ 0, 0, 40, 29 },{ 40, 0, 34, 32 },{52, 38, 56, 12} };
	COLLIDER_TYPE crchpnchCollType2[crhpnchcollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER}, {COLLIDER_PLAYER_ATTACK} };
	Module* crhpnchCallback2[crhpnchcollider2] = { {this},{this},{this},{this},{this} };


	Crouch_punch.PushBack1({ 368, 839, 71, 66 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_punch.PushBack1({ 518, 841, 107, 64 }, { 32, 2 }, crhpnchcollider2, crhpnchhitbox2, crchpnchCollType2, crhpnchCallback2, 6);
	Crouch_punch.PushBack1({ 440, 839, 77, 66 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_punch.speed = 0.13f;
	Crouch_punch.loop = true;

	//crouch  medium punch


	const int crhpnchcollider3 = 6;
	SDL_Rect crhpnchhitbox3[crhpnchcollider3] = { { 30, 48, 23, 19 },{ 17, 29, 22, 27 },{ 38, 29, 29, 24 },{ 0, 0, 40, 29 },{ 40, 0, 34, 32 },{55, 39, 80, 19} };
	COLLIDER_TYPE crchpnchCollType3[crhpnchcollider3] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER}, {COLLIDER_PLAYER_ATTACK} };
	Module* crhpnchCallback3[crhpnchcollider3] = { {this},{this},{this},{this},{this} };


	Crouch_medium_punch.PushBack1({ 751, 838, 80, 67 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_medium_punch.PushBack1({ 832, 838, 100, 67 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_medium_punch.PushBack1({ 626, 838, 124, 67 }, { 32, 2 }, crhpnchcollider3, crhpnchhitbox3, crchpnchCollType3, crhpnchCallback3, 10);
	Crouch_medium_punch.PushBack1({ 626, 838, 124, 67 }, { 32, 2 }, crhpnchcollider3, crhpnchhitbox3, crchpnchCollType3, crhpnchCallback3, 10);
	Crouch_medium_punch.PushBack1({ 626, 838, 124, 67 }, { 32, 2 }, crhpnchcollider3, crhpnchhitbox3, crchpnchCollType3, crhpnchCallback3, 10);
	Crouch_medium_punch.PushBack1({ 832, 838, 100, 67 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_medium_punch.PushBack1({ 751, 838, 80, 67 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_medium_punch.speed = 0.3f;
	Crouch_medium_punch.loop = false;

	//crouch  hard punch


	Crouch_hard_punch.PushBack1({ 751, 838, 80, 67 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_hard_punch.PushBack1({ 832, 838, 100, 67 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_hard_punch.PushBack1({ 626, 838, 124, 67 }, { 32, 2 }, crhpnchcollider3, crhpnchhitbox3, crchpnchCollType3, crhpnchCallback3, 16);
	Crouch_hard_punch.PushBack1({ 626, 838, 124, 67 }, { 32, 2 }, crhpnchcollider3, crhpnchhitbox3, crchpnchCollType3, crhpnchCallback3, 16);
	Crouch_hard_punch.PushBack1({ 626, 838, 124, 67 }, { 32, 2 }, crhpnchcollider3, crhpnchhitbox3, crchpnchCollType3, crhpnchCallback3, 16);
	Crouch_hard_punch.PushBack1({ 832, 838, 100, 67 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_hard_punch.PushBack1({ 751, 838, 80, 67 }, { 32, 2 }, crhpnchcollider, crhpnchhitbox, crchpnchCollType, crhpnchCallback, {});
	Crouch_hard_punch.speed = 0.3f;
	Crouch_hard_punch.loop = false;


	// Crouch kick

	const int crhcollider3 = 4;//Collider num for the crouch animation
	SDL_Rect crhhitbox3[crhcollider3] = { { 10, 3, 37, 51 },{ 11, 6, 43, 25 },{ 11, 31, 35, 25 },{ 21, 43, 31, 21 } };
	COLLIDER_TYPE crchCollType3[crhcollider3] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crhCallback3[crhcollider3] = { {this},{this},{this},{this} };

	const int crhcollider4 = 5;//Collider num for the crouch animation
	SDL_Rect crhhitbox4[crhcollider4] = { { 10, 3, 37, 51 },{ 11, 6, 43, 25 },{ 11, 31, 35, 25 },{ 21, 43, 31, 21 },{ 31, 3, 75, 19 } };
	COLLIDER_TYPE crchCollType4[crhcollider4] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crhCallback4[crhcollider4] = { {this},{this},{this},{this},{this} };

	Crouch_kick.PushBack1({ 139, 966, 63, 59 }, { 32, 2 }, crhcollider3, crhhitbox3, crchCollType3, crhCallback3, {});
	Crouch_kick.PushBack1({ 203, 966, 61, 58 }, { 32, 2 }, crhcollider3, crhhitbox3, crchCollType3, crhCallback3, {});
	Crouch_kick.PushBack1({ 265, 976, 107, 48 }, { 32, 2 }, crhcollider4, crhhitbox4, crchCollType4, crhCallback4, 8);
	Crouch_kick.PushBack1({ 265, 976, 107, 48 }, { 32, 2 }, crhcollider4, crhhitbox4, crchCollType4, crhCallback4, 8);
	Crouch_kick.PushBack1({ 265, 976, 107, 48 }, { 32, 2 }, crhcollider4, crhhitbox4, crchCollType4, crhCallback4, 8);


	Crouch_kick.speed = 0.25f;
	Crouch_kick.loop = false;

	// Crouch kick medium

	const int crhcollider5 = 4;//Collider num for the crouch animation
	SDL_Rect crhhitbox5[crhcollider5] = { { 10, 3, 37, 51 },{ 24, 3, 83, 23 },{ 11, 31, 35, 25 },{ 21, 43, 31, 21 } };
	COLLIDER_TYPE crchCollType5[crhcollider5] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crhCallback5[crhcollider5] = { {this},{this},{this},{this} };

	const int crhcollider6 = 5;//Collider num for the crouch animation
	SDL_Rect crhhitbox6[crhcollider6] = { { 10, 3, 37, 51 },{ 24, 3, 83, 23 },{ 11, 31, 35, 25 },{ 21, 43, 31, 21 },{ 36, 3, 85, 19 } };
	COLLIDER_TYPE crchCollType6[crhcollider6] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crhCallback6[crhcollider6] = { {this},{this},{this},{this},{this} };

	Crouch_medium_kick.PushBack1({ 373, 961, 77, 63 }, { 32, 2 }, crhcollider5, crhhitbox5, crchCollType5, crhCallback5, {});
	Crouch_medium_kick.PushBack1({ 451, 969, 115, 55 }, { 32, 2 }, crhcollider6, crhhitbox6, crchCollType6, crhCallback6, 10);
	Crouch_medium_kick.PushBack1({ 567, 962, 76, 62 }, { 32, 2 }, crhcollider5, crhhitbox5, crchCollType5, crhCallback5, {});


	Crouch_medium_kick.speed = 0.20f;
	Crouch_medium_kick.loop = false;

	// Crouch kick hard

	const int crhcollider1 = 4;//Collider num for the crouch animation
	SDL_Rect crhhitbox1[crhcollider1] = { { 7, 3, 37, 51 },{ 8, 31, 35, 25 },{ 10, 43, 31, 21 },{ 49, 32, 55, 31 } };
	COLLIDER_TYPE crchCollType1[crhcollider1] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crhCallback1[crhcollider1] = { {this},{this},{this},{this} };

	const int crhcollider2 = 5;//Collider num for the crouch animation
	SDL_Rect crhhitbox2[crhcollider2] = { { 7, 3, 37, 51 },{ 8, 31, 35, 25 },{ 18, 43, 31, 21 },{ 57, 32, 55, 31 },{ 46, 32, 89, 33 } };
	COLLIDER_TYPE crchCollType2[crhcollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crhCallback2[crhcollider2] = { {this},{this},{this},{this},{this} };

	Crouch_hard_kick.PushBack1({ 644, 962, 72, 62 }, { 32, 2 }, crhcollider1, crhhitbox1, crchCollType1, crhCallback1, {});
	Crouch_hard_kick.PushBack1({ 717, 960, 60, 64 }, { 32, 2 }, crhcollider1, crhhitbox1, crchCollType1, crhCallback1, {});
	Crouch_hard_kick.PushBack1({ 796, 951, 128, 73 }, { 32, 2 }, crhcollider2, crhhitbox2, crchCollType2, crhCallback2, 14);
	Crouch_hard_kick.PushBack1({ 717, 960, 60, 64 }, { 32, 2 }, crhcollider1, crhhitbox1, crchCollType1, crhCallback1, {});
	Crouch_hard_kick.PushBack1({ 644, 962, 72, 62 }, { 32, 2 }, crhcollider1, crhhitbox1, crchCollType1, crhCallback1, {});
	Crouch_hard_kick.PushBack1({ 147, 839, 72, 65 }, { 32, 2 }, crhcollider1, crhhitbox1, crchCollType1, crhCallback1, {});

	Crouch_hard_kick.speed = 0.25f;
	Crouch_hard_kick.loop = false;

	//punch neutral jump



	const int jumppunchcollider = 6;
	SDL_Rect jumppunchhitbox[jumppunchcollider] = { { 5, 53, 37, 19 },{ 2, 4, 51, 54 },{ 9, 55, 37, 39 },{ 20, 86, 31, 21 },{ 8, 68, 31, 27 }, {29,30,53,35} };
	COLLIDER_TYPE jumppunchCollType[jumppunchcollider] = { {COLLIDER_PLAYER},{COLLIDER_NONE},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER}, {COLLIDER_PLAYER_ATTACK} };
	Module* jumppunchCallback[jumppunchcollider] = { {this},{this},{this},{this},{this},{this} };

	jump_neutral_punch.PushBack1({ 1966, 22, 66,89 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_punch.PushBack1({ 1024, 131,53 ,90 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_punch.PushBack1({ 1078, 146, 85, 75 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_punch.PushBack1({ 1164, 144, 87, 77 }, { 32, 2 }, jumppunchcollider, jumppunchhitbox, jumppunchCollType, jumppunchCallback, 10);
	jump_neutral_punch.speed = 0.45f;
	jump_neutral_punch.loop = false;

	//punch neutral jump medium


	jump_neutral_punch_medium.PushBack1({ 1966, 22, 66,89 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_punch_medium.PushBack1({ 1024, 131,53 ,90 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_punch_medium.PushBack1({ 1078, 146, 85, 75 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_punch_medium.PushBack1({ 1164, 144, 87, 77 }, { 32, 2 }, jumppunchcollider, jumppunchhitbox, jumppunchCollType, jumppunchCallback, 14);
	jump_neutral_punch_medium.speed = 0.45f;
	jump_neutral_punch_medium.loop = false;

	//punch neutral jump hard


	jump_neutral_punch_hard.PushBack1({ 1966, 22, 66,89 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_punch_hard.PushBack1({ 1024, 131,53 ,90 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_punch_hard.PushBack1({ 1078, 146, 85, 75 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_punch_hard.PushBack1({ 1164, 144, 87, 77 }, { 32, 2 }, jumppunchcollider, jumppunchhitbox, jumppunchCollType, jumppunchCallback, 16);
	jump_neutral_punch_hard.speed = 0.45f;
	jump_neutral_punch_hard.loop = false;

	//punch forward jump

	jump_forward_punch.PushBack1({ 1252, 147, 53, 74 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_punch.PushBack1({ 1306, 146, 59,75 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_punch.PushBack1({ 1366, 144,83, 77 }, { 32, 2 }, jumppunchcollider, jumppunchhitbox, jumppunchCollType, jumppunchCallback, 10);
	jump_forward_punch.speed = 0.2f;
	jump_forward_punch.loop = false;

	//punch forward jump medium

	jump_forward_punch_medium.PushBack1({ 1252, 147, 53, 74 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_punch_medium.PushBack1({ 1306, 146, 59,75 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_punch_medium.PushBack1({ 1366, 144,83, 77 }, { 32, 2 }, jumppunchcollider, jumppunchhitbox, jumppunchCollType, jumppunchCallback, 14);
	jump_forward_punch_medium.speed = 0.2f;
	jump_forward_punch_medium.loop = false;

	//punch forward jump hard 

	jump_forward_punch_hard.PushBack1({ 1252, 147, 53, 74 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_punch_hard.PushBack1({ 1306, 146, 59,75 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_punch_hard.PushBack1({ 1366, 144,83, 77 }, { 32, 2 }, jumppunchcollider, jumppunchhitbox, jumppunchCollType, jumppunchCallback, 16);
	jump_forward_punch_hard.speed = 0.2f;
	jump_forward_punch_hard.loop = false;

	//punch backward jump

	jump_backward_punch.PushBack1({ 1252, 147, 53, 74 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_punch.PushBack1({ 1306, 146, 59,75 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_punch.PushBack1({ 1366, 144,83, 77 }, { 32, 2 }, jumppunchcollider, jumppunchhitbox, jumppunchCollType, jumppunchCallback, 10);
	jump_backward_punch.speed = 0.2f;
	jump_backward_punch.loop = false;

	//punch backward jump medium

	jump_backward_punch_medium.PushBack1({ 1252, 147, 53, 74 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_punch_medium.PushBack1({ 1306, 146, 59,75 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_punch_medium.PushBack1({ 1366, 144,83, 77 }, { 32, 2 }, jumppunchcollider, jumppunchhitbox, jumppunchCollType, jumppunchCallback, 14);
	jump_backward_punch_medium.speed = 0.2f;
	jump_backward_punch_medium.loop = false;

	//punch backward jump hard 

	jump_backward_punch_hard.PushBack1({ 1252, 147, 53, 74 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_punch_hard.PushBack1({ 1306, 146, 59,75 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_punch_hard.PushBack1({ 1366, 144,83, 77 }, { 32, 2 }, jumppunchcollider, jumppunchhitbox, jumppunchCollType, jumppunchCallback, 16);
	jump_backward_punch_hard.speed = 0.2f;
	jump_backward_punch_hard.loop = false;

	//KICK forward jump


	const int jumpkCollider2 = 6;//Collider num for the crouch animation
	SDL_Rect jumpkhitbox2[jumpkCollider2] = { { 7, 3, 37, 51 },{ 8, 31, 35, 25 },{ 18, 43, 31, 21 },{ 57, 32, 55, 31 },{ 46, 32, 89, 33 }, {43,10,63,27} };
	COLLIDER_TYPE jumpkCollType2[jumpkCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpkCallback2[jumpkCollider2] = { {this},{this},{this},{this},{this},{this} };

	jump_forward_kick.PushBack1({ 1806,158,57,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick.PushBack1({ 1864,158,72,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick.PushBack1({ 1937,165,111,56 }, { 32, 2 }, jumpkCollider2, jumpkhitbox2, jumpkCollType2, jumpkCallback2, 10);
	jump_forward_kick.PushBack1({ 1937,165,111,56 }, { 32, 2 }, jumpkCollider2, jumpkhitbox2, jumpkCollType2, jumpkCallback2, 10);
	jump_forward_kick.PushBack1({ 1864,158,72,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick.PushBack1({ 1806,158,57,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick.speed = 0.2f;
	jump_forward_kick.loop = false;

	//KICK forward jump medium

	jump_forward_kick_medium.PushBack1({ 1806,158,57,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick_medium.PushBack1({ 1864,158,72,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick_medium.PushBack1({ 1937,165,111,56 }, { 32, 2 }, jumpkCollider2, jumpkhitbox2, jumpkCollType2, jumpkCallback2, 12);
	jump_forward_kick_medium.PushBack1({ 1937,165,111,56 }, { 32, 2 }, jumpkCollider2, jumpkhitbox2, jumpkCollType2, jumpkCallback2, 12);
	jump_forward_kick_medium.PushBack1({ 1864,158,72,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick_medium.PushBack1({ 1806,158,57,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick_medium.speed = 0.2f;
	jump_forward_kick_medium.loop = false;

	//KICK forward jump hard 


	const int jumpkCollider = 6;//Collider num for the crouch animation
	SDL_Rect jumpkhitbox[jumpkCollider] = { { 7, 3, 37, 51 },{ 8, 31, 35, 25 },{ 18, 43, 31, 21 },{ 57, 32, 55, 31 },{ 46, 32, 89, 33 }, {29,45,61,41} };
	COLLIDER_TYPE jumpkCollType[jumpkCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpkCallback[jumpkCollider] = { {this},{this},{this},{this},{this},{this} };

	jump_forward_kick_hard.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick_hard.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick_hard.PushBack1({ 1508, 127, 84, 94 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick_hard.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 16);
	jump_forward_kick_hard.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 16);
	jump_forward_kick_hard.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 16);
	jump_forward_kick_hard.PushBack1({ 1656,128,86,93 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick_hard.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_forward_kick_hard.speed = 0.25f;
	jump_forward_kick_hard.loop = false;

	//KICK forward jump

	jump_backward_kick.PushBack1({ 1806,158,57,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick.PushBack1({ 1864,158,72,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick.PushBack1({ 1937,165,111,56 }, { 32, 2 }, jumpkCollider2, jumpkhitbox2, jumpkCollType2, jumpkCallback2, 10);
	jump_backward_kick.PushBack1({ 1937,165,111,56 }, { 32, 2 }, jumpkCollider2, jumpkhitbox2, jumpkCollType2, jumpkCallback2, 10);
	jump_backward_kick.PushBack1({ 1864,158,72,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick.PushBack1({ 1806,158,57,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick.speed = 0.2f;
	jump_backward_kick.loop = false;

	//KICK forward jump medium

	jump_backward_kick_medium.PushBack1({ 1806,158,57,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick_medium.PushBack1({ 1864,158,72,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick_medium.PushBack1({ 1937,165,111,56 }, { 32, 2 }, jumpkCollider2, jumpkhitbox2, jumpkCollType2, jumpkCallback2, 12);
	jump_backward_kick_medium.PushBack1({ 1937,165,111,56 }, { 32, 2 }, jumpkCollider2, jumpkhitbox2, jumpkCollType2, jumpkCallback2, 12);
	jump_backward_kick_medium.PushBack1({ 1864,158,72,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick_medium.PushBack1({ 1806,158,57,63 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick_medium.speed = 0.2f;
	jump_backward_kick_medium.loop = false;

	//KICK forward jump hard 

	jump_backward_kick_hard.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick_hard.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick_hard.PushBack1({ 1508, 127, 84, 94 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick_hard.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 16);
	jump_backward_kick_hard.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 16);
	jump_backward_kick_hard.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 16);
	jump_backward_kick_hard.PushBack1({ 1656,128,86,93 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick_hard.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_backward_kick_hard.speed = 0.25f;
	jump_backward_kick_hard.loop = false;

	//Lightning Kick

	const int lkcollider = 9;//Collider num for the idle animation
	SDL_Rect lkhitbox[lkcollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} , {91,66,31,15}, {57,19,71,39}, {90,42,51,25} , {48,4,83,29} };
	COLLIDER_TYPE lkCollType[lkcollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER}, {COLLIDER_PLAYER_ATTACK }, {COLLIDER_PLAYER_ATTACK }, {COLLIDER_PLAYER_ATTACK }, {COLLIDER_PLAYER_ATTACK } };
	Module* lkCallback[lkcollider] = { {this},{this},{this},{this},{this},{this},{this},{this},{this} };

	SDL_Rect lkhitbox1[lkcollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33}, {57,19,71,39} };
	SDL_Rect lkhitbox2[lkcollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33}, {90,42,51,25} };
	SDL_Rect lkhitbox3[lkcollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33}, {48,4,83,29} };

	LightningKick.PushBack1({ 1537, 226, 107, 99 }, { 32, 2 }, lkcollider, lkhitbox, lkCollType, lkCallback, 15);
	LightningKick.PushBack1({ 1645,222 , 123, 103 }, { 32, 2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	LightningKick.PushBack1({ 1769, 230, 119, 95 }, { 32, 2 }, lkcollider, lkhitbox, lkCollType, lkCallback, 15);
	LightningKick.PushBack1({ 1889, 230, 136,95 }, { 32, 2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	LightningKick.PushBack1({ 1025, 355, 120, 93 }, { 32, 2 }, lkcollider, lkhitbox, lkCollType, lkCallback, 15);
	LightningKick.PushBack1({ 1146, 353, 152, 95 }, { 32, 2 }, idleCollider, idleHitbox, idleCollType, idleCallBack, {});
	LightningKick.PushBack1({ 1300, 355, 101, 93 }, { 32, 2 }, lkcollider, lkhitbox, lkCollType, lkCallback, 15);
	LightningKick.speed = 0.2f;
	LightningKick.loop = true;

	//Wirlhwind Kick

	const int wkcollider = 2;//Collider num for the WhirlwindKick animation
	SDL_Rect wkhitbox[wkcollider] = { {25,41,31,49},{30,55,37,39} };
	COLLIDER_TYPE wkCollType[wkcollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* wkCallback[wkcollider] = { {this},{this} };

	const int wkcollider1 = 3;//Collider num for the WhirlwindKick animation
	SDL_Rect wkhitbox1[wkcollider1] = { {25,41,31,49},{30,55,37,39}, {1,59,151,41} };
	COLLIDER_TYPE wkCollType1[wkcollider1] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* wkCallback1[wkcollider1] = { {this},{this},{this} };


	WhirlwindKick.PushBack1({ 1402,326,55,122 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1458,333,55,115 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1514,375,101,73 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1616,376,54,71 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1671,375,101,73 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1773,379,149,69 }, { 0, 30 }, wkcollider1, wkhitbox1, wkCollType1, wkCallback1, 15);
	WhirlwindKick.PushBack1({ 1920,379,96,69 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1024,477,48,68 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1073,476,86,69 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1160,475,146,70 }, { 0, 30 }, wkcollider1, wkhitbox1, wkCollType1, wkCallback1, 15);
	WhirlwindKick.PushBack1({ 1514,375,101,73 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1616,376,54,71 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1671,375,101,73 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1773,379,149,69 }, { 0, 30 }, wkcollider1, wkhitbox1, wkCollType1, wkCallback1, 15);
	WhirlwindKick.PushBack1({ 1920,379,96,69 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1024,477,48,68 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1073,476,86,69 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1160,475,146,70 }, { 0, 30 }, wkcollider1, wkhitbox1, wkCollType1, wkCallback1, 15);
	WhirlwindKick.PushBack1({ 1458,333,55,115 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1402,326,55,122 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1235,23,109,88 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1113,63,121,48 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1024,30,88,81 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 1756, 1, 47, 110 }, { 0, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.PushBack1({ 363, 437, 72, 86 }, { 20, 30 }, wkcollider, wkhitbox, wkCollType, wkCallback, 0);
	WhirlwindKick.speed = 0.286f;
	WhirlwindKick.loop = false;


	// JUMP NEUTRAL KICK

	jump_neutral_kick.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_kick.PushBack1({ 1508, 127, 84, 94 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_kick.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 10);
	jump_neutral_kick.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 10);
	jump_neutral_kick.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 10);
	jump_neutral_kick.PushBack1({ 1656,128,86,93 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_kick.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});

	jump_neutral_kick.speed = 0.25f;
	jump_neutral_kick.loop = false;

	// JUMP NEUTRAL KICK MEIDUM


	jump_neutral_kick_medium.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_kick_medium.PushBack1({ 1508, 127, 84, 94 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_kick_medium.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 12);
	jump_neutral_kick_medium.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 12);
	jump_neutral_kick_medium.PushBack1({ 1592,122,63,99 }, { 32, 2 }, jumpkCollider, jumpkhitbox, jumpkCollType, jumpkCallback, 12);
	jump_neutral_kick_medium.PushBack1({ 1656,128,86,93 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_kick_medium.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});

	jump_neutral_kick_medium.speed = 0.25f;
	jump_neutral_kick_medium.loop = false;

	// JUMP NEUTRAL KICK HARD

	const int jumpkCollider1 = 6;//Collider num for the crouch animation
	SDL_Rect jumpkhitbox1[jumpkCollider1] = { { 7, 3, 37, 51 },{ 8, 31, 35, 25 },{ 18, 43, 31, 21 },{ 57, 32, 55, 31 },{ 46, 32, 89, 33 }, {56,53,66,35} };
	COLLIDER_TYPE jumpkCollType1[jumpkCollider1] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpkCallback1[jumpkCollider1] = { {this},{this},{this},{this},{this},{this} };

	jump_neutral_kick_hard.PushBack1({ 1024,228,57,97 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});
	jump_neutral_kick_hard.PushBack1({ 1112,260,99,65 }, { 32, 2 }, jumpkCollider1, jumpkhitbox1, jumpkCollType1, jumpkCallback1, 16);
	jump_neutral_kick_hard.PushBack1({ 1112,260,99,65 }, { 32, 2 }, jumpkCollider1, jumpkhitbox1, jumpkCollType1, jumpkCallback1, 16);
	jump_neutral_kick_hard.PushBack1({ 1212,255,110,70 }, { 32, 2 }, jumpkCollider1, jumpkhitbox1, jumpkCollType1, jumpkCallback1, 16);
	jump_neutral_kick_hard.PushBack1({ 1212,255,110,70 }, { 32, 2 }, jumpkCollider1, jumpkhitbox1, jumpkCollType1, jumpkCallback1, 16);
	jump_neutral_kick_hard.PushBack1({ 1323,232,86,93 }, { 32, 2 }, jumpkCollider1, jumpkhitbox1, jumpkCollType1, jumpkCallback1, 16);
	jump_neutral_kick_hard.PushBack1({ 1450, 126, 57, 95 }, { 32, 2 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback, {});

	jump_neutral_kick_hard.speed = 0.3f;
	jump_neutral_kick_hard.loop = false;



	//damage animation 
	const int dmgCollider = 5;//Collider num for the idle animation
	SDL_Rect dmgHitbox[dmgCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE dmgCollType[dmgCollider] = { {COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE} };
	Module* dmgCallBack[dmgCollider] = { {this},{this},{this},{this},{this} };

	damage.PushBack1({ 1307,465,72,80 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage.PushBack1({ 1385, 458, 79, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage.PushBack1({ 1465, 458, 76, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage.PushBack1({ 1542, 462, 72, 83 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage.speed = 0.1f;
	damage.loop = false;

	//damage animation 

	damage2.PushBack1({ 1804,453,73,92 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage2.PushBack1({ 1878, 453, 76, 92 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage2.PushBack1({ 1024, 547, 102, 84 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage2.speed = 0.4f;
	damage2.loop = false;

	//damage animation

	damage3.PushBack1({ 1825,556,95,76 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage3.PushBack1({ 1921, 572, 83, 60 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage3.PushBack1({ 1024, 681, 117, 48 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage3.PushBack1({ 1142, 691, 139, 38 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage3.PushBack1({ 1284, 672, 104, 57 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage3.PushBack1({ 1389, 658, 94, 71 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage3.PushBack1({ 1284, 672, 104, 57 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage3.PushBack1({ 1142, 691, 139, 38 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage3.speed = 0.2f;
	damage3.loop = false;



	//Damage Crouch

	damage4.PushBack1({ 1350,562,72,69 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage4.PushBack1({ 1423, 560, 73, 71 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage4.PushBack1({ 1497, 564, 76, 67 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage4.PushBack1({ 1574, 570, 92, 61 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage4.speed = 0.2f;
	damage4.loop = false;

	//damage animation

	damage5.PushBack1({ 1825,556,95,76 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage5.PushBack1({ 1921, 572, 83, 60 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage5.PushBack1({ 1024, 681, 117, 48 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage5.PushBack1({ 1142, 691, 139, 38 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage5.PushBack1({ 1284, 672, 104, 57 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage5.PushBack1({ 1389, 658, 94, 71 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage5.PushBack1({ 1284, 672, 104, 57 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage5.PushBack1({ 1142, 691, 139, 38 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	damage5.speed = 0.1f;
	damage5.loop = false;

	//Block standing 

	block_standing.PushBack1({ 1667,546,84,85 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	block_standing.speed = 0.1f;
	block_standing.loop = false;

	//Block standing 

	block_crouch.PushBack1({ 1751,564,74,67 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	block_crouch.speed = 0.1f;
	block_crouch.loop = false;

	//Win1 
	win1.PushBack1({ 1867,632,68,97 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win1.PushBack1({ 1867,632,68,97 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win1.PushBack1({ 1936,632,68,97 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win1.PushBack1({ 1024,764,68,93 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win1.speed = 0.1f;
	win1.loop = false;

	//Win2
	win2.PushBack1({ 1093,755,48,102 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win2.PushBack1({ 1142,729,74,128 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win2.PushBack1({ 1217,745,74,112 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win2.PushBack1({ 1292,755,74,101 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win2.PushBack1({ 1367,753,48,103 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win2.PushBack1({ 1416,740,58,116 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack, {});
	win2.speed = 0.1f;
	win2.loop = false;

}

ModuleChunLi::~ModuleChunLi()
{}

// Load assets
bool ModuleChunLi::Start()
{
	bool ret = true;
	//Effects
	LightningKick_effect = App->audio->LoadChunk("Assets/Sound/Effects/chunli_yap.wav");
	WhirlwindKick_effect = App->audio->LoadChunk("Assets/Sound/Effects/chunli_kick.wav");
	light_damage = App->audio->LoadChunk("Asstes/Sound/Effects/light_attack.wav");
	medium_damage = App->audio->LoadChunk("Assets/Sound/Effects/medium_attack.wav");
	high_damage = App->audio->LoadChunk("Assets/Sound/Effects/high_attack.wav");
	wind = App->audio->LoadChunk("Assets/Sound/Effects/Wind.wav");
	win_sound = App->audio->LoadChunk("Assets/Sound/Effects/chunli-laugh.wav");
	death_sound = App->audio->LoadChunk("Assets/Sound/Effects/chunli-death.wav");
	syou = App->audio->LoadChunk("Assets/Sound/Effects/you.wav");
	swin = App->audio->LoadChunk("Assets/Sound/Effects/win.wav");
	

	graphics = App->textures->Load("Assets/Images/ChunLi.png"); // arcade version
	shadow = App->textures->Load("Assets/Images/shadow.png");

	position.x = 180;
	position.y = 220;

	
	//Start functions to reset player
	ResetPlayer();
	Death.Reset();
	DeathCount = 0;
	victorycount = 0;
	victoryRound1 = false;
	victoryRound2 = false;
	
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

	App->audio->UnloadChunk(LightningKick_effect);
	App->audio->UnloadChunk(WhirlwindKick_effect);
	App->audio->UnloadChunk(light_damage);
	App->audio->UnloadChunk(medium_damage);
	App->audio->UnloadChunk(high_damage);
	App->audio->UnloadChunk(wind);
	App->audio->UnloadChunk(win_sound);
	App->audio->UnloadChunk(death_sound);
	App->audio->UnloadChunk(syou);
	App->audio->UnloadChunk(swin);

	return true;
}


update_status ModuleChunLi::Update()
{
	if (GodMode)//deletes all the collision boxes if in god mode
	{
		for (int i = 0; i < MAX_COLLIDERS; i++)
		{
			if (colliders[i] != nullptr)
				colliders[i]->to_delete = true;
		}
	}
	for (int i = 0; i < MAX_COLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colliders[i] != nullptr) {
			colliders[i]->to_delete = true;
			colliders[i] = nullptr;
		}
	}

	Animation* current_animation = &idle;
	p2Qeue<chunli_inputs2> inputs;

	chunli_states2 current_state = ST_UNKNOWN2;
	
	positionlimits();
	debugcommands();
	

	if (death == false) {
		while (external_input(inputs))
		{
			internal_input(inputs);
			
			
			
			state = process_fsm(inputs);
						
			
			if (state != current_state)
			{
				lifecondition(current_animation);
				
				if (App->chunli2->life >= 0 ) 
				{					
					switch (state)
					{
					case ST_IDLE2:						
						current_animation = &idle;
						resetanimations();						
						crouch.Reset();
						wkcounter = 0;
						whirlwindMove = false;
						onAir = false;
						move = true;			
						break;
					case ST_WALK_FORWARD2:
						current_animation = &forward;
						resetanimations();
						if(move)
						position.x += speedX;		
						onAir = false;
						move = true;
						break;
					case ST_WALK_BACKWARD2:
						current_animation = &backward;
						resetanimations();
						if(move)
						position.x -= speedX;		
						onAir = false;
						move = true;
						break;
					case ST_JUMP_NEUTRAL2:								
						current_animation = &jump_neutral;
						onAir == true;
						jump_neutral_logic();													
						break;
					case ST_JUMP_FORWARD2:						
						current_animation = &jump_forward;
						jump_forward_logic();
						onAir == true;
						break;
					case ST_JUMP_BACKWARD2:						
						current_animation = &jump_backwards;
						jump_backward_logic();	
						onAir == true;
						break;
					case ST_CROUCH2:
						resetanimations();
						current_animation = &crouch;					
						break;
					case ST_PUNCH_STANDING2:						
						current_animation = &punch;	
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						break;
					case ST_PUNCH_CROUCH2:
						current_animation = &Crouch_punch;	
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						break;
					case ST_PUNCH_MEDIUM_CROUCH2:
						current_animation = &Crouch_medium_punch;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						crouchAttack = true;
						break;					
					case ST_PUNCH_HARD_CROUCH2:
						current_animation = &Crouch_hard_punch;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						crouchAttack = true;
						break;
					case ST_KICK_CROUCH2:
						current_animation = &Crouch_kick;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						crouchAttack = true;
						break;
					case ST_KICK_MEDIUM_CROUCH2:
						current_animation = &Crouch_medium_kick;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						crouchAttack = true;
						break;
					case ST_KICK_HARD_CROUCH2:
						current_animation = &Crouch_hard_kick;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						break;
					case ST_PUNCH_NEUTRAL_JUMP2:
						current_animation = &jump_neutral_punch;	
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_neutral_logic();
						break;
					case ST_PUNCH_MEDIUM_NEUTRAL_JUMP2:
						current_animation = &jump_forward_punch_medium;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_neutral_logic();
						break;
					case ST_PUNCH_HARD_NEUTRAL_JUMP2:
						current_animation = &jump_neutral_punch_hard;
						onAir == true;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						jump_neutral_logic();	
						break;
					case ST_PUNCH_FORWARD_JUMP2:					
						current_animation = &jump_forward_punch;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_forward_logic();
						break;
					case ST_PUNCH_MEDIUM_FORWARD_JUMP2:
						current_animation = &jump_forward_punch_medium;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_forward_logic();
						break;
					case ST_PUNCH_HARD_FORWARD_JUMP2:
						current_animation = &jump_forward_punch_hard;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_forward_logic();
						break;
					case ST_KICK_FORWARD_JUMP2:
						current_animation = &jump_forward_kick;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_forward_logic();
						break;
					case ST_KICK_MEDIUM_FORWARD_JUMP2:
						current_animation = &jump_forward_kick_medium;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_forward_logic();
						break;
					case ST_KICK_HARD_FORWARD_JUMP2:
						current_animation = &jump_forward_kick_hard;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_forward_logic();
						break;
					case ST_PUNCH_BACKWARD_JUMP2:
						current_animation = &jump_backward_punch;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_backward_logic();
						break;
					case ST_PUNCH_MEDIUM_BACKWARD_JUMP2:
						current_animation = &jump_backward_punch_medium;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_backward_logic();
						break;
					case ST_PUNCH_HARD_BACKWARD_JUMP2:
						current_animation = &jump_backward_punch_hard;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_backward_logic();
						break;
					case ST_KICK_BACKWARD_JUMP2:
						current_animation = &jump_backward_kick;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_backward_logic();
						break;
					case ST_KICK_MEDIUM_BACKWARD_JUMP2:
						current_animation = &jump_backward_kick_medium;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_backward_logic();
						break;
					case ST_KICK_HARD_BACKWARD_JUMP2:
						current_animation = &jump_backward_kick_hard;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						onAir == true;
						jump_backward_logic();
						break;
					case ST_KICK_STANDING2:
						current_animation = &kick;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						break;
					case ST_PUNCH_MEDIUM2:
						current_animation = &punch_medium;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						break;
					case ST_PUNCH_HARD2:						
						current_animation = &punch_hard;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						break;
					case ST_KICK_MEDIUM_STANDING2:
						current_animation = &kick_medium;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						break;
					case ST_KICK_HARD_STANDING2:
						current_animation = &kick_hard;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						break;
					case ST_LIGHTNINGKICK2:
						current_animation = &LightningKick;	
						App->audio->PlayChunk(LightningKick_effect, 3);
						break;
					case ST_WHIRLWIND2:
						current_animation = &WhirlwindKick;
						App->audio->PlayChunk(WhirlwindKick_effect, 1);
						if (wkcounter < 15) {
							wkcounter++;
						}
						if (wkcounter >= 15 && wkcounter < 80) {
							wkcounter++;
							whirlwindMove = true;
						}
						if (whirlwindMove  ) {
							if (abs(App->chunli2->position.x - position.x) >= 120) {
								if (position.x < App->chunli2->position.x) { position.x += 3; }
								if (position.x > App->chunli2->position.x) { position.x -= 3; }
							}
							
							position.y = 190;
						}
						if (wkcounter >= 60) {
							whirlwindMove = false;
							position.y = 220;
						}
						break;
					case ST_KICK_NEUTRAL_JUMP2:
						current_animation = &jump_neutral_kick;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						jump_neutral_logic();
						break;
					case ST_KICK_MEDIUM_NEUTRAL_JUMP2:
						current_animation = &jump_neutral_kick_medium;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						jump_neutral_logic();
						break;
					case ST_KICK_HARD_NEUTRAL_JUMP2:
						current_animation = &jump_neutral_kick_hard;
						if (hit_started == 0) {
							App->audio->PlayChunk(wind, 1);
							hit_started++;
						}
						jump_neutral_logic();
						break;
					case ST_DAMAGE2:
						current_animation = &damage;
						if (current_animation->current_frame != 0)
						{
							if (position.x > App->chunli2->position.x)
								position.x += 1;
							else
								position.x -= 1;
						}
						move = false;
						break;
					case ST_DAMAGE_HARD2:
						current_animation = &damage2;

						if (current_animation->current_frame != 0)
						{
							if (position.x > App->chunli2->position.x)
								position.x += 3;
							else
								position.x -= 3;
						}
						move = false;
						break;
					case ST_DAMAGE_FALL2:
						current_animation = &damage3;
						damage_received = 0;
						if(position.x < App->chunli2->position.x)
						position.x -= 3;
						else
							position.x += 3;						
						if (SDL_GetTicks() - dmg_fall_timer <= JUMP_TIME2 /4)  {
							position.y -= 12;

						}		
						if (SDL_GetTicks() - dmg_fall_timer >= JUMP_TIME2 /4 && SDL_GetTicks() - dmg_fall_timer <= JUMP_TIME2 / 2) {
							position.y += 14;
						}
						if (position.y >= 220) {
							position.y = 220;
						}	
						move = false;						
						break;
					case ST_DAMAGE_CROUCH2:
						current_animation = &damage4;
						damage_received = 0;
						break;						
					case ST_DAMAGE_AIR2:						
						current_animation = &damage5;
						if (position.x < App->chunli2->position.x)
							position.x -= 2;
						else
							position.x += 2;
							if (SDL_GetTicks() - jump_timer > JUMP_TIME2 / 2) {
								position.y += 4;
							}				
						if (SDL_GetTicks() - jump_timer >= JUMP_TIME2 / 1.28) {
							position.y += 5;
						}
						if (position.y >= 220) {
							position.y = 220;
						}										
						move = false;
						break;
					case ST_BLOCK2:
						block_damage = 0;					
						current_animation = &block_standing;
						break;					
					case ST_BLOCK_CROUCH2:
						block_damage = 0;
						current_animation = &block_crouch;
						break;
					case ST_VICTORY2:
						if (App->chunli2->state == ST_LOSE)
							App->UI->Resultinfo = 1;

						
						if (victorycount == 0)
							victorycount++;

						if (sound < 30) {
							if (sound == 1)
								App->audio->PlayChunk(syou, 1);
							sound++;
						}
						else if (sound == 30) {
							App->audio->PlayChunk(swin, 1);
							sound++;
						}
						current_animation = &win1;
						break;
					case ST_VICTORY2_2:

						if (App->chunli2->state == ST_LOSE) {
							App->UI->Resultinfo = 1;
							current_animation = &win2;
						}		

						

						if (WinSoundPlayed == false) {
							App->audio->PlayChunk(win_sound, 1);
							WinSoundPlayed = true;
						}
						
						if (sound < 30) {
							if (sound == 1)
								App->audio->PlayChunk(syou, 1);
							sound++;
						}
						else if (sound == 30) {
							App->audio->PlayChunk(swin, 1);
							sound++;
						}
						if (win2.current_frame < 2) {
							position.y -= 2;
						}
						else if (win2.current_frame > 2 && position.y<=220) {
							position.y += 2;
						}
						break;
					case ST_LOSE2:	

						ignore = 1;

						if (SDL_GetTicks() - lose_timer >2000 && App->chunli2->victorycount==0)
							App->chunli2->win = 1;
						else if (SDL_GetTicks() - lose_timer > 2000 && App->chunli2->victorycount == 1)
							App->chunli2->win = 2;
						current_animation = &damage3;
						if (DeathSoundPlayed == false)
						{
							App->audio->PlayChunk(death_sound, 1);
							DeathSoundPlayed = true;
						}

						if (SDL_GetTicks() - lose_timer > 9000 && App->chunli2->state==ST_VICTORY)
						App->fade->FadeToBlack(App->combo, App->combo, 2.0f);

						else if (SDL_GetTicks() - lose_timer > 9000 && App->chunli2->state == ST_VICTORY2_) {
							App->audio->StopMusic(250);
							App->fade->FadeToBlack(App->scene_dhalsim, App->lose_scene, 2.0f);
						}
						
						if (position.x < App->chunli2->position.x)
							position.x -= 3;
						else
							position.x += 3;

						if (onAir && position.y <= 225) {
							position.y += 5;
						}

						else if (SDL_GetTicks() - lose_timer < 450 && position.y==220) {
							position.y -= 6;
						}
						else if (position.y <= 225) {
							position.y += 5;
						}
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

	if (position.y == 220 ) {
		speedX = 1;
		speedY = 1;
	}

	if (position.x+50 <= App->scene_dhalsim->background.x - 12) {

		position.x = App->scene_dhalsim->background.x - 12 -50;
		leftLimit = true;
		
	}
	else {
		leftLimit = false;
		
	}

	if (position.x >= (App->scene_dhalsim->background.x + App->scene_dhalsim->background.w) - 90) {
		position.x = (App->scene_dhalsim->background.x + App->scene_dhalsim->background.w) - 90 ;
		RightLimit = true;
	}
	else {
		RightLimit = false;
	}
	
	if (abs(App->chunli2->position.x - position.x) >= SCREEN_WIDTH - 10 && position.x<App->chunli2->position.x) {
		App->chunli2->position.x = position.x + SCREEN_WIDTH - 10;
		position.x = App->chunli2->position.x -SCREEN_WIDTH + 10;		
		
	}
	
	if (abs(App->chunli2->position.x - position.x) >= SCREEN_WIDTH - 130 && position.x > App->chunli2->position.x) {

		App->chunli2->position.x = position.x - SCREEN_WIDTH + 130;
		position.x = App->chunli2->position.x + SCREEN_WIDTH - 130;
	}

}

void ModuleChunLi::colliders_and_blit(Animation* current_animation) {

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
		if (!GodMode) {

			if (position.x < App->chunli2->position.x)
				colliders[i] = App->collision->AddCollider({ position.x + PivotX + r.x , position.y + PivotY - r.h - r.y,r.w,r.h }, current_animation->type[i], current_animation->callback[i]);

			if (position.x > App->chunli2->position.x )
				colliders[i] = App->collision->AddCollider({ position.x - (r.w - PivotX) + 50 - r.x , position.y - r.h + PivotY - r.y,r.w,r.h }, current_animation->type[i], current_animation->callback[i]);
		}
		
	}

	r = current_animation->GetCurrentFrame();
	SDL_Rect shadowrect = { 6,8,71,15 };
	if (position.x + PivotX < App->chunli2->position.x && (!RightLimit || position.y != 220) || leftLimit) {

		App->render->Blit(shadow, position.x+PivotX, 207, &shadowrect);
		App->render->Blit(shadow, App->chunli2->position.x - App->chunli2->PivotX - 8, 207, &shadowrect);
		App->render->Blit(graphics, position.x + PivotX, position.y - r.h, &r);
	}
	if (position.x + PivotX > App->chunli2->position.x && !leftLimit || (RightLimit && position.y == 220)) {

		App->render->Blit(shadow, position.x - (shadowrect.w - PivotX) + 50, 207, &shadowrect);
		App->render->Blit(shadow, App->chunli2->position.x - (shadowrect.w + App->chunli2->PivotX) + 65, 207, &shadowrect);		
		App->render->BlitSym(graphics, position.x - (r.w - PivotX)+ 50, position.y - r.h, &r);
	}

}

void ModuleChunLi::OnCollision(Collider* c1, Collider* c2) {

	
	if (c1->type == COLLIDER_PLAYER && (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_NONE))
	{		
		
		if (state == ST_IDLE2 ) {
			if (position.x < App->chunli2->position.x)
				position.x -= 1;
			else if (position.x > App->chunli2->position.x)
				position.x += 1;
					
		}

		else if (App->chunli2->RightLimit && RightLimit) {
			position.x -= 2;
		}
		
		else if (App->chunli2->RightLimit == true && state == ST_WALK_FORWARD2) {
			position.x -= 2;
		}
	
		else {
			move = false;
		}
	}	


	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT)
	{
		if (state == ST_WALK_BACKWARD2 && App->chunli2->position.x > position.x && !App->chunli2->crouchAttack) {
			block_damage = 1;
			App->particle->AddParticle(App->particle->hit, position.x + PivotX + 25, position.y - 70, COLLIDER_NONE, 0);

		}
		else if (state == ST_WALK_FORWARD2 && App->chunli2->position.x < position.x  && !App->chunli2->crouchAttack) {
			block_damage = 1;
			App->particle->AddParticle(App->particle->hit, position.x + PivotX , position.y - 70, COLLIDER_NONE, 0);

		}
		else if (state == ST_CROUCH2 && (left || left1 || left2) && App->chunli2->position.x > position.x) {
			block_damage = 2;
			App->particle->AddParticle(App->particle->hit, position.x + PivotX + 25, position.y - 70, COLLIDER_NONE, 0);
		}

		else if (state == ST_CROUCH2 && (right || right1 || right2) && App->chunli2->position.x < position.x) {
			block_damage = 2;
			App->particle->AddParticle(App->particle->hit, position.x + PivotX, position.y - 70, COLLIDER_NONE, 0);
		}

		else {

			int aux = life;
			
			
			if (!damage_received) {
				
				life = aux - App->chunli2->dmg;
								
			}


			 
				if (state == ST_WALK_BACKWARD2 || state == ST_WALK_FORWARD2 || state == ST_IDLE2) {
					if (App->chunli2->state == ST_KICK_HARD_CROUCH || App->chunli2->state == ST_KICK_HARD_NEUTRAL_JUMP) {
						
						damage_received = 3;
						App->slow->StartSlowdown(JUMP_TIME2, 50);

					}
					else if (App->chunli2->state == ST_WHIRLWIND) {
						
						damage_received = 2;
						App->slow->StartSlowdown(200, 50);
						

					}
					else if (App->chunli2->state == ST_KICK_HARD_STANDING) {
						
						damage_received = 2;
						App->slow->StartSlowdown(400, 50);
					}
					else {
						
						damage_received = 1;
					}

				}
				else if (state == ST_CROUCH2) {
					
					damage_received = 4;
				}

				else {
				
					damage_received = 5;
				
			}
			
		}

		if(!block_damage)
			App->particle->AddParticle(App->particle->hit, position.x + PivotX, position.y - 70, COLLIDER_NONE, 0);
		App->audio->PlayChunk(medium_damage, 1);
	}
}

bool ModuleChunLi::external_input(p2Qeue<chunli_inputs2>& inputs)
{	
	
	if (App->chunli2->life > 0) {
		//Key up
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_UP) {
			inputs.Push(IN_CROUCH_UP2);
		}
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_UP) {
			return false;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_UP) {
			left = false;
			inputs.Push(IN_LEFT_UP2);

		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_UP) {
			right = false;
			inputs.Push(IN_RIGHT_UP2);

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

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_DOWN || App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT) {
			inputs.Push(IN_JUMP2);
		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_DOWN || App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT) {
			inputs.Push(IN_CROUCH_DOWN2);
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_DOWN || App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT) {
			left = true;
			inputs.Push(IN_LEFT_DOWN2);
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_DOWN || App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT) {
			right = true;
			inputs.Push(IN_RIGHT_DOWN2);
		}
		if (App->input->keyboard[SDL_SCANCODE_X] == KEY_DOWN) {
			inputs.Push(IN_X2);
		}
		if (App->input->keyboard[SDL_SCANCODE_C] == KEY_DOWN) {
			inputs.Push(IN_C2);
		}
		if (App->input->keyboard[SDL_SCANCODE_V] == KEY_DOWN) {
			inputs.Push(IN_LIGHTINGKICK2);
		}
		if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN) {
			inputs.Push(IN_1_2);
		}
		if (App->input->keyboard[SDL_SCANCODE_2] == KEY_DOWN) {
			inputs.Push(IN_2_2);
		}
		if (App->input->keyboard[SDL_SCANCODE_3] == KEY_DOWN) {
			inputs.Push(IN_3_2);
		}
		if (App->input->keyboard[SDL_SCANCODE_4] == KEY_DOWN) {
			inputs.Push(IN_4_2);
		}

		if (App->input->keyboard[SDL_SCANCODE_5] == KEY_DOWN) {
			inputs.Push(IN_WHIRLWINDKICK2);
		}


		//Controller

		if (App->input->Gamepad == true) {
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_UP) {
				return false;
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_UP) {
				return false;
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_UP) {
				return false;
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_UP) {
				return false;
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_UP) {
				inputs.Push(IN_CROUCH_UP2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_UP) {
				left1 = false;
				inputs.Push(IN_LEFT_UP2);;
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_UP) {
				right1 = false;
				inputs.Push(IN_RIGHT_UP2);
			}


			if (App->combo->CheckPunchP1() == true) {
				inputs.Push(IN_X2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
				inputs.Push(IN_C2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_X] == KEY_DOWN) {
				inputs.Push(IN_1_2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_LEFTSHOULDER] == KEY_DOWN) {
				inputs.Push(IN_2_2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN) {
				inputs.Push(IN_3_2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				inputs.Push(IN_4_2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_REPEAT) {
				inputs.Push(IN_JUMP2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_REPEAT) {
				inputs.Push(IN_CROUCH_DOWN2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_REPEAT) {
				left1 = true;
				inputs.Push(IN_LEFT_DOWN2);
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_REPEAT) {
				right1 = true;
				inputs.Push(IN_RIGHT_DOWN2);
			}

			if (App->combo->CheckLightingKickP1() == true) {
				inputs.Push(IN_LIGHTINGKICK2);
			}
			if (App->combo->CheckWhirlwindKickP1() == true) {
				inputs.Push(IN_WHIRLWINDKICK2);
			}

			//Axis
			if (App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTY] < JOYSTICK_DEAD_ZONE_NEGATIVE) {
				inputs.Push(IN_JUMP2);
			}
			if (App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTY] > JOYSTICK_DEAD_ZONE) {
				inputs.Push(IN_CROUCH_DOWN2);
			}
			if (App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTX] < JOYSTICK_DEAD_ZONE_NEGATIVE) {
				left2 = true;
				inputs.Push(IN_LEFT_DOWN2);
			}
			if (App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTX] > JOYSTICK_DEAD_ZONE) {
				right2 = true;
				inputs.Push(IN_RIGHT_DOWN2);
			}


			if (App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTY] > JOYSTICK_DEAD_ZONE_NEGATIVE && App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTY] < JOYSTICK_DEAD_ZONE) {

			}
			if (App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTY] < JOYSTICK_DEAD_ZONE && App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTY] > JOYSTICK_DEAD_ZONE_NEGATIVE) {
				inputs.Push(IN_CROUCH_UP2);
			}
			if (App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTX] > JOYSTICK_DEAD_ZONE_NEGATIVE && App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTX] < JOYSTICK_DEAD_ZONE) {
				left2 = false;
				inputs.Push(IN_LEFT_UP2);
			}
			if (App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTX] < JOYSTICK_DEAD_ZONE && App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTX] > JOYSTICK_DEAD_ZONE_NEGATIVE) {
				right2 = false;
				inputs.Push(IN_RIGHT_UP2);
			}
		}
	}
	
	if (damage_received==1) {
		inputs.Push(IN_DAMAGE2);
	}
	if (damage_received == 2) {
		inputs.Push(IN_DAMAGE_HARD2);
	}
	if (damage_received == 3) {
		inputs.Push(IN_DAMAGE_FALL2);
	}
	if (damage_received == 4) {
		inputs.Push(IN_DAMAGE_CROUCH2);
	}
	if (damage_received == 5) {
		inputs.Push(IN_DAMAGE_AIR2);
	}

	if (block_damage == 1) {
		inputs.Push(IN_BLOCK2);
	}
	if (block_damage == 2) {
		inputs.Push(IN_BLOCK_CROUCH2);
	}
	
	if (win==1 && App->chunli2->state == ST_LOSE) {
		inputs.Push(IN_VICTORY2);
		win = 0;
	}

	if (win == 2 && App->chunli2->state == ST_LOSE) {
		inputs.Push(IN_VICTORY2_2);
		win = 0;
	}

	if (lose && state!=ST_LOSE2) {
		inputs.Push(IN_LOSE2);
		App->slow->StartSlowdown(2000, 50);
		lose = false;
	}
	

	//OMAY GOT, THERE IS NO LOGC HOW CAN THIS BE THIS POSSIBLE, WHAT A MASTER SKILL OF PROGRAMATION

	return true;
}

void ModuleChunLi::internal_input(p2Qeue<chunli_inputs2>& inputs)
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
			hadouken_timer = 0;
			inputs.Push(IN_LIGHTNINGKICK_FINISH2);
			
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

	if (punch_medium_timer > 0)
	{
		if (SDL_GetTicks() - punch_medium_timer > PUNCH_MEDIUM_TIME2)
		{
			inputs.Push(IN_PUNCH_MEDIUM_FINISH2);
			punch_medium_timer = 0;
		}
	}

	if (punch_hard_timer > 0)
	{
		if (SDL_GetTicks() - punch_hard_timer > PUNCH_HARD_TIME2)
		{
			inputs.Push(IN_PUNCH_HARD_FINISH2);
			punch_hard_timer = 0;
		}
	}

	if (kick_medium_timer > 0)
	{
		if (SDL_GetTicks() - kick_medium_timer > KICK_MEDIUM_TIME2)
		{
			inputs.Push(IN_KICK_MEDIUM_FINISH2);
			kick_medium_timer = 0;
		}
	}

	if (kick_hard_timer > 0)
	{
		if (SDL_GetTicks() - kick_hard_timer > JUMP_TIME2)
		{
			inputs.Push(IN_KICK_HARD_FINISH2);
			kick_hard_timer = 0;
		}
	}

	if (dmg_timer > 0)
	{
		if (SDL_GetTicks() - dmg_timer > DMG_TIME2)
		{
			inputs.Push(IN_DAMAGE_FINISH2);
			dmg_timer = 0;
		}
	}

	if (dmg_hard_timer > 0)
	{
		if (SDL_GetTicks() - dmg_hard_timer > DMG_TIME2)
		{
			inputs.Push(IN_DAMAGE_FINISH2);
			dmg_hard_timer = 0;
		}
	}

	if (dmg_fall_timer > 0)
	{
		if (SDL_GetTicks() - dmg_fall_timer > JUMP_TIME2)
		{
			inputs.Push(IN_DAMAGE_FINISH2);
			dmg_fall_timer = 0;
		}
	}

	if (block_timer > 0)
	{
		if (SDL_GetTicks() - block_timer > PUNCH_TIME2)
		{
			inputs.Push(IN_BLOCK_FINISH2);
			block_timer = 0;
		}
	}

	if (whirlwind_timer > 0)
	{
		if (SDL_GetTicks() - whirlwind_timer > WHIRLWINDKICK_TIME2)
		{
			inputs.Push(IN_WHIRLWINDKICK2_FINISH2);
			whirlwind_timer = 0;
		}
	}

	if (victory_timer > 0)
	{
		victoryRound1 = true;
		if (SDL_GetTicks() - victory_timer > 8000)
		{
			inputs.Push(IN_VICTORY_FINISH2);
			victory_timer = 0;
			victoryRound1 = false;
		}
	}
	if (victory2_timer > 0)
	{
		victoryRound2 = true;
		
		if (SDL_GetTicks() - victory2_timer > 8000)
		{
			inputs.Push(IN_VICTORY2_FINISH_2);
			victory2_timer = 0;
			victoryRound2 = false;
		}
	}

	if (lose_timer > 0)
	{
		if (SDL_GetTicks() - lose_timer > 10000)
		{
			inputs.Push(IN_LOSE_FINISH2);
			lose_timer = 0;
		}
	}


	

}

void ModuleChunLi::ResetPlayer() {

	life = 1000;
	position.x = 180; //Returns to its original position
	position.y = 220;
	state = ST_IDLE2;
	App->UI->Resultinfo == 0;
	if (App->chunli2->position.x != 300 || App->chunli2->life != 1000) {
		ActiveDeath = 0;
		App->chunli2->ResetPlayer();
		App->UI->time = 99;
		App->UI->Counter1 = 9;
		App->UI->Counter2 = 9;
		App->UI->Resultinfo = 0;
	}
	
}

chunli_states2 ModuleChunLi:: process_fsm(p2Qeue<chunli_inputs2>& inputs)
{
	static chunli_states2 state = ST_IDLE2;
	chunli_inputs2 last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE2:
		{
			if (hit_conected > 0) {
				hit_conected = 0;
			}
			if (hit_started > 0) {
				hit_started = 0;
			}
			switch (last_input)

			{
			case IN_RIGHT_DOWN2: state = ST_WALK_FORWARD2; break;
			case IN_LEFT_DOWN2: state = ST_WALK_BACKWARD2; break;
			case IN_JUMP2: state = ST_JUMP_NEUTRAL2; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; break;
			case IN_X2: state = ST_PUNCH_STANDING2; punch_timer = SDL_GetTicks();  break;
			case IN_C2: state = ST_KICK_STANDING2; kick_timer = SDL_GetTicks(); break;
			case IN_LIGHTINGKICK2: state = ST_LIGHTNINGKICK2; hadouken_timer = SDL_GetTicks(); break;
			case IN_1_2: state = ST_PUNCH_MEDIUM2; punch_medium_timer = SDL_GetTicks(); break;
			case IN_2_2: state = ST_PUNCH_HARD2; punch_hard_timer= SDL_GetTicks(); break;
			case IN_3_2: state = ST_KICK_MEDIUM_STANDING2; kick_medium_timer = SDL_GetTicks(); break;
			case IN_4_2: state = ST_KICK_HARD_STANDING2; kick_hard_timer = SDL_GetTicks(); break;
			case IN_DAMAGE2: state = ST_DAMAGE2; dmg_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_HARD2: state = ST_DAMAGE_HARD2; dmg_hard_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_FALL2: state = ST_DAMAGE_FALL2; dmg_fall_timer = SDL_GetTicks(); break;
			case IN_WHIRLWINDKICK2: state = ST_WHIRLWIND2; whirlwind_timer = SDL_GetTicks(); break;
			case IN_VICTORY2: state = ST_VICTORY2; victory_timer = SDL_GetTicks();  break;
			case IN_VICTORY2_2: state = ST_VICTORY2_2; victory2_timer = SDL_GetTicks();  break;
			case IN_LOSE2: state = ST_LOSE2; lose_timer = SDL_GetTicks();  break;
			
			}
		}
		break;

		case ST_WALK_FORWARD2:
		{
			if (hit_conected > 0) {
				hit_conected = 0;
			}
			if (hit_started> 0) {
				hit_started = 0;
			}
			switch (last_input)
			{
			case IN_RIGHT_UP2: state = ST_IDLE2; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE2; break;
			case IN_JUMP2: state = ST_JUMP_FORWARD2; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; break;
			case IN_X2: state = ST_PUNCH_STANDING2; punch_timer = SDL_GetTicks();  break;
			case IN_C2: state = ST_KICK_STANDING2; kick_timer = SDL_GetTicks(); break;
			case IN_LIGHTINGKICK2: state = ST_LIGHTNINGKICK2; hadouken_timer = SDL_GetTicks(); break;
			case IN_1_2: state = ST_PUNCH_MEDIUM2; punch_medium_timer = SDL_GetTicks(); break;
			case IN_2_2: state = ST_PUNCH_HARD2; punch_hard_timer = SDL_GetTicks(); break;
			case IN_3_2: state = ST_KICK_MEDIUM_STANDING2; kick_medium_timer= SDL_GetTicks(); break;
			case IN_4_2: state = ST_KICK_HARD_STANDING2; kick_hard_timer = SDL_GetTicks(); break;
			case IN_DAMAGE2: state = ST_DAMAGE2; dmg_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_HARD2: state = ST_DAMAGE_HARD2; dmg_hard_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_FALL2: state = ST_DAMAGE_FALL2; dmg_fall_timer = SDL_GetTicks(); break;
			case IN_BLOCK2: state = ST_BLOCK2; block_timer = SDL_GetTicks(); break;
			case IN_WHIRLWINDKICK2: state = ST_WHIRLWIND2; whirlwind_timer = SDL_GetTicks(); break;
			case IN_VICTORY2: state = ST_VICTORY2; victory_timer = SDL_GetTicks();  break;
			case IN_VICTORY2_2: state = ST_VICTORY2_2; victory2_timer = SDL_GetTicks();  break;
			case IN_LOSE2: state = ST_LOSE2; lose_timer = SDL_GetTicks();  break;
			}
		}
		break;

		case ST_WALK_BACKWARD2:
		{
			if (hit_conected > 0) {
				hit_conected = 0;
			}
			if (hit_started> 0) {
				hit_started = 0;
			}
			switch (last_input)
			{
			case IN_LEFT_UP2: state = ST_IDLE2; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE2; break;
			case IN_JUMP2: state = ST_JUMP_BACKWARD2; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; break;
			case IN_X2: state = ST_PUNCH_STANDING2; punch_timer = SDL_GetTicks();  break;
			case IN_C2: state = ST_KICK_STANDING2; kick_timer = SDL_GetTicks(); break;
			case IN_LIGHTINGKICK2: state = ST_LIGHTNINGKICK2; hadouken_timer = SDL_GetTicks(); break;
			case IN_1_2: state = ST_PUNCH_MEDIUM2; punch_medium_timer = SDL_GetTicks(); break;
			case IN_2_2: state = ST_PUNCH_HARD2; punch_hard_timer = SDL_GetTicks(); break;
			case IN_3_2: state = ST_KICK_MEDIUM_STANDING2; kick_medium_timer = SDL_GetTicks(); break;
			case IN_4_2: state = ST_KICK_HARD_STANDING2; kick_hard_timer = SDL_GetTicks(); break;
			case IN_DAMAGE2: state = ST_DAMAGE2; dmg_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_HARD2: state = ST_DAMAGE_HARD2; dmg_hard_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_FALL2: state = ST_DAMAGE_FALL2; dmg_fall_timer = SDL_GetTicks(); break;
			case IN_BLOCK2: state = ST_BLOCK2; block_timer = SDL_GetTicks(); break;
			case IN_WHIRLWINDKICK2: state = ST_WHIRLWIND2; whirlwind_timer = SDL_GetTicks(); break;
			case IN_VICTORY2: state = ST_VICTORY2; victory_timer = SDL_GetTicks();  break;
			case IN_VICTORY2_2: state = ST_VICTORY2_2; victory2_timer = SDL_GetTicks();  break;
			case IN_LOSE2: state = ST_LOSE2; lose_timer = SDL_GetTicks();  break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL2:
		{
			if (hit_conected > 0) {
				hit_conected = 0;
			}
			if (hit_started > 0) {
				hit_started = 0;
			}
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_NEUTRAL_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_1_2: state = ST_PUNCH_MEDIUM_NEUTRAL_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_2_2: state = ST_PUNCH_HARD_NEUTRAL_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_C2: state = ST_KICK_NEUTRAL_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_3_2:state = ST_KICK_MEDIUM_NEUTRAL_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_4_2:state = ST_KICK_HARD_NEUTRAL_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_AIR2:state = ST_DAMAGE_AIR2; dmg_fall_timer = SDL_GetTicks(); break;
			case IN_LOSE2: state = ST_LOSE2; lose_timer = SDL_GetTicks();  break;
			

			}
		}
		break;

		case ST_JUMP_FORWARD2:
		{
			if (hit_conected > 0) {
				hit_conected = 0;
			}
			if (hit_started > 0) {
				hit_started = 0;
			}
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_FORWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_C2: state = ST_KICK_FORWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_1_2: state = ST_PUNCH_MEDIUM_FORWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_2_2 : state = ST_PUNCH_HARD_FORWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;	
			case IN_3_2: state = ST_KICK_MEDIUM_FORWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_4_2: state = ST_KICK_HARD_FORWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_AIR2:state = ST_DAMAGE_AIR2; dmg_fall_timer = SDL_GetTicks(); break;
			case IN_LOSE2: state = ST_LOSE2; lose_timer = SDL_GetTicks();  break;
				
			}
		}
		break;

		case ST_JUMP_BACKWARD2:
		{
			if (hit_conected > 0) {
				hit_conected = 0;
			}
			if (hit_started > 0) {
				hit_started = 0;
			}
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_BACKWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_C2: state = ST_KICK_BACKWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_1_2: state = ST_PUNCH_MEDIUM_BACKWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_2_2: state = ST_PUNCH_HARD_BACKWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_3_2: state = ST_KICK_MEDIUM_BACKWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_4_2: state = ST_KICK_HARD_BACKWARD_JUMP2; punch_neutral_jump_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_AIR2:state = ST_DAMAGE_AIR2; dmg_fall_timer = SDL_GetTicks(); break;
			case IN_LOSE2: state = ST_LOSE2; lose_timer = SDL_GetTicks();  break;
			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(light_damage, 1);
				App->UI->scoreP1 += 200;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_NEUTRAL2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_PUNCH_MEDIUM_NEUTRAL_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(medium_damage, 1);
				App->UI->scoreP1 += 200;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_NEUTRAL2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_PUNCH_HARD_NEUTRAL_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(medium_damage, 1);
				App->UI->scoreP1 += 200;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_NEUTRAL2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_KICK_NEUTRAL_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(light_damage, 1);
				App->UI->scoreP1 += 200;
				hit_conected++;
			}

			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_NEUTRAL2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2:
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				} 
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_KICK_MEDIUM_NEUTRAL_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(medium_damage, 1);
				App->UI->scoreP1 += 200;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_NEUTRAL2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				} 
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_KICK_HARD_NEUTRAL_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(high_damage, 1);
				App->UI->scoreP1 += 200;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_NEUTRAL2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				state = ST_IDLE2; break;
			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(light_damage, 1);
				App->UI->scoreP1 += 100;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: 
				state = ST_JUMP_FORWARD2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_PUNCH_MEDIUM_FORWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(medium_damage, 1);
				App->UI->scoreP1 += 100;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_FORWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2:
				state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_PUNCH_HARD_FORWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(high_damage, 1);
				App->UI->scoreP1 += 100;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_FORWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_KICK_FORWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(light_damage, 1);
				App->UI->scoreP1 += 100;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_FORWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_KICK_MEDIUM_FORWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(medium_damage, 1);
				App->UI->scoreP1 += 100;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_FORWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_KICK_HARD_FORWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(high_damage, 1);
				App->UI->scoreP1 += 100;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_FORWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_PUNCH_BACKWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(light_damage, 1);
				App->UI->scoreP1 += 100;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: 
				state = ST_JUMP_BACKWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;
		case ST_PUNCH_MEDIUM_BACKWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(medium_damage, 1);
				App->UI->scoreP1 += 100;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_BACKWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;
		case ST_PUNCH_HARD_BACKWARD_JUMP2:
		{	
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(high_damage, 1);
					App->UI->scoreP1 += 100;
					hit_conected++;
				}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_BACKWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_KICK_BACKWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(light_damage, 1);
					App->UI->scoreP1 += 100;
					hit_conected++;
				}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_BACKWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;
		case ST_KICK_MEDIUM_BACKWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(light_damage, 1);
					App->UI->scoreP1 += 100;
					hit_conected++;
				}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_BACKWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2:
				state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;
		case ST_KICK_HARD_BACKWARD_JUMP2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(high_damage, 1);
					App->UI->scoreP1 += 100;
					hit_conected++;
				}
			switch (last_input)
			{
			case IN_PUNCH_FINISH2:
				state = ST_JUMP_BACKWARD2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			case IN_JUMP_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;
		case ST_PUNCH_STANDING2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(light_damage, 1);
					App->UI->scoreP1 += 100;
					hit_conected++;
				}
			
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: 
				state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_CROUCH2:
		{
			if (hit_conected > 0) {
				hit_conected = 0;
			}
			if (hit_started > 0) {
				hit_started = 0;
			}
			switch (last_input)
			{
			case IN_CROUCH_UP2: state = ST_IDLE2; break;
			case IN_JUMP_AND_CROUCH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_CROUCH2; punch_hard_timer = SDL_GetTicks(); break;
			case IN_C2: state = ST_KICK_CROUCH2; punch_medium_timer = SDL_GetTicks(); break;
			case IN_1_2: state = ST_PUNCH_MEDIUM_CROUCH2; punch_hard_timer = SDL_GetTicks(); break;
			case IN_2_2: state = ST_PUNCH_HARD_CROUCH2; punch_hard_timer = SDL_GetTicks(); break;
			case IN_3_2: state = ST_KICK_MEDIUM_CROUCH2; punch_medium_timer = SDL_GetTicks(); break;
			case IN_4_2: state = ST_KICK_HARD_CROUCH2; kick_hard_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_CROUCH2: state = ST_DAMAGE_CROUCH2;dmg_hard_timer = SDL_GetTicks(); break;
			case IN_BLOCK_CROUCH2: state = ST_BLOCK_CROUCH2;block_timer = SDL_GetTicks(); break;
			case IN_VICTORY2: state = ST_VICTORY2; victory_timer = SDL_GetTicks();  break;
			case IN_VICTORY2_2: state = ST_VICTORY2_2; victory2_timer = SDL_GetTicks();  break;
			case IN_LOSE2: state = ST_LOSE2; lose_timer = SDL_GetTicks();  break;
			}
		}
		break;
		
		case ST_PUNCH_CROUCH2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(light_damage, 1);
					App->UI->scoreP1 += 100;
					hit_conected++;
				}
			switch (last_input)
			{
			case IN_PUNCH_HARD_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
					state = ST_CROUCH2;
				else
					state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				crouchAttack = false;
				break;
			}
		}
		break;
		case ST_PUNCH_MEDIUM_CROUCH2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(medium_damage, 1);
					App->UI->scoreP1 += 200;
					hit_conected++;
				}
			switch (last_input)
			{
			case IN_PUNCH_HARD_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
					state = ST_CROUCH2;
				else
					state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				crouchAttack = false;
				break;
			}
		}
		break;
		case ST_PUNCH_HARD_CROUCH2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(high_damage, 1);
					App->UI->scoreP1 += 300;
					hit_conected++;
				}
			switch (last_input)
			{
			case IN_PUNCH_HARD_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
					state = ST_CROUCH2;
				else
					state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				crouchAttack = false;
				break;
			}
		}
		break;
		case ST_KICK_CROUCH2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(light_damage, 1);
					App->UI->scoreP1 += 100;
					hit_conected++;
				}
			switch (last_input)
			{
				case IN_PUNCH_MEDIUM_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
					state = ST_CROUCH2;
				else
					state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				crouchAttack = false;
				break;
			}
		}
		break;
		case ST_KICK_MEDIUM_CROUCH2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(medium_damage, 1);
					App->UI->scoreP1 += 200;
					hit_conected++;
				}
			switch (last_input)
			{
			case IN_PUNCH_MEDIUM_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
					state = ST_CROUCH2;
				else
					state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				crouchAttack = false;
				break;
			}
		}
		break;
		case ST_KICK_HARD_CROUCH2:
		{
				if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
					App->audio->PlayChunk(high_damage, 1);
					App->UI->scoreP1 += 300;
					hit_conected++;
				}
			switch (last_input)
			{
			case IN_KICK_HARD_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
					state = ST_CROUCH2;
				else
					state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;
		case ST_KICK_STANDING2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
					{
						App->audio->PlayChunk(light_damage, 1);
						App->UI->scoreP1 += 100;
						hit_conected++;
					}
			switch (last_input)
			{
				case IN_KICK_FINISH2: 
					state = ST_IDLE2; 
					if (hit_conected > 0) {
						hit_conected = 0;
					}
					if (hit_started > 0) {
						hit_started = 0;
					}
					break;
			}
		}
		break;

		case ST_KICK_MEDIUM_STANDING2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
					{
						App->audio->PlayChunk(medium_damage, 1);
						App->UI->scoreP1 += 200;
						hit_conected++;
					}
			switch (last_input)
			{
				case IN_KICK_MEDIUM_FINISH2: 
					state = ST_IDLE2; 
					if (hit_conected > 0) {
						hit_conected = 0;
					}
					if (hit_started > 0) {
						hit_started = 0;
					}
					break;
			}
		}
		break;

		case ST_KICK_HARD_STANDING2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
					{
						App->audio->PlayChunk(high_damage, 1);
						App->UI->scoreP1 += 300;
						hit_conected++;
					}
			switch (last_input)
			{
				case IN_KICK_HARD_FINISH2: 
					state = ST_IDLE2;
					if (hit_conected > 0) {
						hit_conected = 0;
					}
					if (hit_started > 0) {
						hit_started = 0;
					}
					break;
			}
		}
		break;
		case ST_LIGHTNINGKICK2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
					{
						App->audio->PlayChunk(high_damage, 1);
						App->UI->scoreP1 += 500;
						hit_conected++;
					}
			switch (last_input)
			{
				case IN_LIGHTNINGKICK_FINISH2:
					state = ST_IDLE2;
					if (hit_conected > 0) {
						hit_conected = 0;
					}
					if (hit_started > 0) {
						hit_started = 0;
					}
					
			}
			
		}
		break;
		case ST_WHIRLWIND2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
				{
				    App->audio->PlayChunk(high_damage, 1);
					App->UI->scoreP1 += 500;
					hit_conected++;
				}
			switch (last_input)
			{	
			case IN_WHIRLWINDKICK2_FINISH2:
				state = ST_IDLE2;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				position.y = 220;
			}
		}
		break;
		case ST_PUNCH_MEDIUM2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(medium_damage, 1);
				App->UI->scoreP1 += 200;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_MEDIUM_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
			
		}
		break;


		case ST_PUNCH_HARD2:
		{
			if (App->chunli2->damage_received > 0 && hit_conected == 0)
			{
				App->audio->PlayChunk(high_damage, 1);
				App->UI->scoreP1 += 300;
				hit_conected++;
			}
			switch (last_input)
			{
			case IN_PUNCH_HARD_FINISH2: 
				state = ST_IDLE2; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_DAMAGE2:
		{
			
			switch (last_input)
			{
			case IN_DAMAGE_FINISH2:
				state = ST_IDLE2; 
				damage_received = 0;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_DAMAGE_HARD2:
		{
			switch (last_input)
			{
			case IN_DAMAGE_FINISH2:
				state = ST_IDLE2; 
				damage_received = 0; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;
		case ST_DAMAGE_FALL2:
		{
			switch (last_input)
			{
			case IN_DAMAGE_FINISH2:
				state = ST_IDLE2;
				damage_received = 0;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}

		case ST_DAMAGE_AIR2:
		{
			switch (last_input)
			{
			case IN_DAMAGE_FINISH2:
				state = ST_IDLE2; 
				damage_received = 0;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}

		case ST_BLOCK2:
		{
			switch (last_input)
			{
			case IN_BLOCK_FINISH2:
				state = ST_IDLE2; 
				block_damage = 0;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_BLOCK_CROUCH2:
		{
			switch (last_input)
			{
			case IN_BLOCK_FINISH2:
				state = ST_IDLE2; 
				block_damage = 0; 
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;

		case ST_DAMAGE_CROUCH2:
		{
			switch (last_input)
			{
				case IN_DAMAGE_FINISH2:
					state = ST_IDLE2; 
					damage_received = 0; 
					if (hit_conected > 0) {
						hit_conected = 0;
					}
					if (hit_started > 0) {
						hit_started = 0;
					}
					break;
			}
		}
		break;

		case ST_VICTORY2:
		{
			switch (last_input)
			{
			case IN_VICTORY_FINISH2:
				state = ST_IDLE2;
				win = 3;
				ResetPlayer();

				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}
		break;


		case ST_VICTORY2_2:
		{
			switch (last_input)
			{
			case IN_VICTORY2_FINISH_2:
				state = ST_IDLE2;
				win = 3;
				//victorycount++;
				ResetPlayer();			
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				break;
			}
		}

		break;

		case ST_LOSE2:
		{
			switch (last_input)
			{
			case IN_LOSE_FINISH2:	
				state = ST_IDLE2;
				//App->chunli2->win = 0;
				if (hit_conected > 0) {
					hit_conected = 0;
				}
				if (hit_started > 0) {
					hit_started = 0;
				}
				
				
				break;
			}
		}
		break;
		}
	}
	return state;
}

void ModuleChunLi::lifecondition(Animation* current_animation) {


	healthbar = life * 0.153;
	   

	if (life < 0) {
		life = 0;		
	}
	

	if (life == 0 && state!=ST_LOSE2 && App->chunli2->state!=ST_VICTORY && App->chunli2->state != ST_VICTORY2_ && App->chunli2->victorycount!=2)
	{
		lose = true;	
	}
	else {
		lose = false;
	}
	
	
}

void ModuleChunLi::resetanimations() {

	damage_received = 0;
	
	win = 0;
	sound = 0;
	WinSoundPlayed = false;
	DeathSoundPlayed = false;
	win1.Reset();
	win2.Reset();
	ignore = 0;

	jump_neutral.Reset();
	jump_forward.Reset();
	jump_backwards.Reset();
	punch.Reset();
	jump_neutral_punch.Reset();
	jump_neutral_punch_medium.Reset();
	jump_neutral_punch_hard.Reset();
	jump_backward_punch.Reset();
	jump_forward_punch.Reset();
	Crouch_punch.Reset();
	kick.Reset();
	LightningKick.Reset();
	WhirlwindKick.Reset();
	punch_medium.Reset();
	punch_hard.Reset();
	kick_medium.Reset();
	kick_hard.Reset();
	Crouch_punch.Reset();
	Crouch_medium_punch.Reset();
	Crouch_hard_punch.Reset();
	Crouch_kick.Reset();
	Crouch_medium_kick.Reset();
	Crouch_hard_kick.Reset();
	damage.Reset();
	damage2.Reset();
	damage3.Reset();
	damage4.Reset();
	damage5.Reset();
	jump_neutral_kick.Reset();
	jump_neutral_kick_medium.Reset();
	jump_neutral_kick_hard.Reset();

	jump_forward_punch_medium.Reset();
	jump_forward_punch_hard.Reset();

	jump_backward_punch_medium.Reset();
	jump_backward_punch_hard.Reset();

	jump_forward_kick.Reset();
	jump_forward_kick_medium.Reset();
	jump_forward_kick_hard.Reset();

	jump_backward_kick.Reset();
	jump_backward_kick_medium.Reset();
	jump_backward_kick_hard.Reset();

	block_standing.Reset();
	
}

void ModuleChunLi::debugcommands() {

	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_DOWN) {
		life = 0;
	}

	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN)
	{
		if (!GodMode) {
			for (int i = 0; i < MAX_COLLIDERS; i++)
			{
				if (colliders[i] != nullptr)
					colliders[i]->to_delete = true;
			}
			GodMode = true;
		}
		else {
			GodMode = false;
		}

	}

}

void ModuleChunLi::jump_neutral_logic() {

	
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
	
	
}

void ModuleChunLi::jump_forward_logic() {

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

}

void ModuleChunLi::jump_backward_logic() {

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

}