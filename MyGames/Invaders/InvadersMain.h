#pragma once

#include "../BasedGame.h"

class InvadersMain : public BasedGame
{
#pragma region Init
public:
	InvadersMain();
	~InvadersMain();
	void PostInit();
	void GameInit() override;
	void LoopEvent(sf::Event& event, sf::RenderWindow& window) override;
	void LoopGame(sf::Event& event, sf::RenderWindow& window) override;
	void LoopRender(sf::RenderWindow& window) override;
#pragma endregion
};

