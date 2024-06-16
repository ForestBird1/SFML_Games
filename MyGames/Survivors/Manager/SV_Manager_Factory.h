#pragma once
#include "../../Containers/MyArray.h"

class SV_Monster;

class SV_Manager_Factory
{
#pragma region Init
public:
	SV_Manager_Factory();
	~SV_Manager_Factory();

	void PostInit(class SurvivorsMain* main);

private:
	SurvivorsMain* _main = nullptr;
#pragma endregion

#pragma region Monster
public:
	SV_Monster* WakeMonster();
	void SleepMonster(SV_Monster* monster);
private:
	MyArray<SV_Monster*> _pool_monster;
#pragma endregion


};

