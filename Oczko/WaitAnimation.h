#pragma once
#include "Animation.h"
class WaitAnimation :
    public Animation
{
private:
	sf::Transformable* target = nullptr;
public:
	WaitAnimation(
		float time,
		bool block_input = false
	) :
		Animation(time, block_input),
		target(target)
	{

	}

	void UpdateFunction(float time, float delta_time) {
		;
	}


};

