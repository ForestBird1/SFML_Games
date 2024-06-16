#include "SV_Unit.h"
//#include <iostream>

void SV_Unit::PoolInit(const bool b_is_wake)
{
	/*virtual*/

	if (b_is_wake)
	{

	}
	else
	{

	}

	_info_unit.is_wake = b_is_wake;
}
void SV_Unit::Tick(float DeltaTime, sf::Event& event)
{
	/*virtual*/
	//std::cout << "Unit" << std::endl;
}

void SV_Unit::LoopRender(sf::RenderWindow& window)
{
	/*virtual*/
}

sf::Sprite* SV_Unit::GetSprite() { return _sprite; }
sf::Vector2f SV_Unit::GetPosition()
{
	if (_sprite == nullptr) return sf::Vector2f();
	return _sprite->getPosition();
}