#pragma once

#include <SFML/Graphics.hpp>

class BasedGame
{
public:
	BasedGame();
	~BasedGame();
	virtual void GameInit();
	virtual void Tick();
	virtual void Render(sf::RenderWindow& window);
};

