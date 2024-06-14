#pragma once
#include "../BasedGame.h"

class SV_Hero;

class SurvivorsMain : public BasedGame
{
#pragma region Init
public:
	SurvivorsMain();
	~SurvivorsMain();

	void PostInit(class MyGamesMain* main);
	void GameInit() override;
	void LoopEvent(sf::Event& event, sf::RenderWindow& window) override;
	void LoopGame(sf::Event& event, sf::RenderWindow& window) override;
	void LoopRender(sf::RenderWindow& window) override;
#pragma endregion

#pragma region Unit
public:
	sf::Texture& GetUnitTexture();
private:
	sf::Texture _unit_texture;
#pragma endregion


#pragma region Player
private:
	SV_Hero* _hero = nullptr;
#pragma endregion

};

