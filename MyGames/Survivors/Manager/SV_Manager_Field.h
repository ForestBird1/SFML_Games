#pragma once
#include "../../Containers/MyArray.h"
#include <SFML/Graphics.hpp>

class SV_Monster;

class SV_Manager_Field
{
#pragma region Init
public:
	SV_Manager_Field();
	~SV_Manager_Field();

	void PostInit(class SurvivorsMain* main);
	void Tick(const float DeltaTime, sf::Event& event);

	void FieldLoopRender(sf::RenderWindow& window);

private:
	SurvivorsMain* _main = nullptr;
#pragma endregion

#pragma region Monster
private:
	void SpawnMonster();
private:
	MyArray<SV_Monster*> _spawned_monsters;

	float _monster_spawn_time_current = 0.f;
	float _monster_spawn_time = 1.f;
#pragma endregion


};

