#pragma once

#include "../BasedGame.h"
#include "../Containers/MyArray.h"

class Invaders_Bullet;
class Invaders_Enemy;

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
	float _player_move_speed = 500.f;
	sf::Vector2f _player_muzzle = sf::Vector2f(0.f,0.f);
	float _player_as = 1.f;
	float _player_as_current = 0.f;
#pragma endregion

#pragma region Enemy
private:
	MyArray<Invaders_Enemy*> _enemies;
	sf::Vector2f _enemy_size = sf::Vector2f(40.f, 40.f);
	sf::Vector2f _enemy_muzzle = sf::Vector2f(0.f, 0.f);

	int32_t _enemy_row = 5;
	int32_t _enemy_col = 9;
	sf::Vector2f _enemy_init_position = sf::Vector2f(-64.f, 100.f);

	float _enemy_as = 3.f;
	float _enemy_as_current = 0.f;

	//160의 약수여야합니다
	float _enemy_move_speed_x = 60.f;

	float _enemy_move_speed_y = 64.f;

	//160만큼 이동했으면 반대로 이동합니다
	float _enemy_total_move_x_distance = 0.f;

	//_enemy_max_y 만큼 이동했으면 좌우만 움직입니다
	float _enemy_total_move_y_distance = 0.f;

	float _enemy_max_y = 420.f;
#pragma endregion

#pragma region Bullet
public:
	Invaders_Bullet* WakeBullet(const bool b_is_enemy, const sf::Vector2f v_pos);
	void SleepBullet(Invaders_Bullet* bullet);
private:
	MyArray<Invaders_Bullet*> _bullets;

	MyArray<Invaders_Bullet*> _bullet_pool;
	sf::Vector2f _bullet_size = sf::Vector2f(4.f, 32.f);
	sf::Color _bullet_color = sf::Color::Red;

	float _bullet_speed = 1000.f;
#pragma endregion

#pragma region Debug
private:
	MyArray<sf::RectangleShape> _debug_bg_grid;
#pragma endregion

};

