#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({7, 14, 60, 90});
	idle.PushBack({95, 15, 60, 89});
	idle.PushBack({184, 14, 60, 90});
	idle.PushBack({276, 11, 60, 93});
	idle.PushBack({366, 12, 60, 92});
	idle.speed = 0.175f;

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 9,136,53,83 });
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.15f;

	// walk backward animation
	backward.PushBack({ 542,127,61,91 });
	backward.PushBack({ 628,127,60,91 });
	backward.PushBack({ 713,127,58,91 });
	backward.PushBack({ 797,127,58,91 });
	backward.PushBack({ 883,127,57,91 });
	backward.PushBack({ 974,127,57,91 });
	backward.speed = 0.1f;

	//punch animation
	punch.PushBack({ 19,272,64,91 });
	punch.PushBack({ 108,272,92,91 });
	punch.PushBack({ 19,272,64,91 });
	punch.speed = 0.2f;

	//kick animation

	kick.PushBack({ 606,269,60,90 });
	kick.PushBack({ 689,267,66,92 });
	kick.PushBack({ 777,265,114,94 });
	kick.PushBack({ 689,267,66,92 });
	kick.speed = 0.175f;

	//hadouken animation
	hadouken_pose.PushBack({ 34,1545,74,90 });
	hadouken_pose.PushBack({ 135,1551,85,83 });
	hadouken_pose.PushBack({ 244,1552,91,83 });
	hadouken_pose.PushBack({ 357,1558,106,77 });
	hadouken_pose.speed = 0.1f;
	hadouken_pose.loop = false;

	//crouch animation
	crouch.PushBack({ 32,1212,53,83 });
	crouch.PushBack({ 115,1227,57,69 });
	crouch.PushBack({ 197,1235,61,61 });
	crouch.loop = false;
	crouch.speed = 0.3f;

	//neutral jump animation
	jump_neutral.PushBack({ 17,847,55,85 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 100,823,56,104 });
	jump_neutral.PushBack({ 177,805,50,89 });
	jump_neutral.PushBack({ 177,805,50,89 });
	jump_neutral.PushBack({ 177,805,50,89 });
	jump_neutral.PushBack({ 177,805,50,89 });
	jump_neutral.PushBack({ 251,798,54,77 });
	jump_neutral.PushBack({ 327,813,48,70 });
	jump_neutral.loop = false;
	jump_neutral.speed = 0.175f;

	//falling animation

	falling.PushBack({ 397,810,48,89 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.PushBack({ 464,819,55,109 });
	falling.loop = false;
	falling.speed = 0.175f;
	

	//crouch punch
	Crouch_punch.PushBack({ 24,1344,69,61 });
	Crouch_punch.PushBack({ 118,1344,95,61 });
	Crouch_punch.speed = 0.2f;

	//death animation
	Death.PushBack({ 350,2233,124,48 });
	Death.PushBack({ 849,2246,123,41 });
	Death.PushBack({ 985,2265,127,31 });
	Death.loop = false;
	Death.speed = 0.05f;

	//Jump forward animation
	jump_forward.PushBack({ 594,823,55,103 });
	jump_forward.PushBack({ 594,823,55,103 });
	jump_forward.PushBack({ 594,823,55,103 });
	jump_forward.PushBack({ 594,823,55,103 });
	jump_forward.PushBack({ 594,823,55,103 });
	jump_forward.PushBack({ 594,823,55,103 });
	jump_forward.PushBack({ 669,813,61,78 });
	jump_forward.PushBack({ 744,811,104,42 });
	jump_forward.PushBack({ 864,791,53,82 });
	jump_forward.PushBack({ 927,808,122,44 });
	jump_forward.PushBack({ 1064,806,71,87 });
	jump_forward.PushBack({ 1149,802,55,109 });
	jump_forward.loop = false;
	jump_forward.speed = 0.175f;

	//Jump backwards animation
	jump_backwards.PushBack({ 1064,806,71,87 });
	jump_backwards.PushBack({ 1064,806,71,87 });
	jump_backwards.PushBack({ 1064,806,71,87 });
	jump_backwards.PushBack({ 1064,806,71,87 });
	jump_backwards.PushBack({ 1064,806,71,87 });
	jump_backwards.PushBack({ 1064,806,71,87 });
	jump_backwards.PushBack({ 927,808,122,44 });
	jump_backwards.PushBack({ 864,791,53,82 });
	jump_backwards.PushBack({ 744,811,104,42 });
	jump_backwards.PushBack({ 669,813,61,78 });
	jump_backwards.PushBack({ 594,823,55,103 });
	jump_backwards.loop = false;
	jump_backwards.speed = 0.175f;

	//Jump neutral punch
	jump_neutral_punch.PushBack({176,805,50,89});
	jump_neutral_punch.PushBack({ 29,987,52,69 });
	jump_neutral_punch.PushBack({ 97,985,81,71 });
	jump_neutral_punch.loop = false;
	jump_neutral_punch.speed = 0.175f;

	//Jump forward punch

	jump_forward_punch.PushBack({ 235,987,52,69 });
	jump_forward_punch.PushBack({ 307,979,69,77 });
	jump_forward_punch.PushBack({ 395,992,88,64 });
	jump_forward_punch.loop = false;
	jump_forward_punch.speed = 0.175f;

	//Jump backward punch
	jump_backward_punch.PushBack({ 27,1099,59,76 });
	jump_backward_punch.PushBack({ 107,1102,55,73 });
	jump_backward_punch.PushBack({ 182,1108,77,67 });
	jump_backward_punch.loop = false;
	jump_backward_punch.speed = 0.175f;

	//Damage animation

	damage.PushBack({ 30,2101,68,79 });
	damage.PushBack({ 117,2090,62,90 });
	damage.PushBack({ 207,2091,68,89 });
	damage.PushBack({ 297,2091,72,88 });
	damage.PushBack({ 398,2094,58, 85});
	damage.PushBack({ 482,2097,66, 82});
	damage.speed = 0.1f;
	damage.loop = false;

	//Victory animation
	victory.PushBack({ 495, 2479, 53, 83 });
	victory.PushBack({ 573, 2474, 60,88 });
	victory.PushBack({ 660, 2465, 60, 97 });
	victory.PushBack({ 745, 2440, 55,122 });
	victory.speed = 0.05f;
	victory.loop = false;

	//Victory2 animation

	victory1.PushBack({ 46	,2467,53,97 });
	victory1.PushBack({ 124,2469,54, 95});
	victory1.PushBack({ 206,2469,54, 95});
	victory1.PushBack({ 289,2469,54,95 });
	victory1.PushBack({ 380,2468,54,96 });
	victory1.loop = false;
	victory1.speed = 0.1f;

	

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/ryu.png"); // arcade version
	position.x = 100; //Returns to its original position
	
	//Sounds
	deathSound = App->audio->LoadChunk("Assets/Sound/ryu-death.wav");
	ugh = App->audio->LoadChunk("Assets/Sound/ugh.wav");
	hit = App->audio->LoadChunk("Assets/Sound/golpe.wav");

	//Start functions to reset player
	ResetPlayer();
	Death.Reset();
	DeathCount = 0;
	victorycount = 0;

	//Add a collider to the player
	colliderplayer = App->collision->AddCollider({ position.x + 7 ,position.y - 90,45,90 }, COLLIDER_PLAYER, App->player);
	
	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player textures");

	App->textures->Unload(graphics);

	return true;
}



// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;
	p2Qeue<ryu_inputs> inputs;
	ryu_states current_state = ST_UNKNOWN;

	if (position.y == 220) {
		speedX = 1;
		speedY = 1;
	}
	if (HaveCollider == false && GodMode == false && state != ST_CROUCH) {
		colliderplayer = App->collision->AddCollider({ position.x + 7 ,position.y - 90,45,90 }, COLLIDER_PLAYER, App->player);
		HaveCollider = true;
	}

	//Debug Commands
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN ) {
		if (GodMode == false) {
			App->collision->DeleteCollider(colliderplayer);

			GodMode = true;
		}
		else if (GodMode == true) {
			colliderplayer = App->collision->AddCollider({ position.x + 7 ,position.y - 90,45,90 }, COLLIDER_PLAYER, App->player);

			GodMode = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) //Treu-re abans d'entregar
	{
		life = 0;
	}

	if (death == false) {
		while (external_input(inputs))
		{

			internal_input(inputs);

			state = process_fsm(inputs);

			
			if (state != current_state)
			{

				healthbar = life * 0.153;

				
				if (life < 0) {
					life = 0;
				}

				if (App->player2->life == 0 && App->UI->victorycount==0) {

					if (acumvictory < 75) {
						current_animation = &victory;
						acumvictory++;
					}
					if (acumvictory == 75) {
						victory.Reset();
						acumvictory = 0;
					}
				}
				if (App->player2->life == 0 && App->UI->victorycount == 1) {

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
						
						App->audio->PlayChunk(deathSound, 0);
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

					//ResetPlayer();
				}

				
				
			
				if (damage_received == true) {				
					
					
					if (life == 0) {
						damage_received = false;
					}
					if (acumdamage == 1) {
						App->collision->DeleteCollider(colliderplayer);
						App->audio->PlayChunk(hit, 0);
						App->audio->PlayChunk(ugh,0);
					}
					if (acumdamage >= 0 && acumdamage < 60 && life > 0) {
						
						
						current_animation = &damage;
						acumdamage++;
					}
					
					if (acumdamage == 60 && life > 0) {
						
						acumdamage = 0;
						
						damage.Reset();
						
						damage_received = false;
						colliderplayer = App->collision->AddCollider({ position.x + 7 ,position.y - 90,45,90 }, COLLIDER_PLAYER, App->player);
						
					}					
					
				}				

				else  if (life > 0 && damage_received==false && App->player2->life>0) {
					
					
					switch (state)
					{
					case ST_IDLE:
						current_animation = &idle;
						forward.Reset();
						backward.Reset();
						crouch.Reset();
						kick.Reset();
						punch.Reset();
						hadouken_pose.Reset();
						HadoukenCount = 0;
						ActiveHadouken = 0;
						ActiveDeath = 0;
						break;

					case ST_WALK_FORWARD:
						if (movef == true) {
							current_animation = &forward;
							if (position.x < 825)
							{
								position.x += speedX;
								if (-((position.x - 60)*2) <= App->render->camera.x - SCREEN_WIDTH)
								{
									if (App->render->camera.x > -1004)
									{
										App->render->camera.x -= speedX * 2;
									}
								}

							}
							crouch.Reset();
							kick.Reset();
							punch.Reset();
							hadouken_pose.Reset();
							HadoukenCount = 0;
							ActiveHadouken = 0;
							ActiveDeath = 0;
						}
						else if (movef == false) {
							movef = true;
						}
						break;

					case ST_WALK_BACKWARD:
						if (moveb == true) {
							current_animation = &backward;
							if (position.x > 0 && App->plyDistance < SCREEN_WIDTH)
							{
								position.x -= (0.6 *speedX);
								if (-(position.x * 2) >= App->render->camera.x - 5)
								{
									if (App->render->camera.x < 0)
									{
										App->render->camera.x += speedX * 2;
									}
								}
							}
							crouch.Reset();
							kick.Reset();
							punch.Reset();
							hadouken_pose.Reset();
							HadoukenCount = 0;
							ActiveHadouken = 0;
							ActiveDeath = 0;
						}
						else if (moveb == true) {
							moveb = true;
						}
						break;
					case ST_JUMP_NEUTRAL:

						JumpCount = 1;
						if (JumpCount == 1) {
							if (position.y == 220) {
								JumpMax = false;
								JumpMin = true;
							}
							if (position.y <= 105) {
								JumpMin = false;
								JumpMax = true;
							}

							if (JumpMin == true) {
								falling.Reset();
								position.y -= (speedY * 2);
								current_animation = &jump_neutral;
							}
							if (JumpMax == true) {
								jump_neutral.Reset();
								position.y += (speedY * 3.2);
								current_animation = &falling;
							}

						}

						break;
					case ST_JUMP_FORWARD:
						if (position.x < 825)
						{
							position.x += speedX * 1.5;
							if (-((position.x - 60) * 2) <= App->render->camera.x - SCREEN_WIDTH && App->input->camMoving == false)
							{
								if (App->render->camera.x > -1004)
								{
									App->render->camera.x -= speedX * 2;
								}
							}
						}
						JumpCount = 1;
						if (JumpCount == 1) {
							if (position.y == 220) {
								JumpMax = false;
								JumpMin = true;
							}
							if (position.y <= 110) {
								JumpMin = false;
								JumpMax = true;
							}

							if (JumpMin == true) {
								falling.Reset();
								position.y -= (speedY * 2);
								current_animation = &jump_forward;
							}
							if (JumpMax == true) {
								jump_forward.Reset();
								position.y += (speedY * 3.2);
								current_animation = &falling;
							}
						}
						break;
					case ST_JUMP_BACKWARD:
						if (position.x > 0)
						{
							position.x -= (0.6 *speedX);
							if (-(position.x * 2) >= App->render->camera.x - 5)
							{
								if (App->render->camera.x < 0)
								{
									App->render->camera.x += speedX * 2;
								}
							}
						}
						JumpCount = 1;
						if (JumpCount == 1) {
							if (position.y == 220) {
								JumpMax = false;
								JumpMin = true;
							}
							if (position.y <= 110) {
								JumpMin = false;
								JumpMax = true;
							}

							if (JumpMin == true) {
								falling.Reset();
								position.y -= (speedY * 2);
								current_animation = &jump_backwards;
							}
							if (JumpMax == true) {
								jump_backwards.Reset();
								position.y += (speedY * 3.2);
								current_animation = &falling;
							}
						}
						break;
					case ST_CROUCH:
						if (HaveCollider == true) {
							App->collision->DeleteCollider(colliderplayer);
							HaveCollider = false;
						}
						colliderplayer = App->collision->AddCollider({position.x, position.y +100, 45, 65}, COLLIDER_PLAYER, App->player);
						current_animation = &crouch;
						App->collision->DeleteCollider(colliderplayer);
						break;
					case ST_PUNCH_STANDING:
						current_animation = &punch;
						if (punchCol == false) {
							if (position.x < App->player2->position.x) {
								punchcollider = App->collision->AddCollider({ position.x + 41, position.y - 79, 51, 13 }, COLLIDER_PLAYER_ATTACK, App->player, 25);
							}
							if (position.x > App->player2->position.x) {
								punchcollider = App->collision->AddCollider({ position.x -21, position.y - 79, 51, 13 }, COLLIDER_PLAYER_ATTACK, App->player, 25);
							}
							
							punchCol = true;
						}
						else if (punchCol == true) {
							App->collision->DeleteCollider(punchcollider);
						}
						if (punch.current_frame == 0 && colliderErese == true) {
							punchCol = false;
						}
						colliderErese = true;
						break;
					case ST_PUNCH_CROUCH:
						current_animation = &Crouch_punch;
						if (CrPunchCol == false) {
							if (position.x < App->player2->position.x) {
								crouchpunchcollider = App->collision->AddCollider({ position.x + 48, position.y - 49, 48, 10 }, COLLIDER_PLAYER_ATTACK, App->player, 25);
							}
							if (position.x > App->player2->position.x) {
								crouchpunchcollider = App->collision->AddCollider({ position.x - 28, position.y - 49, 48, 10 }, COLLIDER_PLAYER_ATTACK, App->player, 25);
							}
							
							CrPunchCol = true;
						}
						else if (CrPunchCol == true) {
							App->collision->DeleteCollider(crouchpunchcollider);
						}
						if (Crouch_punch.current_frame == 0 && colliderErese3 == true) {
							CrPunchCol = false;
						}
						colliderErese3 = true;
						break;
					case ST_PUNCH_NEUTRAL_JUMP:
						current_animation = &jump_neutral_punch;
						if (JumpCount == 1) {
							if (position.y == 220) {
								JumpMax = false;
								JumpMin = true;
							}
							if (position.y <= 105) {
								JumpMin = false;
								JumpMax = true;
							}

							if (JumpMin == true) {
								falling.Reset();
								position.y -= (speedY * 2);
							}
							if (JumpMax == true) {
								jump_neutral.Reset();
								position.y += (speedY * 3.2);
							}
						}
						break;
					case ST_PUNCH_FORWARD_JUMP:
						
						if (position.x < 825)
						{
							position.x += speedX * 1.5;
							if (-((position.x - 60) * 2) <= App->render->camera.x - SCREEN_WIDTH && App->input->camMoving == false)
							{
								if (App->render->camera.x > -1004)
								{
									App->render->camera.x -= speedX * 2;
								}
							}
						}
						current_animation = &jump_forward_punch;
						if (JumpCount == 1) {
							if (position.y == 220) {
								JumpMax = false;
								JumpMin = true;
							}
							if (position.y <= 110) {
								JumpMin = false;
								JumpMax = true;
							}

							if (JumpMin == true) {
								falling.Reset();
								position.y -= (speedY * 2);
								
							}
							if (JumpMax == true) {
								jump_forward.Reset();
								position.y += (speedY * 3.2);
							
							}
						}

						break;
					case ST_PUNCH_BACKWARD_JUMP:
						current_animation = &jump_backward_punch;
						if (position.x > 0)
						{
							position.x -= (0.6 *speedX);
							if (-(position.x * 2) >= App->render->camera.x - 5)
							{
								if (App->render->camera.x < 0)
								{
									App->render->camera.x += speedX * 2;
								}
							}
						}
						
						if (JumpCount == 1) {
							if (position.y == 220) {
								JumpMax = false;
								JumpMin = true;
							}
							if (position.y <= 110) {
								JumpMin = false;
								JumpMax = true;
							}

							if (JumpMin == true) {
								falling.Reset();
								position.y -= (speedY * 2);
								
							}
							if (JumpMax == true) {
								jump_backwards.Reset();
								position.y += (speedY * 3.2);
								
							}
						}
						break;
					case ST_KICK_STANDING:
						current_animation = &kick;
						if (kickCol == false) {
							kickcollider = App->collision->AddCollider({ position.x + 25, position.y - 92, 70, 27 }, COLLIDER_PLAYER_ATTACK, App->player, 25);
							kickCol = true;
						}
						if (kickCol == true && kick.current_frame != 0) {
							App->collision->DeleteCollider(kickcollider);
							kickCol = false;
						}
						break;
					case ST_HADOUKEN:
						current_animation = &hadouken_pose;
						if (HadoukenCount < 35) {
							HadoukenCount++;
						}
						if (HadoukenCount == 35 && ActiveHadouken == 0) {
							if (position.x < App->player2->position.x) {
								App->particle->AddParticle(App->particle->hadouken, position.x + 65, position.y - 70, COLLIDER_PLAYER_ATTACK, 0);
							}
							if (position.x > App->player2->position.x) {
								App->particle->AddParticle(App->particle->hadoukenSym, position.x - 10, position.y - 70, COLLIDER_PLAYER_ATTACK, 0);
							}
							App->audio->PlayChunk(App->particle->hadouken.sound, 0);
							HadoukenCount = 0;
							ActiveHadouken = 1;
						}
						break;
					}
					
				}
				current_state = state;

				
				// Draw everything --------------------------------------

				SDL_Rect r = current_animation->GetCurrentFrame();
				if (position.x < App->player2->position.x) {
					App->render->Blit(graphics, position.x, position.y - r.h, &r);
				}
				if (position.x > App->player2->position.x) {
					App->render->BlitSym(graphics, position.x, position.y - r.h, &r);
				}
				//Update collider position to player position
				if (state == ST_CROUCH) {
					colliderplayer->SetPos(position.x + 7, position.y - 65);
				}
				else {
					colliderplayer->SetPos(position.x + 7, position.y - 90);
				}
				
				return UPDATE_CONTINUE;
			}
		}
	}
}

	

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY && (state == ST_WALK_FORWARD || state == ST_WALK_BACKWARD || state == ST_IDLE))
	{			
		movef = false;
	}
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY && (state == ST_JUMP_BACKWARD || state == ST_JUMP_FORWARD || state == ST_JUMP_NEUTRAL)) {
		speedX = -1;
		
	}
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT)
	{
		int aux = life;
		life = aux - c2->damage;
		damage_received = true;
		
	}
	
}

bool ModulePlayer::external_input(p2Qeue<ryu_inputs>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;

	SDL_Event event;
	int max = App->input->eventList.size();
	for(int a=0; a < max; ++a)
	{		
		event = App->input->eventList.front();
		App->input->eventList.pop_front();
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_s:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_w:
				up = false;
				break;
			case SDLK_a:
				inputs.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_d:
				inputs.Push(IN_RIGHT_UP);
				right = false;
				break;
			case SDLK_x:
				return false;
				break;
			case SDLK_k:
				return false;
				break;
			case SDLK_h:
				return false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_x:
				inputs.Push(IN_X);
				break;
			case SDLK_c:
				inputs.Push(IN_C);
				break;
			case SDLK_v:
				inputs.Push(IN_V);
				break;
			case SDLK_w:
				up = true;
				break;
			case SDLK_s:
				down = true;
				break;
			case SDLK_a:
				left = true;
				break;
			case SDLK_d:
				right = true;
				break;
			}
		}
		App->input->eventList.push_back(event);
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

void ModulePlayer::internal_input(p2Qeue<ryu_inputs>& inputs)
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

	if (hadouken_timer > 0)
	{
		if (SDL_GetTicks() - hadouken_timer > HADOUKEN_TIME)
		{
			inputs.Push(IN_HADOUKEN_FINISH);
			hadouken_timer = 0;
		}
	}
}

void ModulePlayer::ResetPlayer() {
	
	life = 1000;
	position.x = 100; //Returns to its original position
	if (App->player2->position.x != 300 || App->player2->life != 1000) {
		ActiveDeath = 0;		
		App->player2->ResetPlayer();
		App->UI->time = 99;
		App->UI->Counter1 = 9;
		App->UI->Counter2 = 9;		
	}
}