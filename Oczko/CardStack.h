#pragma once
#include <SFML/Graphics.hpp>
#include "CardSprite.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <algorithm>

#define DEG_TO_RAD (M_PI/180)

//Przyk³ad u¿ycia
//try {
//	auto card = stack.get_new_card();
//	pack.cards.push_back(card);
//}
//catch (int err) {
//	std::cout << "Cannot create new card" << std::endl;
//}

// Klasa reprezentuj¹ca Sprita ze stosem kart
class CardStack :
	public sf::Drawable,
	public sf::Transformable
{
	std::shared_ptr<ResourceMenager> resources;
	std::shared_ptr<CardSprite> blank_card;
public:
	std::vector<Cards::CardHash> used_cards;
	
	//Ilosc kart na stosie (ma³e wartoœci wygl¹daj¹ dobrze)
	int card_amount = 5;
	//Kierunek rozrostu kupki
	float direction = 135;
	//przesuniêcie na karte
	float offset = 3.0f;

	CardStack(std::shared_ptr<ResourceMenager> resources):
		resources(resources),
		blank_card(std::make_shared<CardSprite>(CardSprite(Cards::Club, Cards::card_Ace, resources)))
	{
		blank_card->HideCard();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		for (size_t i = 0; i < card_amount; i++)
		{
		
			blank_card->spt.setPosition(
				sin(direction * DEG_TO_RAD)* i * offset * getScale().x, 
				cos(direction * DEG_TO_RAD)* i * offset * getScale().y);
			
			blank_card->spt.move(getPosition());
			blank_card->spt.rotate(getRotation());
			blank_card->spt.setScale(getScale());

			target.draw(*blank_card);
		}
	}

	std::shared_ptr<CardSprite> get_new_card() {
		
		auto card = Cards::CardHash::get_random_card();

		if (used_cards.size() == 52) {
			throw -1; // nie mo¿na stworzyæ nowej karty
		}

		do {
			card = Cards::CardHash::get_random_card();
		} while (std::find(used_cards.begin(), used_cards.end(), card) != used_cards.end());
		used_cards.push_back(card);

		return std::make_shared<CardSprite>(CardSprite(card, resources));

	}

	int get_stack_points() {
		int sum = 0;
	}

};

