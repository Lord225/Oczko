#pragma once
#include <SFML/Graphics.hpp>
#include "CardSprite.h"
#define _USE_MATH_DEFINES

template<size_t N>
class Popup:
	public sf::Drawable
{
	std::shared_ptr <ResourceMenager> resources;
	sf::IntRect rects[N];
public:
	sf::Sprite popup;
	Popup(std::shared_ptr <ResourceMenager> resources) : resources(resources)
	{
		popup.setTexture(resources->popups);
		auto size = sf::Vector2f(popup.getTexture()->getSize());
		popup.setOrigin(size.x*0.5f,size.y/(2*N));
		for (size_t i = 0; i < N; i++)
		{
			rects[i] = 
				sf::IntRect(
					sf::Vector2i(0, i*popup.getTexture()->getSize().y / N),
					sf::Vector2i(popup.getTexture()->getSize().x, popup.getTexture()->getSize().y/ N )
				);
		}
	}

	void set_type(int type) {
		popup.setTextureRect(rects[type]);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		

		target.draw(this->popup);
	}

};

