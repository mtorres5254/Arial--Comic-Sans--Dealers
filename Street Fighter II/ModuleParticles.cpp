#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Images/particles.png");

	//Hadouken particle
	hadouken.anim.PushBack({ 9, 22, 43, 32 });
	hadouken.anim.PushBack({ 66, 24, 56, 28 });
	hadouken.life = 3000;
	hadouken.anim.speed = 0.15f;
	hadouken.speed.x = 4;
	hadouken.sound = App->audio->LoadChunk("Assets/Sound/Hadouken.wav");
	hadouken.damage = 100;

	hadoukenFinish.anim.PushBack({ 130,28,26,20 });
	hadoukenFinish.anim.PushBack({ 168,25,15,25 });
	hadoukenFinish.anim.PushBack({ 193,24,28,28 });
	hadoukenFinish.life = 200;
	hadoukenFinish.anim.speed = 0.15f;
	hadoukenFinish.speed.x = 0;
	hadoukenFinish.anim.loop = false;

	//Hadouken Symmetry particle
	hadoukenSym.anim.PushBack({ 410,22,43,32 });
	hadoukenSym.anim.PushBack({ 340,24,56,28 });
	hadoukenSym.life = 3000;
	hadoukenSym.anim.speed = 0.115f;
	hadoukenSym.speed.x = -4;
	hadoukenSym.sound = App->audio->LoadChunk("Assets/Sound/Hadouken.wav");
	hadoukenSym.damage = 100;

	hadoukenFinishSym.anim.PushBack({ 306,28,26,20 });
	hadoukenFinishSym.anim.PushBack({ 279,25,15,25 });
	hadoukenFinishSym.anim.PushBack({ 241,24,28,28 });
	hadoukenFinishSym.life = 200;
	hadoukenFinishSym.anim.speed = 0.15f;
	hadoukenFinishSym.speed.x = 0;
	hadoukenFinishSym.anim.loop = false;
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];		

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				
				//
			}
		}
	
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->damage = particle.damage;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this, p->damage);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

