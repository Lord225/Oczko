#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"


class MainMenuButton :
    public Button
{
public:
	enum ButtonID {
		exit,
		play
	};
	ButtonID id;
	MainMenuButton(
		std::string&& text,
		sf::Vector2f pos,
		MainMenuButton::ButtonID id,
		std::shared_ptr<ResourceMenager> resources
	);
	void OnHover();

	void OnClick();

};

