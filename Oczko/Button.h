#pragma once
#include <memory>
#include "ResourceMenager.h"
#include "Mapping.h"
#include <SFML/Graphics.hpp>

//#define BUTTON_DEBUG

//Ogólna klasa przycisku
class Button :
	sf::Drawable
{
public:
	float text_scale = 2.0f;
	int next_frame_action = 0;
	sf::Sprite display;
	std::shared_ptr<sf::Texture> rest_look;
	std::shared_ptr<sf::Texture> hover_look;
	std::shared_ptr<sf::Texture> click_look;
	

	sf::Text display_text;
	sf::FloatRect hitbox;
	static int isAllButtonsBloced; //zero oznacza dzialajace przyciski (Hover dzia³a dalej)
	
	Button() {}

	Button(
		std::string&& text,
		sf ::Vector2f pos,
		sf ::Vector2f size,
		std::shared_ptr<sf::Texture> rest_look,
		std::shared_ptr<sf::Texture> hover_look,
		std::shared_ptr<sf::Texture> click_look,
		std::shared_ptr<sf::Font> Font,
		sf::Color text_color
	);
	
	void setPosition(float x, float y) {
		setPosition({ x,y });
	}

	void setPosition(sf::Vector2f pos);
	
	void setScale(float x, float y) {
		setScale({ x,y });
	}
	void setScale(sf::Vector2f scale);

	void construct_helper(
		std::string&& text,
		sf::Vector2f pos,
		sf::Vector2f size,
		std::shared_ptr<sf::Texture> rest_look,
		std::shared_ptr<sf::Texture> hover_look,
		std::shared_ptr<sf::Texture> click_look,
		std::shared_ptr<sf::Font> Font,
		sf::Color text_color
	);
	void set_text_origin() {
		auto bouds = display_text.getLocalBounds();
		display_text.setOrigin(bouds.left + bouds.width / 2.0f,
			bouds.top + bouds.height / 2.0f);
	}
	void set_text_size(int size) {
		display_text.setCharacterSize(size);
	}
	//Trackuje klikniêcia i wywo³uje funkcje wirtualne
	void update(sf::Window& target);

	virtual void OnHover() = 0;

	virtual void OnClick() = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

