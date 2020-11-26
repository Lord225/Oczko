#pragma once
#include "GameState.h"
#include "Mapping.h"
#include <SFML/Graphics.hpp>
#include "MainMenuButton.h"

//Klasa menu g³ównego
class MainMenuState :
    public GameState
{
    sf::Sprite background;
    sf::Sprite title;
    std::shared_ptr<MainMenuButton> start_button;
    std::shared_ptr<MainMenuButton> exit_button;

public:

    MainMenuState(std::shared_ptr<ResourceMenager> resouree, sf::Window* target);
    void update(float delta_time) override;
    void render(sf::RenderWindow& target) override;
    void onResize(int new_w, int new_h) override;
    void onStart() override;

    static void ExitEvent() {
        GameState::isExit = true;
    }

    static void GameStartEvent() {
        GameState::isScenSwap = 1;
    }
};

