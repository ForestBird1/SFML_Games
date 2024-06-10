#pragma once

#include <SFML/Graphics.hpp>

class BasedGame
{
public:
	BasedGame();
	~BasedGame();

	virtual void GameInit();
	virtual void Tick(sf::Event& event, sf::RenderWindow& window);
	virtual void Render(sf::RenderWindow& window);
};

