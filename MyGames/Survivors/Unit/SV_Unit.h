#pragma once

#include <SFML/Graphics.hpp>

struct FInfoUnit
{
public:
	bool is_wake = false;
	bool can_move = true;

	int32_t move_speed = 500;
};

class SV_Unit
{
#pragma region Init
public:
	virtual void PoolInit(const bool b_is_wake);
	virtual void Tick(float DeltaTime, sf::Event& event);
	virtual void LoopRender(sf::RenderWindow& window);

	sf::Vector2f GetPosition();
	sf::Sprite* GetSprite();
protected:
	FInfoUnit _info_unit;
	sf::Texture* _texture = nullptr;
	sf::Sprite* _sprite = nullptr;
#pragma endregion

};

