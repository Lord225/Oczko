#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>

// Animacja liniowego przesuniêcia obiektu
class TranslateAnimation :
	public Animation
{
private:
	sf::Transformable* target = nullptr;
	sf::Vector2f start;
	sf::Vector2f end;
public:
	TranslateAnimation(
		sf::Transformable* target, 
		sf::Vector2f start, 
		sf::Vector2f end, 
		float lerp_time, 
		bool block_input
	) :
	Animation(lerp_time, block_input), 
	target(target),
	start(start),
	end(end)
	{

	}

	void UpdateFunction(float time, float delta_time) {
		target->setPosition(lerp_vec(start, end, time));
	}

	sf::Vector2f lerp_vec(sf::Vector2f _start, sf::Vector2f _end, float lerp) 
	{
		float x = _start.x + (_end.x - _start.x) * lerp;
		float y = _start.y + (_end.y - _start.y) * lerp;

		return { x, y };
	}
};

