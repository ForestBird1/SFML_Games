#pragma once

#include <SFML/Graphics.hpp>

class Invaders_Bullet
{
#pragma region Init
public:
	Invaders_Bullet();
	~Invaders_Bullet();
	void PostInit(const sf::Vector2f& bullet_size, const sf::Color& bullet_color, const float bullet_speed);
	void WakeInit(const bool b_is_enemy, const sf::Vector2f v_pos);

	void Draw(sf::RenderWindow& window);

	const sf::Vector2f& GetPosition() const;
	const bool IsEnemy() const;
	sf::RectangleShape* GetShape();
private:
	sf::RectangleShape* _shape = nullptr;
	float _bullet_speed = 0.f;
	bool _is_enemy = true;
#pragma endregion

#pragma region Bullet
public:
	void BulletMove(const float f_delta_time);
#pragma endregion

};

