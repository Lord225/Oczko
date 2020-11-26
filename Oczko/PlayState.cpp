#include "PlayState.h"

#define DEBUG_STATES



PlayState::PlayState(std::shared_ptr<ResourceMenager> resoures, sf::Window* target)
	: GameState(resoures, target)
{}

void PlayState::onStart()
{
	background.setTexture(this->resoures->background);

	std::function<void()> on_pass_bind = std::bind(&PlayState::onPassButton, this);
	std::function<void()> on_take_bind = std::bind(&PlayState::onTakeCardButton, this);
	std::function<void()> on_main_manu = std::bind(&PlayState::onMainMenuButton, this);

	pass_button = std::make_shared<GameButton>(
		GameButton(
			"STAY",
			Mapping::ToGlobal(-0.2, 0.7),
			on_pass_bind,
			resoures
			)
		);
	take_card_button = std::make_shared<GameButton>(
		GameButton(
			"HIT",
			Mapping::ToGlobal(0.2, 0.7),
			on_take_bind,
			resoures
			)
		);
	main_menu = std::make_shared<GameButton>(
		GameButton(
			"MENU",
			Mapping::ToGlobal(0.0, 0.0),
			on_main_manu,
			resoures
		)
		);

	auto size = Vec2(pass_button->display.getTexture()->getSize());
	float scale = Mapping::FitToX(size) * button_scale;

	pass_button->setScale(scale, scale);
	take_card_button->setScale(scale, scale);
	main_menu->setScale(scale, scale);

	cards = std::make_shared<CardStack>(CardStack(resoures));
	cards->setPosition(Mapping::ToGlobal(0.2, -0.7));

	size = Vec2(pass_button->display.getTexture()->getSize());
	float card_stack_size = Mapping::FitToX(size) * button_scale;
	cards->setScale(card_stack_size, card_stack_size);

	bot1     = std::make_shared<Bot>(Bot("Bot 1",resoures));
	bot2     = std::make_shared<Bot>(Bot("Bot 2", resoures));
	player   = std::make_shared<Player>(Player("You", resoures));
	dealer   = std::make_shared<Dealer>(Dealer("Dealer", resoures));
	selector = std::make_shared<sf::Sprite>(sf::Sprite());
	popups   = std::make_shared<Popup<4>>(Popup<4>(resoures));

	//bot1->BotsCards.setRotation(-30);
	//bot2->BotsCards.setRotation(30);

	selector->setTexture(resoures->selector);
	selector->setOrigin(Vec2(selector->getTexture()->getSize()) * 0.5f);
	selector->setColor(sf::Color(255, 255, 255, 128));

}

bool PlayState::take_cards(CardPack & target, float delta_time)
{
	if (animation_handeler == nullptr)
	{

		current_animated_card.reset();

		current_animated_card = cards->get_new_card();

		if (state == DEALER_TAKES_CARDS2) {
			current_animated_card->HideCard();
		}

		auto size = Vec2(pass_button->display.getTexture()->getSize());
		card_stack_size = Mapping::FitToX(size) * animated_card_size;
		current_animated_card->spt.setScale(card_stack_size, card_stack_size);
		

		animation_handeler = std::make_unique<TranslateAnimation>(
			TranslateAnimation(
				&current_animated_card->spt,
				cards->getPosition(),
				target.getPosition(),
				0.3f,
				true
			));
		animation_handeler->TriggerAnimation();

	}
	else {
		if (animation_handeler->isPlaying())
		{
			animation_handeler->Update(delta_time);
		}
		else
		{
			animation_handeler.reset();

			target.cards.emplace_back(current_animated_card);
			return true;
		}
	}
	return false;

}

void PlayState::dealer_takes_cards(float delta_time)
{
	if (take_cards(dealer->Cards, delta_time)) {
		if (state == DEALER_TAKES_CARDS) {
			state = DEALER_TAKES_CARDS2;
		}
		else {
			state = BOT1_TAKES_CARDS;
		}
	}
}

void PlayState::bot1_takes_init_cards(float delta_time)
{
	if (take_cards(bot1->BotsCards, delta_time)) {
		if (state == BOT1_TAKES_CARDS) {
			state = BOT1_TAKES_CARDS2;
		}
		else {
			state = BOT2_TAKES_CARDS;
		}
	}
}

void PlayState::bot2_takes_init_cards(float delta_time)
{
	if (take_cards(bot2->BotsCards, delta_time)) {
		if (state == BOT2_TAKES_CARDS) {
			state = BOT2_TAKES_CARDS2;
		}
		else {
			state = PLAYER_TAKES_CARDS;
		}
	}
}

void PlayState::player_takes_init_cards(float delta_time)
{
	if (take_cards(player->PlayerCards, delta_time)) {
		if (state == PLAYER_TAKES_CARDS) {
			state = PLAYER_TAKES_CARDS2;
		}
		else {
			state = AFTER_BOT1_DECISION_POPUP;
		}
	}
}

bool PlayState::bot_makes_decision(Bot& bot, float delta_time)
{
	bool decision = bot.make_decision(dealer->Cards.get_stack_points());

	if (animation_handeler == nullptr)
	{
		animation_handeler = std::make_unique<WaitAnimation>(
			WaitAnimation(
				0.3f + (rand() % 1000)/1000.0f * 0.4f,
				true
			));
		animation_handeler->TriggerAnimation();

	}
	else {
		if (animation_handeler->isPlaying())
		{
			animation_handeler->Update(delta_time);
		}
		else
		{
			animation_handeler.reset();

			if (decision) {
				std::cout << "BOT: HIT" << std::endl;
				action = HIT;
			}
			else {
				std::cout << "BOT: STAY" << std::endl;
				action = STAY;
			}

			return true;
		}
	}
	return false;
}

bool PlayState::show_selector_anim(int id, float delta_time)
{
	if (animation_handeler == nullptr)
	{
		show_selector = true;
		selector_pos = id;

		switch (selector_pos) {
		case 0:
			selector->setPosition(bot1->BotsCards.getPosition());
			break;
		case 1:
			selector->setPosition(player->PlayerCards.getPosition());
			break;
		case 2:
			selector->setPosition(bot2->BotsCards.getPosition());
			break;
		}

		selector->setScale(selector_size, selector_size);
		animation_handeler = std::make_unique<FadeInAnimation>(
			FadeInAnimation(
				(sf::Sprite*)selector.get(),
				0.4f,
				selector_size,
				0.2f,
				0.0f,
				0.7f,
				true
			));
		animation_handeler->TriggerAnimation();
	}
	else {
		if (animation_handeler->isPlaying()) {
			animation_handeler->Update(delta_time);
		}
		else 
		{
			animation_handeler.reset();
			
			return true;
		}
	}
	return false;
}

int PlayState::check_cards(CardPack& cards)
{
	int points = cards.get_stack_points();

	if (points > 21) {
		return -1;
	}
	if (points < 21) {
		return 0;
	}
	if (points == 21) {
		return 1;
	}

	return 0;
}

bool PlayState::pop_up_animation(int s, float delta_time, bool clickable)
{
	if (animation_handeler == nullptr)
	{
		popups->popup.setPosition(Mapping::ToGlobal(0, 0));
		popups->set_type(s);
		show_popup = true;

		animation_handeler = std::make_unique<FadeInAnimation>(
			FadeInAnimation(
				&(popups->popup),
				2.0f,
				1.6f,
				0.3f,
				0.0f,
				1.0f,
				clickable
			));
		animation_handeler->TriggerAnimation();
	}
	else {
		if (animation_handeler->isPlaying()) {
			animation_handeler->Update(delta_time);
		}
		else
		{
			animation_handeler.reset();

			return true;
		}
	}
	return false;


}

bool PlayState::stay_anim(float time, float delta_time)
{
	if (animation_handeler == nullptr)
	{
		animation_handeler = std::make_unique<WaitAnimation>(
			WaitAnimation(
				time,
				true
			));
		animation_handeler->TriggerAnimation();

	}
	else {
		if (animation_handeler->isPlaying())
		{
			animation_handeler->Update(delta_time);
		}
		else
		{
			animation_handeler.reset();

			return true;
		}
	}
	return false;
}

void PlayState::update(float delta_time)
{
#ifdef DEBUG_STATES
	STATE_WATCHER::update(this->state);
#endif

	pass_button->update(*target);
	take_card_button->update(*target);
	main_menu->update(*target);

	if (state != PLAYER_MAKES_DECISION) {
		Button::isAllButtonsBloced = 2;
	}
	else {
		Button::isAllButtonsBloced = 0;
	}



	switch (state)
	{
	case PlayState::DEALER_TAKES_CARDS:
	case PlayState::DEALER_TAKES_CARDS2:
		dealer_takes_cards(delta_time);
		break;
	case PlayState::PLAYER_TAKES_CARDS:
	case PlayState::PLAYER_TAKES_CARDS2:
		player_takes_init_cards(delta_time);
		break;
	case PlayState::BOT1_TAKES_CARDS:
	case PlayState::BOT1_TAKES_CARDS2:
		bot1_takes_init_cards(delta_time);
		break;
	case PlayState::BOT2_TAKES_CARDS:
	case PlayState::BOT2_TAKES_CARDS2:
		bot2_takes_init_cards(delta_time);
		break;
	case PlayState::AFTER_BOT1_DECISION_POPUP:
		if (show_selector_anim(0, delta_time)) {
			state = BOT_ONE_DECISION;
		}
		break;
	case PlayState::AFTER_BOT2_DECISION_POPUP:
		if (show_selector_anim(2, delta_time)) {
			state = BOT_TWO_DECISION;
		}
		break;
	case PlayState::AFTER_PLAYER_DECISION_POPUP:
		if (show_selector_anim(1, delta_time)) {
			state = PLAYER_MAKES_DECISION;
		}
		break;
	case PlayState::BOT_ONE_DECISION:
		if (bot1->stay_flag == true) {
			state = BOT1_EXEC_DECISION; //skip popups
			action = NONE;
			break;
		}
		if (bot_makes_decision(*bot1.get(), delta_time)) {
			state = BOT1_EXEC_DECISION;
		}
		break;
	case PlayState::BOT_TWO_DECISION:
		if (bot2->stay_flag == true) {
			state = BOT2_EXEC_DECISION; //skip popups
			action = NONE;
			break;
		}
		if (bot_makes_decision(*bot2.get(), delta_time)) {
			state = BOT2_EXEC_DECISION;
		}
		break;
	case PlayState::PLAYER_MAKES_DECISION:
		if (player->stay_flag == true) {
			state = AFTER_BOT1_DECISION_POPUP; //skip popups
			action = NONE;
		}
		if (action == STAY) {
			player->stay_flag = true;
			state = AFTER_BOT1_DECISION_POPUP;
			action = NONE;
		}
		else if (action == HIT) {
			if (take_cards(player->PlayerCards, delta_time)) {
				state = POPUP_ANIM;
				action = NONE;
			}
		}
		popupval = check_cards(player->PlayerCards);
		break;
	case PlayState::BOT1_EXEC_DECISION:
		if (action == STAY || bot1->stay_flag == true) {
			bot1->stay_flag = true;
			state = AFTER_BOT2_DECISION_POPUP;
			action = NONE;
		}
		else if (action == HIT) {
			if (take_cards(bot1->BotsCards, delta_time)) {
				if (check_cards(bot1->BotsCards) != 0) {
					bot1->stay_flag = true;
				}
				state = AFTER_BOT2_DECISION_POPUP;
				action = NONE;
			}
		}
		break;
	case PlayState::BOT2_EXEC_DECISION:
		if (action == STAY || bot2->stay_flag == true) {
			bot2->stay_flag = true;
			state = AFTER_PLAYER_DECISION_POPUP;
			action = NONE;
		}
		else if (action == HIT) {
			if (take_cards(bot2->BotsCards, delta_time)) {
				if (check_cards(bot2->BotsCards) != 0) {
					bot2->stay_flag = true;
				}
				state = AFTER_PLAYER_DECISION_POPUP;
				action = NONE;
			}
		}
		break;
	case PlayState::POPUP_ANIM:
		if (popupval != 0) {
			if (popupval == -1) {
				if (pop_up_animation(0, delta_time, false)) {
					player->stay_flag = true;
					state = POPUP_STAY;
					player->isBusted = true;
				}
			}
			if (popupval == 1) {
				if (pop_up_animation(1, delta_time, false)) {
					player->stay_flag = true;
					state = POPUP_STAY;
					player->BlackJacked = true;
				}
			}
		}
		else {
			state = POPUP_STAY;
		}
		break;
	case PlayState::POPUP_STAY:
		//END OF TOUR
		if (stay_anim(2.0f, delta_time)) {
			std::cout << "END OF TOUR" << std::endl;
			show_popup = false;
			state = AFTER_BOT1_DECISION_POPUP;
		}
		break;

	case PlayState::END_OF_GAME_SEQUANCE:
		if (stay_anim(2.0f, delta_time)) {
			state = SHOW_HIDDEN_CARD;
		}
		break;
	case PlayState::SHOW_HIDDEN_CARD_DELAY:
		if (stay_anim(1.5f, delta_time)) {
			if (dealer->Cards.get_stack_points() < 17) {
				state = TAKE_NEW_CARD;
			}
			else {
				state = END_OF_GAME_POPUP;
			}
		}
		break;
	case PlayState::SHOW_HIDDEN_CARD:
		dealer->Cards.cards[1]->ShowCard();
		state = SHOW_HIDDEN_CARD_DELAY;
		break;
	case PlayState::TAKE_NEW_CARD:
		if (take_cards(dealer->Cards, delta_time)) {
			state = SHOW_HIDDEN_CARD_DELAY;
		}
		break;
	case PlayState::END_OF_GAME_POPUP:
		if (player->isBusted) {
			if (pop_up_animation(3, delta_time, false)) {
				state = LEAVE;
			}
		}
		else if(player->BlackJacked) {
			if (pop_up_animation(2, delta_time, false)) {
				state = LEAVE;
			}
		}
		else {
			if (dealer->Cards.get_stack_points() > 21) {
				if (pop_up_animation(2, delta_time, false)) {
					state = LEAVE;
				}
			}
			if (dealer->Cards.get_stack_points() > player->PlayerCards.get_stack_points()) {
				if (pop_up_animation(3, delta_time, false)) {
					state = LEAVE;
				}
			}
			else {
				if (pop_up_animation(2, delta_time, false)) {
					state = LEAVE;
				}
			}
		}
		break;
	case PlayState::LEAVE:
		if (stay_anim(4.0f, delta_time)) {
			show_popup = false;
			state = MAIN_MENU_BUTTON;
			
			std::cout << "END OF GAME" << std::endl;
		}
		break;
	case PlayState::MAIN_MENU_BUTTON:
		Button::isAllButtonsBloced = 0;
		break;
	default:
		std::cout << "UNKNOWN STATE" << std::endl;
		break;
	}

	if ((player->stay_flag && bot1->stay_flag && bot2->stay_flag) && !endered_end_of_game_seq) {
		// End of Game
		std::cout << "END OF GAME SEQUANCE" << std::endl;

		state = END_OF_GAME_SEQUANCE;
		endered_end_of_game_seq = true;
	}
}


void PlayState::render(sf::RenderWindow& target)
{
	target.draw(background);

	target.draw(reinterpret_cast<sf::Drawable&>(*pass_button));
	target.draw(reinterpret_cast<sf::Drawable&>(*take_card_button));
	

	target.draw(*cards);
	target.draw(player->PlayerCards);
	target.draw(player->name);

	
	target.draw(bot1->BotsCards);
	target.draw(bot1->name);

	target.draw(bot2->BotsCards);
	target.draw(bot2->name);

	target.draw(dealer->Cards);
	target.draw(dealer->name);

	if (animation_handeler) {
		target.draw(*current_animated_card);
	}

	if (state == MAIN_MENU_BUTTON) {
		target.draw(reinterpret_cast<sf::Drawable&>(*main_menu));
	}

	if (show_selector) {
		target.draw(*selector);
	}
	if (show_popup) {
		target.draw(*popups);
	}

	
}

void PlayState::onResize(int new_w, int new_h)
{
	//Background
	auto size = Vec2(background.getTexture()->getSize());
	float scale = Mapping::FitToX(size);
	background.setScale(scale, scale);

	//Buttons pos
	pass_button->setPosition(Mapping::ToGlobal(button_spacing, 1 - padding_top));
	take_card_button->setPosition(Mapping::ToGlobal(-button_spacing, 1 - padding_top));
	main_menu->setPosition(Mapping::ToGlobal(0, 0));

	//Buttons size
	size = Vec2(pass_button->display.getTexture()->getSize());
	scale = Mapping::FitToX(size) * button_scale;
	pass_button->setScale(scale, scale);
	take_card_button->setScale(scale, scale);
	main_menu->setScale(scale, scale);

	//Card Stack
	//TODO extract function
	cards->setPosition(Mapping::ToGlobal(0.4, -0.4));
	size = Vec2(pass_button->display.getTexture()->getSize());
	float card_stack_size = Mapping::FitToX(size) * button_scale;
	cards->setScale(card_stack_size, card_stack_size);

	//Setup cards pos
	bot1->BotsCards.setPosition(Mapping::ToGlobal(cards_positions[0]));
	bot1->name.setPosition(Mapping::ToGlobal(cards_positions[0]));
	size = Vec2(pass_button->display.getTexture()->getSize());
	card_stack_size = Mapping::FitToX(size) * bot_card_size;
	bot1->BotsCards.setScale(card_stack_size, card_stack_size);

	bot2->BotsCards.setPosition(Mapping::ToGlobal(cards_positions[2]));
	bot2->name.setPosition(Mapping::ToGlobal(cards_positions[2]));
	size = Vec2(pass_button->display.getTexture()->getSize());
	card_stack_size = Mapping::FitToX(size) * bot_card_size;
	bot2->BotsCards.setScale(card_stack_size, card_stack_size);

	player->PlayerCards.setPosition(Mapping::ToGlobal(cards_positions[1]));
	player->name.setPosition(Mapping::ToGlobal(cards_positions[1]));
	size = Vec2(pass_button->display.getTexture()->getSize());
	card_stack_size = Mapping::FitToX(size) * player_card_size;
	player->PlayerCards.setScale(card_stack_size, card_stack_size);

	dealer->Cards.setPosition(Mapping::ToGlobal(dealer_pos));
	dealer->name.setPosition(Mapping::ToGlobal(dealer_pos));
	size = Vec2(pass_button->display.getTexture()->getSize());
	card_stack_size = Mapping::FitToX(size) * dealer_card_size;
	dealer->Cards.setScale(card_stack_size, card_stack_size);


	if (current_animated_card) {
		size = Vec2(pass_button->display.getTexture()->getSize());
		card_stack_size = Mapping::FitToX(size) * animated_card_size;
		dealer->Cards.setScale(card_stack_size, card_stack_size);
	}

	switch (selector_pos) {
	case 0:
		selector->setPosition(bot1->BotsCards.getPosition());
		break;
	case 1:
		selector->setPosition(player->PlayerCards.getPosition());
		break;
	case 2:
		selector->setPosition(bot2->BotsCards.getPosition());
		break;
	}

	size = Vec2(pass_button->display.getTexture()->getSize());
	card_stack_size = Mapping::FitToX(size) * selector_size;
	if (show_selector) {
		selector->setScale(card_stack_size, card_stack_size);
	}

}

void PlayState::onTakeCardButton()
{
	if (isButtonRelased) {
		std::cout << "TAKE CARD" << std::endl;
		if (state == PLAYER_MAKES_DECISION) {
			action = HIT;
		}
	}
}

void PlayState::onPassButton()
{
	if (isButtonRelased) {
		std::cout << "PASS" << std::endl;

		if (state == PLAYER_MAKES_DECISION) {
			action = STAY;
		}
	}
}
void PlayState::onMainMenuButton()
{
	if (isButtonRelased) {
		std::cout << "MAIN_MENU" << std::endl;

		if (state == MAIN_MENU_BUTTON) {
			GameState::isScenSwap = 0;
		}
	}
}

PlayState::GAME_STATE STATE_WATCHER::state = (PlayState::GAME_STATE)0;