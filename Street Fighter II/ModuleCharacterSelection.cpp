#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleCharacterSelection.h"
#include "ModuleAudio.h"
#include "ModuleSceneDhalsim.h"

/*
 *Image dimensions are not being selected correctly
*/

ModuleCharacterSelection::ModuleCharacterSelection()
{
	Map = { 32,7,581,337 };
	Characters = { 40,405,352,234 }; // 37 x 37

	P1Pointer.PushBack({ 447,406,87,131 });
	P1Pointer.PushBack({ 1000,1000,87,131 });
	P1Pointer.speed = 0.2f;
	P1Pointer.loop = true;

	P1PpointerDest = { 116,134,40,45 };

	P2Pointer.PushBack({ 550,526,87,132 });
	P2Pointer.PushBack({ 1000,1000,87,132 });
	P2Pointer.speed = 0.2f;
	P2Pointer.loop = true;

	P2PointerDest = { 227,171,40,45 };
	Plane = { 569,442,47,47 };

	Ryu = {649,250,167,223};
	Ken = {829,720,160,213};
	ChunLi = {649,734,158,199};
	Dhalsim = {648,26,147,211};
	Zangief = {825,58,155,179};
	EHonda = {828,255,166,218};
	Guile = {829,478,160,225};
	Blanka = {649,486,167,199};
}

ModuleCharacterSelection::~ModuleCharacterSelection()
{}


bool ModuleCharacterSelection::Start()
{
	LOG("Loading characters selection");

	graphics = App->textures->Load("Assets/Images/character-selection.png");
	versus_graphics = App->textures->Load("Assets/Images/Versus.png");
	music = App->audio->LoadMusic("Assets/Sound/Musics/PlayerSelect.ogg");
	versus_effect = App->audio->LoadChunk("Assets/Sound/Effects/versus.wav");
	App->audio->PlayMusic(music, 300);

	character_effect = App->audio->LoadChunk("Assets/Sound/Effects/character_selection.wav");
    map_effect = App->audio->LoadChunk("Assets/Sound/Effects/map_selection.wav");
	plane_effect = App->audio->LoadChunk("Assets/Sound/Effects/plane.wav");

	P2PointerDest = { 227,171,40,45 };
	P1PpointerDest = { 116,134,40,45 };

	P1selected = false;
	P2selected = false;
	VersusScrenn = false;
	VersusTime = false;

	App->render->camera.x = App->render->camera.y = 0;

	return true;
}

bool ModuleCharacterSelection::CleanUp()
{
	LOG("Unloading Selection page");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(music);

	return true;
}

update_status ModuleCharacterSelection::Update()
{

		SDL_Rect MapDest = { 65,20,250,110 };
		SDL_Rect CharacterDest = { 117,140,150,75 }; //37 x 37

		SDL_Rect Character2;
		SDL_Rect Character2Dest = { 309,134,75,75 };

		SDL_Rect Character1;
		SDL_Rect Character1Dest = { 10,134,75,75 };


		App->render->DrawQuad({ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, 0, 0, 108, 255);
		App->render->RectBlit2(graphics, &Map, &MapDest);
		App->render->RectBlit2(graphics, &Characters, &CharacterDest);

		//P1 character slector
		if (P1selected == false) {


			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_DOWN || App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTY] < JOYSTICK_DEAD_ZONE_NEGATIVE) {
				if (P1PpointerDest.y == 171) { P1PpointerDest.y = 134; App->audio->PlayChunk(character_effect, 1); }
			}
			if (App->input->keyboard[SDL_SCANCODE_S] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_DOWN || App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTY] > JOYSTICK_DEAD_ZONE) {
				if (P1PpointerDest.y == 134) { P1PpointerDest.y = 171; App->audio->PlayChunk(character_effect, 1); }
			}
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN || App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTX] < JOYSTICK_DEAD_ZONE_NEGATIVE) {
				if (P1PpointerDest.x == 116) {/*NOTHING*/ }
				else if (P1PpointerDest.x == 153) { P1PpointerDest.x -= 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P1PpointerDest.x == 190) { P1PpointerDest.x -= 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P1PpointerDest.x == 227) { P1PpointerDest.x -= 37; App->audio->PlayChunk(character_effect, 1); }
			}
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_DOWN || App->input->Pad1.axis_state[SDL_CONTROLLER_AXIS_LEFTX] > JOYSTICK_DEAD_ZONE) {
				if (P1PpointerDest.x == 116) { P1PpointerDest.x += 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P1PpointerDest.x == 153) { P1PpointerDest.x += 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P1PpointerDest.x == 190) { P1PpointerDest.x += 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P1PpointerDest.x == 227) { /*NOTHING*/ }
			}

			if (P1PpointerDest.x == 116) {
				if (P1PpointerDest.y == 134) { Character1 = Ryu; }
				if (P1PpointerDest.y == 171) { Character1 = Ken; }
			}
			if (P1PpointerDest.x == 153) {
				if (P1PpointerDest.y == 134) { Character1 = EHonda; }
				if (P1PpointerDest.y == 171) { Character1 = ChunLi; }
			}
			if (P1PpointerDest.x == 190) {
				if (P1PpointerDest.y == 134) { Character1 = Blanka; }
				if (P1PpointerDest.y == 171) { Character1 = Zangief; }
			}
			if (P1PpointerDest.x == 227) {
				if (P1PpointerDest.y == 134) { Character1 = Guile; }
				if (P1PpointerDest.y == 171) { Character1 = Dhalsim; }
			}

			//Character select
			if (App->input->keyboard[SDL_SCANCODE_X] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				if (P1PpointerDest.x == 153 && P1PpointerDest.y == 171) {
					P1selected = true;
					App->audio->PlayChunk(map_effect, 1);
				}
			}
		}

		//P2 character slector
		if (P2selected == false) {

			if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_DOWN || App->input->Pad2.axis_state[SDL_CONTROLLER_AXIS_LEFTY] < JOYSTICK_DEAD_ZONE_NEGATIVE) {
				if (P2PointerDest.y == 171) { P2PointerDest.y = 134; App->audio->PlayChunk(character_effect, 1); }
			}
			if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_DOWN || App->input->Pad2.axis_state[SDL_CONTROLLER_AXIS_LEFTY] > JOYSTICK_DEAD_ZONE) {
				if (P2PointerDest.y == 134) { P2PointerDest.y = 171; App->audio->PlayChunk(character_effect, 1); }
			}
			if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN || App->input->Pad2.axis_state[SDL_CONTROLLER_AXIS_LEFTX] < JOYSTICK_DEAD_ZONE_NEGATIVE) {
				if (P2PointerDest.x == 116) {/*NOTHING*/ }
				else if (P2PointerDest.x == 153) { P2PointerDest.x -= 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P2PointerDest.x == 190) { P2PointerDest.x -= 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P2PointerDest.x == 227) { P2PointerDest.x -= 37; App->audio->PlayChunk(character_effect, 1); }
			}
			if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_DOWN || App->input->Pad2.axis_state[SDL_CONTROLLER_AXIS_LEFTX] > JOYSTICK_DEAD_ZONE) {
				if (P2PointerDest.x == 116) { P2PointerDest.x += 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P2PointerDest.x == 153) { P2PointerDest.x += 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P2PointerDest.x == 190) { P2PointerDest.x += 37; App->audio->PlayChunk(character_effect, 1); }
				else if (P2PointerDest.x == 227) { /*NOTHING*/ }
			}

			if (P2PointerDest.x == 116) {
				if (P2PointerDest.y == 134) { Character2 = Ryu; }
				if (P2PointerDest.y == 171) { Character2 = Ken; }
			}
			if (P2PointerDest.x == 153) {
				if (P2PointerDest.y == 134) { Character2 = EHonda; }
				if (P2PointerDest.y == 171) { Character2 = ChunLi; }
			}
			if (P2PointerDest.x == 190) {
				if (P2PointerDest.y == 134) { Character2 = Blanka; }
				if (P2PointerDest.y == 171) { Character2 = Zangief; }
			}
			if (P2PointerDest.x == 227) {
				if (P2PointerDest.y == 134) { Character2 = Guile; }
				if (P2PointerDest.y == 171) { Character2 = Dhalsim; }
			}

			//Character select
			if (App->input->keyboard[SDL_SCANCODE_J] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				if (P2PointerDest.x == 153 && P2PointerDest.y == 171) {
					P2selected = true;
					App->audio->PlayChunk(map_effect, 1);
				}
			}
		}

		App->render->RectBlit2Sym(graphics, &Character2, &Character2Dest);
		App->render->RectBlit2(graphics, &Character1, &Character1Dest);

		if (P1selected == true) {
			App->render->RectBlit2(graphics, &ChunLi, &Character1Dest);
		}
		if (P2selected == true) {
			App->render->RectBlit2Sym(graphics, &ChunLi, &Character2Dest);
		}

		if (P1selected == true && P2selected == true) {

			SDL_Rect PlaneDest = { 130,60,20,20 };
			App->render->RectBlit2(graphics, &ChunLi, &Character1Dest);
			App->render->RectBlit2Sym(graphics, &ChunLi, &Character2Dest);
			App->render->RectBlit2(graphics, &Plane, &PlaneDest);
			App->audio->PlayChunk(plane_effect, 1);
			App->fade->FadeToBlack(App->selectionScene, App->scene_dhalsim, 2.0f);
		}

		App->render->RectBlit2(graphics, &P1Pointer.GetCurrentFrame(), &P1PpointerDest);
		App->render->RectBlit2(graphics, &P2Pointer.GetCurrentFrame(), &P2PointerDest);
	
	
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {
		App->fade->FadeToBlack(App->selectionScene, App->scene_dhalsim, 2.0f);
		App->audio->StopMusic(250);
	}
	
	return UPDATE_CONTINUE;
}