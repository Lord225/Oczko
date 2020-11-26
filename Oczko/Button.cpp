#include "Button.h"

int Button::isAllButtonsBloced = 0;

Button::Button(
	std::string&& text,
	sf::Vector2f pos,
	sf::Vector2f size,
	std::shared_ptr<sf::Texture> rest_look,
	std::shared_ptr<sf::Texture> hover_look,
	std::shared_ptr<sf::Texture> click_look,
	std::shared_ptr<sf::Font> Font,
	sf::Color text_color)
{
	construct_helper(
		std::move(text),
		pos,
		size,
		rest_look,
		hover_look,
		click_look,
		Font,
		text_color
	);
}

void Button::construct_helper(
	std::string&& text,
	sf::Vector2f pos,
	sf::Vector2f size,
	std::shared_ptr<sf::Texture> rest_look,
	std::shared_ptr<sf::Texture> hover_look,
	std::shared_ptr<sf::Texture> click_look,
	std::shared_ptr<sf::Font> Font,
	sf::Color text_color) 
{
	display_text.setFont(*Font);
	display_text.setFillColor(text_color);
	display_text.setString(text);
	
	next_frame_action = false;

	this->rest_look = rest_look;
	this->hover_look = hover_look;
	this->click_look = click_look;

	display.setTexture(*click_look);
	set_text_size(72);

	auto texture_size = sf::Vector2f(display.getTexture()->getSize());

	display.setOrigin(texture_size * 0.5f);

	set_text_origin();
	
	
	hitbox = sf::FloatRect(pos, size);

	setPosition(pos);
}

void Button::setPosition(sf::Vector2f pos) {
	display_text.setPosition(pos);
	display.setPosition(pos);
	auto texture_size = sf::Vector2f(display.getTexture()->getSize());
	hitbox.left = pos.x- texture_size.x*display.getScale().x/2;
	hitbox.top = pos.y - texture_size.y * display.getScale().y/2;
}
void Button::setScale(sf::Vector2f scale) {
	display_text.setScale(scale*2.0f);
	set_text_origin();
	display.setScale(scale);
	auto size = sf::Vector2f(rest_look->getSize());
	hitbox.width = size.x*scale.x;
	hitbox.height = size.y* scale.y;
}

void Button::update(sf::Window& target) {
	auto pos = sf::Vector2f(sf::Mouse::getPosition(target));

	if (next_frame_action) {
		OnClick();
		next_frame_action -= 1;
	}

	if (isAllButtonsBloced) {
		display.setColor(sf::Color(255, 255, 255, 128));
		display_text.setFillColor(sf::Color(255, 255, 255, 128));
		display.setTexture(*rest_look);
		return;
	}
	else {
		display.setColor(sf::Color(255, 255, 255, 255));
		display_text.setFillColor(sf::Color(255, 255, 255, 255));
	}

	if (hitbox.contains(pos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			display.setTexture(*click_look);
			next_frame_action = 2;
		}
		else {
			display.setTexture(*hover_look);
			OnHover();
		}
	}
	else {
		display.setTexture(*rest_look);
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

#ifdef BUTTON_DEBUG
	sf::RectangleShape a({ hitbox.width , hitbox.height });
	a.setPosition(hitbox.left, hitbox.top);
	target.draw(a);
#endif

	target.draw(display);
	target.draw(display_text);
	
}