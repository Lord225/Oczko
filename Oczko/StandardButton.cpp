#include "StandardButton.h"

StandardButton::StandardButton(
	std::string&& text,
	sf::Vector2f pos,
	std::shared_ptr<ResourceMenager> resources,
	sf::Color text_color
)
{
	this->display_text.setString(text);
	this->display_text.setFont(resources->font);
	this->display_text.setFillColor(text_color);

	this->hitbox = sf::FloatRect(pos, sf::Vector2f(resources->std_button->getSize()));
	this->setPosition(pos);

	this->rest_look = resources->std_button;
	this->hover_look = resources->std_button_hover;
	this->click_look = resources->std_button_click;
}
