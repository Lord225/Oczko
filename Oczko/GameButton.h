#pragma once
#include "Button.h"
#include <functional>
// Ulepszona klasa przycisku 
class GameButton :
    public Button
{
	std::function<void()> on_click;

public:
	GameButton(
		std::string&& text,
		sf::Vector2f pos,
		std::function<void()> on_click,
		std::shared_ptr<ResourceMenager> resources
	): on_click(on_click)
	{
		auto texture_size = sf::Vector2f(resources->std_button->getSize());
		construct_helper(
			std::move(text),
			pos,
			texture_size,
			resources->std_button,
			resources->std_button_hover,
			resources->std_button_click,
			resources->font,
			sf::Color::White
		);
	}
	void OnHover() {

	}

	void OnClick() {
		on_click();
	}
private:

};

