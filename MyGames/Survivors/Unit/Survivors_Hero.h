#pragma once
#include "Survivors_Unit.h"
class Survivors_Hero : public Survivors_Unit
{

#pragma region Debug
public:
	//sf::Texture debug_texture;
#pragma endregion

#pragma region Init
public:
	Survivors_Hero();
	~Survivors_Hero();

	void PostInit(class SurvivorsMain* main);

	void Tick(float DeltaTime, sf::Event& event) override;

	sf::Sprite* GetSprite();
#pragma endregion

#pragma region Render
private:
	sf::Sprite* _sprite = nullptr;
#pragma endregion


#pragma region Move
private:
	void DoMove(sf::Event& event, const float f_delta_time);
private:
	int32_t _move_speed = 500;
#pragma endregion


};

