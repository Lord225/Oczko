#include "MainMenuButton.h"


MainMenuButton::MainMenuButton(
	std::string&& text, 
	sf::Vector2f pos, 
	MainMenuButton::ButtonID id, 
	std::shared_ptr<ResourceMenager> resources) : id(id)
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

void MainMenuButton::OnHover()
{

}

void MainMenuButton::OnClick()
{
	switch (id)
	{
	case MainMenuButton::exit:
		GameState::isExit = true;
		break;
	case MainMenuButton::play:
		GameState::isScenSwap = 1;
		break;
	default:
		break;
	}
}

