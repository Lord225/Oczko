#pragma once
#include <memory>
#include "ResourceMenager.h"
#include <SFML/Graphics.hpp>


//Interfejs dla stanów gry. Zawiera wskaŸnik na zasoby i podstawowe informacje o grze.
//Wymaga implementacji trzech podstawowych funkcji.
class GameState {
public:
	static bool isExit;
	static int isScenSwap;

	GameState(std::shared_ptr<ResourceMenager> resoures, sf::Window* target) {
		this->resoures = resoures;
		this->target = target;
		time = 0;
	}
	
	float time = 0;
	bool isButtonRelased = false;
	std::shared_ptr<ResourceMenager> resoures;
	sf::Window* target;
	sf::Vector2i mouse_pos;
	sf::Vector2f window_size;

	virtual void onStart() = 0; 
	virtual void update(float delta_time) = 0;
	virtual void render(sf::RenderWindow& target) = 0;
	virtual void onResize(int new_w, int new_h) = 0;
};