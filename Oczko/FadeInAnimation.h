#pragma once
#include "Animation.h"

class FadeInAnimation :
	public Animation
{
private:
	sf::Sprite* target = nullptr;
	float size_start;
	float size_end;
	float opacity_start;
	float opacity_end;
public:
	FadeInAnimation(
		sf::Sprite* target,
		float size_start,
		float size_end,
		float lerp_time,
		float opacity_start,
		float opacity_end,
		bool block_input
	) :
		Animation(lerp_time, block_input),
		target(target),
		size_start(size_start),
		size_end(size_end),
		opacity_start(opacity_start),
		opacity_end(opacity_end)
	{

	}

	void UpdateFunction(float time, float delta_time) {
		time = sqrt(time);
		float scale   = size_start + (size_end - size_start) * time;
		float opacity = opacity_start + (opacity_end - opacity_start) * time;

		target->setScale(scale, scale);
		target->setColor(sf::Color(255, 255, 255, sf::Uint8(opacity * 255)));
	}
};

