#include "SurvivorsMain.h"

#include "Manager/SV_Manager_Factory.h"
#include "Manager/SV_Manager_Field.h"

#include "Unit/SV_Hero.h"

SurvivorsMain::SurvivorsMain()
{
	_display_name = "SFML Survivors";
}
SurvivorsMain::~SurvivorsMain()
{
	delete _mgr_factory;
	delete _mgr_field;

	delete _hero;
}

void SurvivorsMain::PostInit(class MyGamesMain* main)
{
	if (!_unit_texture.loadFromFile("resource/survivors/texture/unit/test.png"))
	{
		system("Pause");
	}

	//Create ManagerClass
	_mgr_factory = new SV_Manager_Factory();
	_mgr_field = new SV_Manager_Field();

	//Init ManagerClass
	_mgr_factory->PostInit(this);
	_mgr_field->PostInit(this);

	_hero = new SV_Hero();
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
	if (_mgr_field == nullptr) return;

	_mgr_field->Tick(_delta_time, event);
	_hero->Tick(_delta_time, event);
}
void SurvivorsMain::LoopRender(sf::RenderWindow& window)
{
	if (_hero == nullptr) return;


	_mgr_field->FieldLoopRender(window);


	_hero->LoopRender(window);
}

sf::Texture& SurvivorsMain::GetUnitTexture() { return _unit_texture; }
SV_Hero* SurvivorsMain::GetHero() { return _hero; }

SV_Manager_Factory* SurvivorsMain::GetManagerFactory() { return _mgr_factory; }
