#pragma once
#include "SV_Unit.h"

struct FHeroStat
{
public:
	int32_t hp = 0;
	int32_t hp_max = 0;

	int32_t dmg = 0;
};

class SV_Hero : public SV_Unit
{

#pragma region Debug
public:
	//sf::Texture debug_texture;
#pragma endregion

#pragma region Init
public:
	SV_Hero();
	~SV_Hero();

	void PostInit(class SurvivorsMain* main);

	void Tick(float DeltaTime, sf::Event& event) override;

	
#pragma endregion

#pragma region Stat
private:
	FHeroStat _hero_stat;
#pragma endregion


#pragma region Move
private:
	void DoMove(sf::Event& event, const float f_delta_time);
#pragma endregion

#pragma region UI
private:
	void TickUpdateUI();
private:
	class ProgressBar* _hp_bar;
#pragma endregion

#pragma region Render
public:
	void LoopRender(sf::RenderWindow& window) override;
private:
	int32_t _hero_size = 64;
#pragma endregion

};

