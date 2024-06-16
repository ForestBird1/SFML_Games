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

#pragma region Manager
private:
	class SV_Manager_Factory* _mgr_factory = nullptr;
	class SV_Manager_Field* _mgr_field = nullptr;
public:
	SV_Manager_Factory* GetManagerFactory();
#pragma endregion


#pragma region Unit
public:
	sf::Texture& GetUnitTexture();
private:
	sf::Texture _unit_texture;
#pragma endregion

#pragma region Player
public:
	SV_Hero* GetHero();
private:
	SV_Hero* _hero = nullptr;
#pragma endregion

};

