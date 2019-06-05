#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Module.h"
#include "ModuleWelcomePage.h"
#include "ModuleAudio.h"
#include "ModuleSceneDhalsim.h"
#include "ModuleCharacterSelection.h"


ModuleWelcomePage::ModuleWelcomePage()
{
	background.x = 0;
	background.y = 0;
	background.h = SCREEN_HEIGHT;
	background.w = SCREEN_WIDTH;

	pointer.x = 6;
	pointer.y = 7;
	pointer.h = 18;
	pointer.w = 20;
	//////////////////
	LicensedBy[0].x = 112;
	LicensedBy[0].y = 12;
	LicensedBy[0].h = 14;
	LicensedBy[0].w = 165;

	LicensedBy[1].x = 112;
	LicensedBy[1].y = 32;
	LicensedBy[1].h = 14;
	LicensedBy[1].w = 165;

	LicensedBy[2].x = 112;
	LicensedBy[2].y = 52;
	LicensedBy[2].h = 14;
	LicensedBy[2].w = 165;

	LicensedBy[3].x = 112;
	LicensedBy[3].y = 73;
	LicensedBy[3].h = 14;
	LicensedBy[3].w = 165;

	LicensedBy[4].x = 112;
	LicensedBy[4].y = 93;
	LicensedBy[4].h = 14;
	LicensedBy[4].w = 165;

	LicensedBy[5].x = 112;
	LicensedBy[5].y = 114;
	LicensedBy[5].h = 14;
	LicensedBy[5].w = 165;
	
	/*LicensedBy[6].x = 112;
	LicensedBy[6].y = 134;
	LicensedBy[6].h = 14;
	LicensedBy[6].w = 165;*/
	///////////////////
	CapcomLogo[0].x = 35;
	CapcomLogo[0].y = 20;
	CapcomLogo[0].h = 31;
	CapcomLogo[0].w = 144;

	CapcomLogo[1].x = 35;
	CapcomLogo[1].y = 58;
	CapcomLogo[1].h = 31;
	CapcomLogo[1].w = 144;

	CapcomLogo[2].x = 35;
	CapcomLogo[2].y = 97;
	CapcomLogo[2].h = 31;
	CapcomLogo[2].w = 144;

	CapcomLogo[3].x = 35;
	CapcomLogo[3].y = 135;
	CapcomLogo[3].h = 31;
	CapcomLogo[3].w = 144;

	CapcomLogo[4].x = 35;
	CapcomLogo[4].y = 174;
	CapcomLogo[4].h = 31;
	CapcomLogo[4].w = 144;
	
	CapcomLogo[5].x = 212;
	CapcomLogo[5].y = 59;
	CapcomLogo[5].h = 31;
	CapcomLogo[5].w = 144;

	CapcomLogo[6].x = 212;
	CapcomLogo[6].y = 98;
	CapcomLogo[6].h = 31;
	CapcomLogo[6].w = 144;

	CapcomLogo[7].x = 212;
	CapcomLogo[7].y = 137;
	CapcomLogo[7].h = 31;
	CapcomLogo[7].w = 144;
	/////////////
	GameLogo[0].x = 1;//64
	GameLogo[0].y = 3;//0
	GameLogo[0].h = 129;//37
	GameLogo[0].w = 248;//70

	GameLogo[1].x = 25;//69
	GameLogo[1].y = 161;//39
	GameLogo[1].h = 197;//55
	GameLogo[1].w = 225;//63

	GameLogo[2].x = 40;//83
	GameLogo[2].y = 389;//94
	GameLogo[2].h = 212;//59
	GameLogo[2].w = 188;//53

	GameLogo[3].x = 11;//66
	GameLogo[3].y = 635;//160
	GameLogo[3].h = 135;//39
	GameLogo[3].w = 273;//78

	GameLogo[4].x = 299;//142
	GameLogo[4].y = 3;//0
	GameLogo[4].h = 220;//62
	GameLogo[4].w = 256;//72

	GameLogo[5].x = 321;//152
	GameLogo[5].y = 245;//67
	GameLogo[5].h = 235;//67
	GameLogo[5].w = 156;//45

	GameLogo[6].x = 309;//149
	GameLogo[6].y = 498;//138
	GameLogo[6].h = 163;//47
	GameLogo[6].w = 246;//70

	GameLogo[7].x = 661;//247
	GameLogo[7].y = 19;//4
	GameLogo[7].h = 254;//72
	GameLogo[7].w = 230;//65

	GameLogo[8].x = 625;//237
	GameLogo[8].y = 294;//81
	GameLogo[8].h = 253;//72
	GameLogo[8].w = 186;//53

	GameLogo[9].x = 606;//231
	GameLogo[9].y = 579;//160
	GameLogo[9].h = 229;//65
	GameLogo[9].w = 231;//67
	///////////
	Nintendo = true;
	capcom = false;
	logoOff = false;	
}

ModuleWelcomePage::~ModuleWelcomePage()
{}

bool ModuleWelcomePage::Start()
{
	LOG("Loading WelcomePage");

	graphics = App->textures->Load("Assets/Images/TitleScreen.png");
	pointUI = App->textures->Load("Assets/Images/MenuPointer.png");
	Licensed = App->textures->Load("Assets/Images/LicensedBy.png");
	Capcom = App->textures->Load("Assets/Images/Capcom.png");
	Logo = App->textures->Load("Assets/Images/Logo2.png");
	music = App->audio->LoadMusic("Assets/Sound/Musics/start_music.ogg");
	//SelectFX = App->audio->LoadChunk("Assets/Sound/Musics/.ogg");
	//start_sound = App->audio->LoadChunk("Assets/Sound/start_sound.wav");
	App->render->camera.x = App->render->camera.y = 0;

	finish = false;
	select = false;
	timer = 0;
	return true;
}

bool ModuleWelcomePage::CleanUp()
{
	LOG("Unloading WelcomePage");

	App->textures->Unload(graphics);
	App->textures->Unload(pointUI);
	App->textures->Unload(Licensed);
	App->textures->Unload(Logo);
	App->audio->UnloadMusic(music);
	//App->audio->UnloadChunk(SelectFX);

	return true;
}

update_status ModuleWelcomePage::Update()
{	
	if (App->intro == true)
	{
		Nintendo = false;
	}

	if (Nintendo == true)
	{
		++timer;
		if (timer == 120)
		{
			timer = 0;
			Nintendo = false;
			capcom = true;				
		}
		if (timer < 95)App->render->Blit(Licensed, 110, 100, &LicensedBy[0]);
		if (timer > 94 && timer < 101)App->render->Blit(Licensed, 110, 100, &LicensedBy[1]);
		if (timer > 100 && timer < 106)App->render->Blit(Licensed, 110, 100, &LicensedBy[2]);
		if (timer > 105 && timer < 111)App->render->Blit(Licensed, 110, 100, &LicensedBy[3]);
		if (timer > 110 && timer < 116)App->render->Blit(Licensed, 110, 100, &LicensedBy[4]);
		//if (timer > 115 && timer <121)App->render->Blit(Licensed, 110, 100, &LicensedBy[5]);
		//if (timer > 118)App->render->Blit(Licensed, 120, 100, &LicensedBy[6]);
	}

	if (capcom == true)
	{
		++timer;
		if (timer == 200)
		{
			capcom = false;
			logoOff = true;
			timer = 0;
		}
		if (timer > 60 && timer < 66)App->render->Blit(Capcom, 120, 100, &CapcomLogo[4]);
		if (timer > 65 && timer < 71)App->render->Blit(Capcom, 120, 100, &CapcomLogo[3]);
		if (timer > 70 && timer < 76)App->render->Blit(Capcom, 120, 100, &CapcomLogo[2]);
		if (timer > 75 && timer < 81)App->render->Blit(Capcom, 120, 100, &CapcomLogo[1]);
		if (timer > 80 && timer < 101)App->render->Blit(Capcom, 120, 100, &CapcomLogo[0]);

		if (timer > 100 && timer < 106)App->render->Blit(Capcom, 120, 100, &CapcomLogo[5]);
		if (timer > 105 && timer < 111)App->render->Blit(Capcom, 120, 100, &CapcomLogo[6]);
		if (timer > 110 && timer < 116)App->render->Blit(Capcom, 120, 100, &CapcomLogo[7]);
		if (timer > 115 && timer < 121)App->render->Blit(Capcom, 120, 100, &CapcomLogo[6]);
		if (timer > 120 && timer < 126)App->render->Blit(Capcom, 120, 100, &CapcomLogo[5]);

		if (timer > 125 && timer < 156)App->render->Blit(Capcom, 120, 100, &CapcomLogo[0]);
		if (timer > 155 && timer < 161)App->render->Blit(Capcom, 120, 100, &CapcomLogo[1]);
		if (timer > 160 && timer < 166)App->render->Blit(Capcom, 120, 100, &CapcomLogo[2]);
		if (timer > 165 && timer < 171)App->render->Blit(Capcom, 120, 100, &CapcomLogo[3]);
		if (timer > 170 && timer < 176)App->render->Blit(Capcom, 120, 100, &CapcomLogo[4]);	
	}

	if (logoOff == true)
	{
		++timer;
		if (timer == 230)
		{
			logoOff = false;
			App->intro = true;
			timer = 0;
			App->audio->PlayMusic(music, 300);
		}
		if (timer > 60 && timer < 101)App->render->Blit(Logo, 60, 20, &GameLogo[0]);

		if (timer > 100 && timer < 106)App->render->Blit(Logo, 60, 20, &GameLogo[1]);
		if (timer > 105 && timer < 111)App->render->Blit(Logo, 60, 20, &GameLogo[2]);
		if (timer > 110 && timer < 116)App->render->Blit(Logo, 60, 20, &GameLogo[3]);
		if (timer > 115 && timer < 121)App->render->Blit(Logo, 60, 20, &GameLogo[4]);
		if (timer > 120 && timer < 126)App->render->Blit(Logo, 60, 20, &GameLogo[5]);
		if (timer > 125 && timer < 131)App->render->Blit(Logo, 60, 20, &GameLogo[6]);
		if (timer > 130 && timer < 136)App->render->Blit(Logo, 60, 20, &GameLogo[7]);
		if (timer > 135 && timer < 141)App->render->Blit(Logo, 60, 20, &GameLogo[8]);
		if (timer > 140 && timer < 146)App->render->Blit(Logo, 60, 20, &GameLogo[9]);
		if (timer > 125 && timer < 156)App->render->Blit(Logo, 60, 20, &GameLogo[6]);
		if (timer > 155 && timer < 161)App->render->Blit(Logo, 60, 20, &GameLogo[8]);
		if (timer > 160 && timer < 166)App->render->Blit(Logo, 60, 20, &GameLogo[5]);
		if (timer > 165 && timer < 171)App->render->Blit(Logo, 60, 20, &GameLogo[9]);
		if (timer > 170 && timer < 176)App->render->Blit(Logo, 60, 20, &GameLogo[6]);
		if (timer > 175 && timer < 181)App->render->Blit(Logo, 60, 20, &GameLogo[5]);
		if (timer > 180 && timer < 186)App->render->Blit(Logo, 60, 20, &GameLogo[8]);
		if (timer > 185 && timer < 191)App->render->Blit(Logo, 60, 20, &GameLogo[7]);
		if (timer > 190 && timer < 196)App->render->Blit(Logo, 60, 20, &GameLogo[6]);
		if (timer > 195 && timer < 201)App->render->Blit(Logo, 60, 20, &GameLogo[5]);
		if (timer > 200 && timer < 206)App->render->Blit(Logo, 60, 20, &GameLogo[4]);
		if (timer > 205 && timer < 211)App->render->Blit(Logo, 60, 20, &GameLogo[3]);
		if (timer > 210 && timer < 216)App->render->Blit(Logo, 60, 20, &GameLogo[2]);
		if (timer > 215 && timer < 221)App->render->Blit(Logo, 60, 20, &GameLogo[1]);
		if (timer > 220 && timer < 260)App->render->Blit(Logo, 60, 20, &GameLogo[0]);
	}

	if (capcom == false && Nintendo == false && logoOff == false)
	{
		App->render->Blit(graphics, 0, 0, &background);
		if (select == false)
		{
			App->render->Blit(pointUI, 100, 180, &pointer);
		}
		else
		{
			++timer;
			if (timer >= 20)
			{
				finish = true;
			}
			if (timer % 7 == 0)
			{
				App->render->Blit(pointUI, 100, 180, &pointer);
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN || App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN)
		{
			select = true;
			//App->audio->PlayChunk(SelectFX, 0);
		}


		if (finish == true)
		{
			App->fade->FadeToBlack(App->welcome_page, App->selectionScene, 0.8f);		
			//App->audio->PlayChunk(start_sound, 0);
			App->audio->StopMusic(250);
			select = false;
			finish = false;
		}
	}

	return UPDATE_CONTINUE;
}