#pragma once

#include <SFML/Graphics.hpp>

class Survivors_Unit
{
#pragma region Init
public:
	virtual void Tick(float DeltaTime, sf::Event& event);
#pragma endregion

};

