#pragma once
#include "CardStack.h"
#include "CardPack.h"


class Dealer
{
	std::shared_ptr<ResourceMenager> resoures;
public:
	CardPack Cards;
	sf::Text name;

	Dealer(std::string&& name, std::shared_ptr<ResourceMenager> resoures) : resoures(resoures)
	{
		this->name.setString(name);
		this->name.setFont(*(resoures->font));
	}
	void update() {

	}


};

