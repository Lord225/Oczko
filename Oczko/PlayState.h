#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

#include "Bot.h"
#include "Popup.h"
#include "Player.h"
#include "Dealer.h"
#include "Mapping.h"
#include "CardPack.h"
#include "CardStack.h"
#include "GameButton.h"
#include "WaitAnimation.h"
#include "FadeInAnimation.h"
#include "TranslateAnimation.h"


using Vec2 = sf::Vector2f;

//Klasa gry
class PlayState :
    public GameState
{
public:
    enum GAME_STATE {
        DEALER_TAKES_CARDS,
        DEALER_TAKES_CARDS2,
        PLAYER_TAKES_CARDS,
        PLAYER_TAKES_CARDS2,
        BOT1_TAKES_CARDS,
        BOT1_TAKES_CARDS2,
        BOT2_TAKES_CARDS,
        BOT2_TAKES_CARDS2,


        AFTER_BOT1_DECISION_POPUP,
        AFTER_BOT2_DECISION_POPUP,
        AFTER_PLAYER_DECISION_POPUP,


        BOT_ONE_DECISION,
        BOT_TWO_DECISION,
        
        BOT1_EXEC_DECISION,
        BOT2_EXEC_DECISION,
        PLAYER_MAKES_DECISION,
    
        POPUP_ANIM,
        POPUP_STAY,

        END_OF_GAME_SEQUANCE,

        SHOW_HIDDEN_CARD,

        SHOW_HIDDEN_CARD_DELAY,

        TAKE_NEW_CARD,

        END_OF_GAME_POPUP,

        LEAVE,
        
        MAIN_MENU_BUTTON

    };
    enum PLAYER_ACTION {
        NONE,
        HIT,
        STAY,
    };

private:
    GAME_STATE state = DEALER_TAKES_CARDS;
    PLAYER_ACTION action = NONE;

    sf::Sprite background;


    std::shared_ptr<GameButton> take_card_button;
    std::shared_ptr<GameButton> pass_button;
    std::shared_ptr<GameButton> main_menu;

    std::shared_ptr<CardStack> cards;


    std::shared_ptr<Bot> bot1;
    std::shared_ptr<Bot> bot2;


    std::shared_ptr<Player> player;
    std::shared_ptr<Dealer> dealer;

    std::unique_ptr<Animation> animation_handeler;
    std::shared_ptr<CardSprite> current_animated_card;
    std::shared_ptr<Popup<4>> popups;

    
    Vec2 cards_positions[3] = 
    { 
        { 0.20, 0.1}, 
        {-0.15, 0.4}, 
        {-0.50, 0.1} 
    };
    Vec2 dealer_pos = { -0.15, -0.5 };
    
    int selector_pos = 0;
    int popupval = -2;
    bool show_selector = false;
    bool show_popup = false;
    bool endered_end_of_game_seq = false;

    std::shared_ptr<sf::Sprite> selector;
    float selector_size = 0.3f;

    float card_stack_size      = 0.4f;
    float bot_card_size        = 0.3f;
    float player_card_size     = 0.36f;
    float dealer_card_size     = 0.36f;
    float animated_card_size   = 0.36f;

    float button_spacing  = 0.4f;
    float button_scale    = 0.25f;
    float padding_top     = 0.25f;
    
public:
    PlayState(std::shared_ptr<ResourceMenager> resouree, sf::Window* target);
    void update(float delta_time) override;
    void render(sf::RenderWindow& target) override;
    void onResize(int new_w, int new_h) override;
    void onStart() override;

    // Game logic functions
    void dealer_takes_cards(float delta_time);
    void bot1_takes_init_cards(float delta_time);
    void bot2_takes_init_cards(float delta_time);

    bool take_cards(CardPack& target, float delta_time);
    bool show_selector_anim(int id, float delta_time);
    bool bot_makes_decision(Bot& bot, float delta_time);

    void player_takes_init_cards(float delta_time);
    
    bool pop_up_animation(int s, float delta_time, bool clickable);

    bool stay_anim(float time, float delta_time);

    //-1=Busted, 0=Fine, 1=BlackJack
    int check_cards(CardPack& cards);

    void onTakeCardButton();


    void onPassButton();

    void onMainMenuButton();
};

class STATE_WATCHER {
    static PlayState::GAME_STATE state;
public:
    static void update(PlayState::GAME_STATE actual_state) {
        if (actual_state != state) {
            std::cout << "STATE CHANGE: " << state << "->"<< actual_state << std::endl;
            state = actual_state;
        }
    }
};