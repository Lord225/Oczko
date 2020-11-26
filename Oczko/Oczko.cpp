#include <SFML/Graphics.hpp>
#include <memory>
#include <time.h>
#include "BlackJackGame.h"
#include "ResourceMenager.h"
#include "CardPack.h"
#include "CardStack.h"
#include "TranslateAnimation.h"

#define LOCK_FPS 60

// Przy próbie kompilacji proszę ustawić tą ścieżkę na bezpośrednią do folderu Resources
#define RESOURCE_PATH "Resources"
#define SAVES_PATH ""

const float default_window_ratio = 16.0f / 9.0f;
const int default_window_size = 500;

int main()
{
    srand(time(0));
    auto resources = std::make_shared<ResourceMenager>(ResourceMenager(RESOURCE_PATH, SAVES_PATH));
    
    resources->load_all();

    if (!resources->isLoaded()) {
        std::cout << "Cannot load nesesery resources. Check if Resource folder is in this dir: " << RESOURCE_PATH << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(default_window_ratio*default_window_size, default_window_size), "BlackJack");
    if (!window.isOpen()) {
        std::cout << "Cannot open window (why?) " << std::endl;
    }

#ifdef LOCK_FPS
    window.setFramerateLimit(LOCK_FPS);
#endif

    sf::Event event;
    sf::Clock deltaClock;

    BlackJackGame game_instance(resources, &window);

    game_instance.OnStart(window, default_window_ratio * default_window_size, default_window_size);

    int counter = 0;


    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
                game_instance.OnResize(window, { (float)event.size.width, (float)event.size.height });
            
            if (event.type == sf::Event::MouseButtonReleased) 
                game_instance.OnButtonRelase();
            
        }
        
        sf::Time dt = deltaClock.restart();

        window.clear();

        if (game_instance.update(window, dt.asSeconds()))
            window.close();


        window.display();

        counter++;
    }

    return 0;
}