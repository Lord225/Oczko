#include "ResourceMenager.h"
#include <iostream>

#define LOAD_DEBUG

#ifdef LOAD_DEBUG
#define DEBUGMSG(x) std::cout << (x) << std::endl
#else
#define DEBUGMSG(x) 
#endif


void ResourceMenager::load_all()
{
	if (!cards_texture.loadFromFile(resource_path + "/cards.png")) {
		DEBUGMSG("Cannot load /cards.png");
		return;
	}
	if (!background.loadFromFile(resource_path + "/background.png")) {
		DEBUGMSG("Cannot load /background.png");
		return;
	}
	if (!title.loadFromFile(resource_path + "/title.png")) {
		DEBUGMSG("Cannot load /title.png");
		return;
	}
	if (!selector.loadFromFile(resource_path + "/selector.png")) {
		DEBUGMSG("Cannot load /selector.png");
		return;
	}
	if (!popups.loadFromFile(resource_path + "/popups.png")) {
		DEBUGMSG("Cannot load /popups.png");
		return;
	}
	
	cards_texture.setSmooth(true);

	std_button = std::make_shared<sf::Texture>(sf::Texture());
	std_button_hover = std::make_shared<sf::Texture>(sf::Texture());
	std_button_click = std::make_shared<sf::Texture>(sf::Texture());
	font = std::make_shared<sf::Font>(sf::Font());

	if (!std_button->loadFromFile(resource_path + "/std_button_idle.png")) {
		DEBUGMSG("Cannot load /std_button_idle.png");
		return;
	}
	if (!std_button_hover->loadFromFile(resource_path + "/std_button_hover.png")) {
		DEBUGMSG("Cannot load /std_button_hover.png");
		return;
	}
	if (!std_button_click->loadFromFile(resource_path + "/std_button_click.png")) {
		DEBUGMSG("Cannot load /std_button_click.png");
		return;
	}
	if (!font->loadFromFile(resource_path + "/Roboto-Bold.ttf")) {
		DEBUGMSG("Cannot load /Bold.ttf");
		return;
	}

	auto size = cards_texture.getSize();
	
	// Generowanie atlasu dla kart.
	// card_value_x - typ karty,   wed³ug enuma w Cards
	// card_color_y - kolor karty, wed³ug enuma w Cards
	this->TextureCutter.resize(4 * 13 + 1);
	for (size_t card_value_x = 0, offset_x = 0; 
		card_value_x < 13; 
		card_value_x++, offset_x += card_x_step
		)
	{
		for (size_t card_color_y = 0, offset_y = 0; 
			card_color_y < 4; 
			card_color_y++, offset_y += card_y_step
			)
		{
			this->TextureCutter[Cards::CardHash::get_hash(card_color_y, card_value_x)] = sf::IntRect(offset_x, offset_y, card_wight, card_height);
		}
	}
	this->TextureCutter[4*13] = sf::IntRect(296, 920, card_wight, card_height); //Zakryta Karta

	_isLoaded = true;
}

ResourceMenager::ResourceMenager(std::string&& resource_path, std::string&& save_path)
{
	this->resource_path = resource_path;
	this->save_path = save_path;
}

void ResourceMenager::load()
{
	return;
}

void ResourceMenager::save()
{
	return;
}