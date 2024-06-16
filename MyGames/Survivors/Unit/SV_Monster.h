#pragma once
#include "SV_Unit.h"

class SV_Monster : public SV_Unit
{
#pragma region Init
public:
	SV_Monster();
	~SV_Monster();

	void PostInit(class SurvivorsMain* main);
	void PoolInit(const bool b_is_wake) override;
	void LoopRender(sf::RenderWindow& window) override;

	void Tick(float DeltaTime, sf::Event& event) override;

	void SpawnInit(const sf::Vector2f& v_pos);
private:
	class SV_Hero* _target = nullptr;
#pragma endregion

};

