#include "MainMenuState.h"

MainMenuState::MainMenuState(std::shared_ptr<ResourceMenager> resoures, sf::Window* target) :
	GameState(resoures, target)
{

}

void MainMenuState::onStart()
{
	start_button = std::make_shared<MainMenuButton>(
		MainMenuButton(
			"Start",
			Mapping::ToGlobal(0, 0.3),
			MainMenuButton::play,
			resoures
		));
	exit_button = std::make_shared<MainMenuButton>(
		MainMenuButton(
			"Exit",
			Mapping::ToGlobal(0, 0.7),
			MainMenuButton::exit,
			resoures
		));

	start_button->setScale(0.3, 0.3);
	exit_button->setScale(0.3, 0.3);

	background.setTexture(this->resoures->background);

	title.setTexture(this->resoures->title);
	auto size = sf::Vector2f(title.getTexture()->getSize());
	title.setOrigin(size * 0.5f);
}

void MainMenuState::update(float delta_time)
{
	title.setPosition(Mapping::ToGlobal({ 0.0f, cos(3.0f*time)*0.05f-0.6f }));
	start_button->update(*target);
	exit_button->update(*target);
}

void MainMenuState::render(sf::RenderWindow& target)
{
	target.draw(background);
	target.draw(title);
	target.draw(reinterpret_cast<sf::Drawable&>(*start_button));
	target.draw(reinterpret_cast<sf::Drawable&>(*exit_button));
}

void MainMenuState::onResize(int new_w, int new_h)
{
	auto size = sf::Vector2f(background.getTexture()->getSize());
	float scale = Mapping::FitToX(size);
	background.setScale(scale, scale);
	
	start_button->setPosition(Mapping::ToGlobal(0, 0.3));
	exit_button->setPosition(Mapping::ToGlobal(0, 0.7));

	
}
