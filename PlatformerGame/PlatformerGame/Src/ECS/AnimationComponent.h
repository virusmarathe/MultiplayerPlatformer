#pragma once

#include "Components.h"
#include <map>

struct Animation
{
	Animation(int i, int f, int s) : index(i), frames(f), timePerFrame(s) {}

	int index;
	int frames;
	int timePerFrame;
};

class AnimationComponent : public Component
{
public:

	void AddAnimation(int ID, Animation * anim)
	{
		animations.emplace(ID, anim);
	}

	void play(int ID)
	{
		frames = animations[ID]->frames;
		timePerFrame = animations[ID]->timePerFrame;
		animIndex = animations[ID]->index;
	}

	int animIndex = 0;
	std::map<int, Animation*> animations;
	int frames = 0;
	int timePerFrame = 100;
};