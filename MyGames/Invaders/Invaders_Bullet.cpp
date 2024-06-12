#include "../Invaders/Invaders_Bullet.h"

Invaders_Bullet::Invaders_Bullet()
{

}
Invaders_Bullet::~Invaders_Bullet()
{
	delete _shape;
}
void Invaders_Bullet::PostInit(const sf::Vector2f& bullet_size, const sf::Color& bullet_color, const float bullet_speed)
{
	_bullet_speed = bullet_speed;

	_shape = new sf::RectangleShape();
	_shape->setSize(bullet_size);
	_shape->setFillColor(bullet_color);
}
void Invaders_Bullet::WakeInit(const bool b_is_enemy, const sf::Vector2f v_pos)
{
	_is_enemy = b_is_enemy;

	_shape->setPosition(v_pos);
}
void Invaders_Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(*_shape);
}

void Invaders_Bullet::BulletMove(const float f_delta_time)
{
	int8_t i_sign = 1;
	if (_is_enemy == false)
	{
		i_sign = -1;
	}

	_shape->move(sf::Vector2f(0.f, i_sign * (f_delta_time * _bullet_speed)));
}

const sf::Vector2f& Invaders_Bullet::GetPosition() const { return _shape->getPosition(); }
const bool Invaders_Bullet::IsEnemy() const { return _is_enemy; }
sf::RectangleShape* Invaders_Bullet::GetShape() { return _shape; }