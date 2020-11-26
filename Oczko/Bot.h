#pragma once
#include "CardStack.h"
#include "CardPack.h"

class Bot
{
	std::shared_ptr<ResourceMenager> resoures;
public:
	CardPack BotsCards;
	sf::Text name;
	bool stay_flag = false;

	Bot(std::string && name,std::shared_ptr<ResourceMenager> resoures) : resoures(resoures)
	{
		this->name.setString(name);
		this->name.setFont(*(resoures->font));
	}
	bool make_decision(int dealer_points) 
	{
		if (BotsCards.get_stack_points() < 17) {
			return true;
		}
		return !(rand() % 3);
	}

private:

};

