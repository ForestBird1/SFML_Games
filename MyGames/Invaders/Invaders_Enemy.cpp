#include "Invaders_Enemy.h"

Invaders_Enemy::Invaders_Enemy()
{

}
Invaders_Enemy::~Invaders_Enemy()
{
	delete _shape;
}

void Invaders_Enemy::PostInit(const sf::Vector2f& v_size, const sf::Vector2f v_pos)
{
	_shape = new sf::RectangleShape();
	_shape->setSize(v_size);
	_shape->setPosition(v_pos);
}

void Invaders_Enemy::Move(const sf::Vector2f& v_velocity)
{
	_shape->move(v_velocity);
}

sf::RectangleShape* Invaders_Enemy::GetShape() { return _shape; }