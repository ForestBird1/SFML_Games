#include "SV_Manager_Factory.h"
#include "../Unit/SV_Monster.h"

SV_Manager_Factory::SV_Manager_Factory()
{

}
SV_Manager_Factory::~SV_Manager_Factory()
{

}
void SV_Manager_Factory::PostInit(class SurvivorsMain* main)
{
	_main = main;
}

SV_Monster* SV_Manager_Factory::WakeMonster()
{
	SV_Monster* monster = nullptr;
	if (_pool_monster.Num() <= 0)
	{
		monster = new SV_Monster();
		monster->PostInit(_main);
	}
	else
	{
		monster = _pool_monster.Pop();
	}

	monster->PoolInit(true);
	return monster;
}
void SV_Manager_Factory::SleepMonster(SV_Monster* monster)
{
	monster->PoolInit(false);
	_pool_monster.Add(monster);
}