#pragma once

#include "SFML/Graphics.hpp"

class Invaders_Enemy
{
#pragma region Init
public:
	Invaders_Enemy();
	~Invaders_Enemy();

	void PostInit(const sf::Vector2f& v_size, const sf::Vector2f v_pos);

	sf::RectangleShape* GetShape();
private:
	sf::RectangleShape* _shape = nullptr;
#pragma endregion

};

