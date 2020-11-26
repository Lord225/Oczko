#pragma once
#include <SFML/Graphics.hpp>

// Statyczna klasa mapuj¹ca koordynaty
// SFML nie zawiera ¿adnych klas pomocniczych 
// je¿eli chodzi o rozk³ad UI wiêc wszystko musi byæ mapowane rêcznie

class Mapping
{
public:
	static sf::Vector2f windows_size;
	static float aspect_ratio;
	static const bool use_aspect_ratio;

	static void set_window_size(int size_w, int size_h) {
		windows_size.x = size_w;
		windows_size.y = size_h;
	}
	static sf::Vector2f ToGlobal(float x, float y) {
		return ToGlobal(sf::Vector2f(x, y));
	}

	//Zamienia wspó³rzêdne z zakresu <-1,1> na przestrzeñ ekranu
 	static sf::Vector2f ToGlobal(sf::Vector2f local) {
		local += {1.0f, 1.0f};
		local *= 0.5f;
		if (use_aspect_ratio) {
			return sf::Vector2f(local.x * windows_size.x,
				                local.y*(1/aspect_ratio)* windows_size.x);
			
		}
		return sf::Vector2f(local.x * windows_size.x,
							local.y * windows_size.y);
	}
	
	//Zwraca skalê przez któr¹ obiekt zajmie ca³¹ szerokoœæ
	static float FitToX(sf::Vector2f size) {
		return (windows_size.x / size.y) * size.y / size.x;
	}
	
	//Zwraca skalê przez któr¹ obiekt zajmie ca³¹ wysokoœæ
	static float FitToY(sf::Vector2f size) {
		return (windows_size.x / size.y) * size.y / size.x;
	}

};

