#include "SV_Monster.h"
#include "../SurvivorsMain.h"

#include "SV_Hero.h"

SV_Monster::SV_Monster()
{

}
SV_Monster::~SV_Monster()
{

}

void SV_Monster::PostInit(class SurvivorsMain* main)
{
	_sprite = new sf::Sprite();
	_sprite->setTexture(main->GetUnitTexture());
	_sprite->setTextureRect(sf::IntRect(64, 0, 32, 32));
	_sprite->setScale(sf::Vector2f(2.f, 2.f));

	_target = main->GetHero();

	_info_unit.move_speed = 300;
}
void SV_Monster::PoolInit(const bool b_is_wake)
{
	__super::PoolInit(b_is_wake);
	if (b_is_wake)
	{

	}
	else
	{

	}
}
void SV_Monster::SpawnInit(const sf::Vector2f& v_pos)
{
	_sprite->setPosition(v_pos);
}

void SV_Monster::Tick(float DeltaTime, sf::Event& event)
{
	__super::Tick(DeltaTime, event);
	
	//Move
	if (_target != nullptr && _info_unit.can_move)
	{
		sf::Vector2f v_velocity = _target->GetPosition() - GetPosition();
		float f_sq_sum = v_velocity.x * v_velocity.x + v_velocity.y * v_velocity.y;
		float f_scale = sqrt(f_sq_sum);

		v_velocity.x /= f_scale;
		v_velocity.y /= f_scale;

		v_velocity.x *= _info_unit.move_speed * DeltaTime;
		v_velocity.y *= _info_unit.move_speed * DeltaTime;

		_sprite->move(v_velocity);
	}
}

void SV_Monster::LoopRender(sf::RenderWindow& window)
{
	__super::LoopRender(window);
	if (_sprite == nullptr) return;

	if(_info_unit.is_wake)
		window.draw(*_sprite);
}