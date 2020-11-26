#pragma once
class Player
{
	std::shared_ptr<ResourceMenager> resoures;
public:
	CardPack PlayerCards;
	sf::Text name;
	bool stay_flag = false;
	bool BlackJacked = false;
	bool isBusted = false;

	Player(std::string && name, std::shared_ptr<ResourceMenager> resoures) : resoures(resoures)
	{
		this->name.setString(name);
		this->name.setFont(*(resoures->font));
	}

	void update() {

	}


private:
};

