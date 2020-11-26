#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Card.h"


// Aby zapobiec duplikacji du�ych i drogich danych, wszystkie wczytuje i trzymam w jednym miejscu
// Obiekty maj� dost�p jednynie do wska�nika
// Je�eli by�bym sprytny to stworzy� bym klas� statyczn�, nie trzeba by dodawa� 
// std::shared_ptr<ResourceData> do ka�dego obiektu kt�ry musi z tego korzysta� 
class ResourceData {
public:
	sf::Texture cards_texture;
	sf::Texture background;
	sf::Texture title;
	sf::Texture selector;
	sf::Texture popups;

	std::shared_ptr<sf::Texture> std_button;
	std::shared_ptr<sf::Texture> std_button_hover;
	std::shared_ptr<sf::Texture> std_button_click;

	std::shared_ptr <sf::Font> font;
	std::vector<sf::IntRect> TextureCutter;

	const int card_wight  = 147;
	const int card_x_step = 148;
	const int card_height = 230;
	const int card_y_step = 230;
};

class ResourceMenager : public ResourceData
{
	std::string resource_path;
	std::string save_path;
	bool _isLoaded = false;
public:
	
	ResourceMenager(std::string&& resource_path, std::string&& save_path);

	//Wczytuje wszystkie potrzebne grze zasoby
	void load_all();

	//Zapisuje savay (tabele wynik�w ect)
	void save();

	//Wczytuje savy (tabele wynik�w ect)
	void load();

	bool isLoaded() {
		return _isLoaded;
	}
};


