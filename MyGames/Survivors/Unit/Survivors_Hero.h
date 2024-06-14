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
public:
	void LoopRender(sf::RenderWindow& window);
private:
	sf::Sprite* _sprite = nullptr;

	int32_t _hero_size = 64;
#pragma endregion

#pragma region Move
private:
	void DoMove(sf::Event& event, const float f_delta_time);
private:
	int32_t _move_speed = 500;
#pragma endregion

#pragma region UI
private:
	void TickUpdateUI();
private:
	class ProgressBar* _hp_bar;
#pragma endregion


};

