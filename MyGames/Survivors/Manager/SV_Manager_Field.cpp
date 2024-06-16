#include "SV_Manager_Field.h"
#include "SV_Manager_Factory.h"
#include "../SurvivorsMain.h"

#include "../Unit/SV_Monster.h"

SV_Manager_Field::SV_Manager_Field()
{

}
SV_Manager_Field::~SV_Manager_Field()
{

}

void SV_Manager_Field::PostInit(SurvivorsMain* main)
{
	_main = main;

	_spawned_monsters.Reserve(100);
}

void SV_Manager_Field::Tick(const float DeltaTime, sf::Event& event)
{
	if (_spawned_monsters.Num() >= 1)
	{
		for (SV_Monster* monster : _spawned_monsters)
		{
			monster->Tick(DeltaTime, event);
		}
	}
	

	_monster_spawn_time_current += DeltaTime;
	if (_monster_spawn_time_current >= _monster_spawn_time)
	{
		SpawnMonster();

		_monster_spawn_time_current = 0.f;
	}
}

void SV_Manager_Field::SpawnMonster()
{
	int32_t i_height = 1080;
	int32_t i_width = 1920;

	i_height = rand() % (i_height -100) +100;
	i_width = rand() % (i_width - 100) + 100;

	SV_Monster* monster = _main->GetManagerFactory()->WakeMonster();
	monster->SpawnInit(sf::Vector2f((float)i_width, (float)i_height));
	_spawned_monsters.Add(monster);
}

void SV_Manager_Field::FieldLoopRender(sf::RenderWindow& window)
{
	if (_spawned_monsters.Num() <= 0) return;

	for (SV_Monster* monster : _spawned_monsters)
	{
		monster->LoopRender(window);
	}
}