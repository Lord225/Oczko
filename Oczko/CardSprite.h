#pragma once
#include "Card.h"
#include "ResourceMenager.h"
#include <SFML/Graphics.hpp>

//Sprite Karty
//Dziedziczy po sf::Drawable która impelentuje draw. Dziêki temu mo¿na wygodnie rysowaæ sprita
class CardSprite :
    public Cards::CardHash,
	public sf::Drawable
{
	std::shared_ptr<ResourceMenager> resoures;
	bool hide;

public:
	sf::Sprite spt;
	CardSprite(Cards::Color color, Cards::Value value, std::shared_ptr<ResourceMenager> resoures) : CardHash(color, value)
	{
		this->resoures = resoures;
		spt.setOrigin(0, resoures->card_height);
		spt.setTexture(resoures->cards_texture);
		ShowCard();
	}

	CardSprite(Cards::CardHash card, std::shared_ptr<ResourceMenager> resoures) : CardHash(card)
	{
		this->resoures = resoures;
		spt.setOrigin(0, resoures->card_height);
		spt.setTexture(resoures->cards_texture);
		ShowCard();
	}

	int get_points() {
		switch (value)
		{
		case Cards::card_Ace:
			return 11;
		case Cards::card_2:
			return 2;
		case Cards::card_3:
			return 3;
		case Cards::card_4:
			return 4;
		case Cards::card_5:
			return 5;
		case Cards::card_6:
			return 6;
		case Cards::card_7:
			return 7;
		case Cards::card_8:
			return 8;
		case Cards::card_9:
			return 9;
		case Cards::card_10:
			return 10;
		case Cards::card_Jack:
			return 10;
		case Cards::card_Queen:
			return 10;
		case Cards::card_King:
			return 10;
		default:
			return 0;
			break;
		}
	}

	bool isAce() {
		return value == Cards::card_Ace;
	}

	void HideCard() {
		spt.setTextureRect(this->resoures->TextureCutter.at(13*4));
		hide = true;
	}

	void ShowCard() {
		spt.setTextureRect(this->resoures->TextureCutter.at(get_hash()));
		hide = false;
	}
	bool isHide() {
		return hide;
	}
	
	CardHash get_CardHash() {
		return CardHash(this->color, this->value);
	}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
		target.draw(spt);
    }

};

