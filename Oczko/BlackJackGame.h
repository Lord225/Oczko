#pragma once
#include <memory>
#include "Card.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "Mapping.h"

// G³ówna klasa gry. Zawiera wszystko zwi¹zanie z gr¹. Ale g³ównie - resources i wektor stanów
class BlackJackGame
{
	std::shared_ptr<ResourceMenager> resoures;
	std::vector<std::shared_ptr<GameState>> states;
	int current_state = 0;
	sf::Window* target;
public:
	static const sf::Vector2f screen_size;

	BlackJackGame(std::shared_ptr<ResourceMenager> resoures, sf::Window* target) : target(target) {
		this->resoures = resoures;

		current_state = 0;
		states.reserve(3);

		states.emplace_back(std::make_shared<MainMenuState>(MainMenuState(resoures, target)));
		states.emplace_back(std::make_shared<PlayState>(PlayState(resoures, target)));
	}

	//Inicjalizacja
	void OnStart(sf::RenderWindow& window,int w, int h) {
		if (!resoures->isLoaded()) {
			throw std::exception("Recources not loaded");
		}

		Mapping::windows_size = sf::Vector2f(w, h);

		for (size_t i = 0; i < states.size(); i++)
		{
			states[i]->window_size = { (float)w, (float)h };
			states[i]->isButtonRelased = false;
			states[i]->onStart();
			states[i]->onResize(w, h);
		}
		OnResize(window, { (float)w, (float)h });
	}

	//Przy ka¿dej klatce odœwie¿y aktualny state + wywa³a ich funckje
	bool update(sf::RenderWindow & window, float delta_time) 
	{
		states[current_state]->mouse_pos = sf::Mouse::getPosition();
		states[current_state]->time += delta_time;

		states[current_state]->update(delta_time);
		states[current_state]->render(window);

		if (states[current_state]->isButtonRelased) {
			states[current_state]->isButtonRelased = false;
		}

		if (GameState::isExit == true) {
			return true;
		}

		if (current_state != GameState::isScenSwap) {
			if (GameState::isScenSwap == 1) {
				states[1] = std::make_shared<PlayState>(PlayState(resoures, target));

				OnStart(window, Mapping::windows_size.x, Mapping::windows_size.y);
			}

		}
		current_state = GameState::isScenSwap;

		return false;
	}

	//wywo³ywanie przy zmianie rozdzielczoœci
	void OnResize(sf::RenderWindow& window, sf::Vector2f size) {
		Mapping::windows_size = sf::Vector2f(size.x, size.y);

		states[current_state]->window_size = size;
		states[current_state]->onResize(size.x, size.y);
			
		window.setView(sf::View(sf::FloatRect(0, 0, size.x, size.y)));
	}

	void OnButtonRelase() {
		states[current_state]->isButtonRelased = true;
	}

private:


};

