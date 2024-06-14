#include "Survivors_Hero.h"
#include "../SurvivorsMain.h"
#include <iostream>
#include <filesystem>

Survivors_Hero::Survivors_Hero()
{

}

void Survivors_Hero::PostInit(SurvivorsMain* main)
{
    _sprite = new sf::Sprite();
    _sprite->setTexture(main->GetUnitTexture());
    _sprite->setTextureRect(sf::IntRect(0, 0, 36, 36));
    _sprite->setScale(sf::Vector2f(2.f, 2.f));
}
void Survivors_Hero::Tick(float DeltaTime, sf::Event& event)
{
	__super::Tick(DeltaTime, event);

	DoMove(event,DeltaTime);
}

void Survivors_Hero::DoMove(sf::Event& event, const float f_delta_time)
{
    sf::Vector2f v_velocity(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        v_velocity.y = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        v_velocity.y = 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        v_velocity.x = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        v_velocity.x = 1.f;
    }

    if (v_velocity.x != 0.f && v_velocity.y != 0.f)
    {
        //v_velocity /= std::sqrt(2.f); //== 0.707107

        v_velocity.x *= 0.707107f;
        v_velocity.y *= 0.707107f;
    }

    v_velocity.x *= _move_speed * f_delta_time;
    v_velocity.y *= _move_speed * f_delta_time;
    _sprite->move(v_velocity);
}

sf::Sprite* Survivors_Hero::GetSprite() { return _sprite; }

Survivors_Hero::~Survivors_Hero()
{

}