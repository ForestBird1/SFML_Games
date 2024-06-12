#include "InvadersMain.h"
#include "Invaders_Bullet.h"
#include <iostream>

InvadersMain::InvadersMain()
{
	_display_height = 1024;
	_display_width = 768;
	_display_name = "SFML Invaders";
}
InvadersMain::~InvadersMain()
{
	//MyArray<> _bullet_pool은 MyArray<>의 소멸자에서 원소와 배열을 메모리해제합니다
	//MyArray<> _enemies은 MyArray<>의 소멸자에서 원소와 배열을 메모리해제합니다

	//for (int32_t i = _bullet_pool.Num() - 1; i >= 0; --i)
	//{
	//	delete _bullets[i];
	//}

	//for (int32_t i = _enemies.Num() - 1; i >= 0; --i)
	//{
	//	delete _enemies[i];
	//}
}
void InvadersMain::PostInit()
{
	//Create Debug Tile
	float tile_size = 32.f;
	sf::RectangleShape based_tile(sf::Vector2f(tile_size, tile_size));
	based_tile.setFillColor(sf::Color(128, 128, 128));
	based_tile.setOutlineColor(sf::Color::Blue);
	based_tile.setOutlineThickness(2.f);
	for (int32_t i_row = 0, i_row_len = _display_height / tile_size; i_row < i_row_len; ++i_row)
	{
		for (int32_t i_col = 0, i_col_len = _display_width / tile_size; i_col < i_col_len; ++i_col)
		{
			sf::RectangleShape tile = based_tile;
			tile.setPosition(sf::Vector2f(tile_size * i_col, tile_size * i_row));
			_debug_bg_grid.Add(tile);
		}
		
	}
	
	//Create Player
	_player.setSize(sf::Vector2f(_player_size, _player_size));
	_player.setFillColor(sf::Color::Green);
	_player.setPosition((_display_width - _player_size) * 0.5f, _display_height - _player_size - 32);
	_player_muzzle = sf::Vector2f(_player_size * 0.5f, -_bullet_size.y);

	//Init Bullet Pool
	int32_t i_bullet_size = 20;
	Invaders_Bullet* bullet = nullptr;
	_bullet_pool.Reserve(i_bullet_size);
	_bullets.Reserve(i_bullet_size);
	for (int32_t i = 0; i < i_bullet_size; ++i)
	{
		bullet = new Invaders_Bullet();
		bullet->PostInit(_bullet_size, _bullet_color, _bullet_speed);
		_bullet_pool.Add(bullet);
	}

	//Create Enemies
	sf::RectangleShape* enemy = nullptr;
	_enemies.Reserve(_enemy_row * _enemy_col);
	for (int32_t i_row = 0; i_row < _enemy_row; ++i_row)
	{
		for (int32_t i_col = 0; i_col < _enemy_col; ++i_col)
		{
			enemy = new sf::RectangleShape();
			enemy->setSize(_enemy_size);
			enemy->setPosition((_enemy_init_position.x + (64.f - _enemy_size.x) * i_col + _enemy_size.x * i_col),
				(_enemy_init_position.y + (64.f - _enemy_size.y) * i_row + _enemy_size.y * i_row));
			_enemies.Add(enemy);
		}
	}
}
void InvadersMain::GameInit()
{
	_player_as_current = _player_as;
}
void InvadersMain::LoopEvent(sf::Event& event, sf::RenderWindow& window)
{

}
void InvadersMain::LoopGame(sf::Event& event, sf::RenderWindow& window)
{
	//Move Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if(_player.getPosition().x > 0)
			_player.move(-_player_move_speed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if(_player.getPosition().x < _display_width - _player_size)
			_player.move(_player_move_speed, 0);
	}

	//Calc Player AttackSpeed
	_player_as_current += _delta_time;

	//Player Shoot
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (_player_as_current >= _player_as)
		{
			//std::cout << "Shot" << std::endl;
			Invaders_Bullet* bullet = WakeBullet(false, _player.getPosition() + _player_muzzle);
			_player_as_current = 0.f;
		}
	}

	//Move Bullet And Collision, Pooling
	Invaders_Bullet* bullet = nullptr;
	for (int32_t i = _bullets.Num() - 1; i >= 0; --i)
	{
		//Move
		bullet = _bullets[i];
		bullet->BulletMove(_delta_time);

		//Pooling
		if (bullet->GetPosition().y <= 50)
		{
			SleepBullet(bullet);
			_bullets.RemoveAtSwap(i);
			continue;
		}

		//Collision
		if (bullet->IsEnemy() == true)
		{

		}
		else
		{
			sf::RectangleShape* enemy = nullptr;
			for (int32_t j = _enemies.Num() - 1; j >= 0; --j)
			{
				enemy = _enemies[j];
				if (bullet->GetShape()->getGlobalBounds().intersects(enemy->getGlobalBounds()))
				{
					//Success
					delete enemy;
					_enemies.RemoveAtSwap(j);

					_bullets.RemoveAtSwap(i);
					SleepBullet(bullet);
					break;
				}
			}
		}
	}
}
void InvadersMain::LoopRender(sf::RenderWindow& window)
{
	for (const auto& debug_tile : _debug_bg_grid)
	{
		window.draw(debug_tile);
	}

	window.draw(_player);

	for (const sf::RectangleShape* enemy : _enemies)
	{
		window.draw(*enemy);
	}

	for (Invaders_Bullet* bullet : _bullets)
	{
		bullet->Draw(window);
	}
}

Invaders_Bullet* InvadersMain::WakeBullet(const bool b_is_enemy, const sf::Vector2f v_pos)
{
	Invaders_Bullet* bullet = nullptr;
	if (_bullet_pool.Num() <= 0)
	{
		bullet = new Invaders_Bullet();
		bullet->PostInit(_bullet_size, _bullet_color, _bullet_speed);
	}
	else
	{
		bullet = _bullet_pool.Pop();
	}

	bullet->WakeInit(b_is_enemy, v_pos);
	_bullets.Add(bullet);
	return bullet;
}
void InvadersMain::SleepBullet(Invaders_Bullet* bullet)
{
	_bullet_pool.Add(bullet);
}