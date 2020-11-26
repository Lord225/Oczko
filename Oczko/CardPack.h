#pragma once
#include <SFML/Graphics.hpp>
#include "CardSprite.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define DEG_TO_RAD (M_PI/180)

//Klasa wyœwietlaj¹ca karty w "d³oni"
class CardPack :
	public sf::Drawable,
	public sf::Transformable
{
public:
	std::vector<std::shared_ptr<CardSprite>> cards;
	float rotation_start = -30;
	float rotation_end = 30;
	float rotation_radius = 50.0f;
	float pos_offset_factor = 0.04f;
	float unlinear_increase_treshold = 2.0f;
	float rise_amount = 2.0f;

	CardPack() {
		
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		
		float rotation_step = (rotation_end - rotation_start) / cards.size();
		if (rotation_step < unlinear_increase_treshold) {
			float card = cards.size() / 52.0f;
			rotation_step *= rise_amount * sqrt(card);
		}
		float actual_rotation = rotation_start;

		for (auto card : cards) {
			states.transform *= getTransform();

			card->spt.setPosition(
				cos(actual_rotation * DEG_TO_RAD* pos_offset_factor)* rotation_radius, 
				sin(actual_rotation * DEG_TO_RAD* pos_offset_factor)* rotation_radius);
			card->spt.setRotation(actual_rotation);
			
			card->spt.move(getPosition());
			card->spt.rotate(getRotation());
			card->spt.setScale(getScale());

			actual_rotation += rotation_step;

			target.draw(*card);
		}
	}
	int get_stack_points() {
		int sum = 0;
		for (auto card : cards) {
			if (!card->isHide()) {
				sum += card->get_points();
			}
		}
		if (sum == 22 && cards.size() == 2) {
			return cards[0]->isAce() && cards[1]->isAce() ? 21 : 22;
		}
		return sum;
	}

};

