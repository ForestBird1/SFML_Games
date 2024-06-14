#include "SurvivorsMain.h"
#include "Unit/Survivors_Hero.h"

SurvivorsMain::SurvivorsMain()
{
	_display_name = "SFML Survivors";
}
SurvivorsMain::~SurvivorsMain()
{
	
}

void SurvivorsMain::PostInit(class MyGamesMain* main)
{
	if (!_unit_texture.loadFromFile("resource/survivors/texture/unit/test.png"))
	{
		system("Pause");
	}

	_hero = new Survivors_Hero();
	_hero->PostInit(this);
}
void SurvivorsMain::GameInit()
{

}
void SurvivorsMain::LoopEvent(sf::Event& event, sf::RenderWindow& window)
{

}
void SurvivorsMain::LoopGame(sf::Event& event, sf::RenderWindow& window)
{
	if (_hero == nullptr) return;

	_hero->Tick(_delta_time, event);
}
void SurvivorsMain::LoopRender(sf::RenderWindow& window)
{
	if (_hero == nullptr) return;

	_hero->LoopRender(window);
}

sf::Texture& SurvivorsMain::GetUnitTexture() { return _unit_texture; }