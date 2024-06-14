#pragma once

#include <SFML/Graphics.hpp>

class SV_Unit
{
#pragma region Init
public:
	virtual void Tick(float DeltaTime, sf::Event& event);
#pragma endregion

};

