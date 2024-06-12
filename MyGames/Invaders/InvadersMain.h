#pragma once

#include "../BasedGame.h"
#include "../Containers/MyArray.h"

class InvadersMain : public BasedGame
{
#pragma region Init
public:
	InvadersMain();
	~InvadersMain();
	void PostInit();
	void GameInit() override;
	void LoopEvent(sf::Event& event, sf::RenderWindow& window) override;
	void LoopGame(sf::Event& event, sf::RenderWindow& window) override;
	void LoopRender(sf::RenderWindow& window) override;
#pragma endregion


#pragma region Player
private:
	sf::RectangleShape _player;
	float _player_size = 64.f;
	float _player_move_speed = 2.f;
	sf::Vector2f _player_muzzle = sf::Vector2f(0.f,0.f);
	float _player_as = 1.f;
	float _player_as_current = 0.f;
#pragma endregion

#pragma region Enemy
private:
	MyArray<sf::RectangleShape*> _enemies;
	sf::Vector2f _enemy_size = sf::Vector2f(50.f, 50.f);

	int32_t _enemy_row = 5;
	int32_t _enemy_col = 11;
	sf::Vector2f _enemy_init_position = sf::Vector2f(32.f, 100.f);
#pragma endregion

#pragma region Bullet
public:
	sf::RectangleShape* WakeBullet();
	void SleepBullet(sf::RectangleShape* bullet);
private:
	MyArray<sf::RectangleShape*> _bullets;
	MyArray<sf::RectangleShape*> _bullet_pool;
	sf::Vector2f _bullet_size = sf::Vector2f(4.f, 32.f);
	sf::Color _bullet_color = sf::Color::Red;

	float _bullet_speed = 700.f;
#pragma endregion







#pragma region Debug
private:
	MyArray<sf::RectangleShape> _debug_bg_grid;
#pragma endregion

};

