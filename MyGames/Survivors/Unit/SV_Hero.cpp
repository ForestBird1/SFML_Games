#include "SV_Hero.h"
#include "../SurvivorsMain.h"

#include "../../UI/ProgressBar/ProgressBar.h"

#include <iostream>

SV_Hero::SV_Hero()
{

}

void SV_Hero::PostInit(SurvivorsMain* main)
{
    _sprite = new sf::Sprite();
    _sprite->setTexture(main->GetUnitTexture());
    _sprite->setTextureRect(sf::IntRect(0, 0, 36, 36));
    _sprite->setScale(sf::Vector2f(2.f, 2.f));

    _hp_bar = new ProgressBar(64.f, 4.f, sf::Color::Black, sf::Color::Red);
}
void SV_Hero::Tick(float DeltaTime, sf::Event& event)
{
	__super::Tick(DeltaTime, event);

	DoMove(event,DeltaTime);

    TickUpdateUI();
}

void SV_Hero::DoMove(sf::Event& event, const float f_delta_time)
{
    if (_sprite == nullptr) return;

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

void SV_Hero::TickUpdateUI()
{
    if (_hp_bar == nullptr) return;
    if (_sprite == nullptr) return;


    _hp_bar->SetPosition(sf::Vector2f(_sprite->getPosition().x, _sprite->getPosition().y + _hero_size + 10.f));
    //_hp_bar->SetPosition(_sprite->getPosition());
}

void SV_Hero::LoopRender(sf::RenderWindow& window)
{
    if (_sprite == nullptr) return;
    if (_hp_bar == nullptr) return;

    window.draw(*_sprite);
    _hp_bar->Draw(window);
}

sf::Sprite* SV_Hero::GetSprite() { return _sprite; }

SV_Hero::~SV_Hero()
{
    delete _sprite;
    delete _hp_bar;
}