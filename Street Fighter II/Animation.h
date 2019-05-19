#ifndef __ANIMATION_H__
#define __ANIMATION_H__


#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_FRAMES 25

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

	p2Point <int> pivot[MAX_FRAMES];
	SDL_Rect hitbox[MAX_FRAMES]; 
	COLLIDER_TYPE type[MAX_FRAMES]; 
	Module *callback[MAX_FRAMES]; 
	int maxcolliders[MAX_FRAMES]; 
	int damage[MAX_FRAMES];
	

public:
	float current_frame;
	int last_frame = 0;
	int loops = 0;
	int last_collider = 0;


public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= last_frame)
		{
			current_frame = (loop) ? 0.0f : last_frame - 1;
			loops++;
		}

		return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0;
	}
	
	void PushBack1(const SDL_Rect& rect, p2Point <int> Pivot, int nColliders, SDL_Rect rhitbox[], COLLIDER_TYPE ctipo[], Module *pcallback[], int dmg)
	{

		
		frames[last_frame] = rect;		
		pivot[last_frame] = Pivot;
		damage[last_frame] = dmg*10;
	
		maxcolliders[last_frame] = nColliders;

		for (int i = 0; i < nColliders; i++)
		{			
			hitbox[i] = rhitbox[i];
			type[i] = ctipo[i];
			callback[i] = pcallback[i];
			
		}
		last_frame++;
	}
	
	
};



#endif