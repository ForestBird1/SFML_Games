#include "InvadersMain.h"
#include <iostream>

InvadersMain::InvadersMain()
{
	_display_height = 1024;
	_display_width = 768;
	_display_name = "SFML Invaders";
}
InvadersMain::~InvadersMain()
{
	for (int32_t i = _bullets.Num() - 1; i >= 0; --i)
	{
		delete _bullets[i];
	}

	for (int32_t i = _enemies.Num() - 1; i >= 0; --i)
	{
		delete _enemies[i];
	}
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
	sf::RectangleShape* bullet = nullptr;
	_bullet_pool.Reserve(i_bullet_size);
	_bullets.Reserve(i_bullet_size);
	for (int32_t i = 0; i < i_bullet_size; ++i)
	{
		bullet = new sf::RectangleShape();
		bullet->setSize(_bullet_size);
		bullet->setFillColor(_bullet_color);
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
		if(_player.getPosition().x < 1920 - _player_size)
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
			sf::RectangleShape* bullet = WakeBullet();
			bullet->setPosition(_player.getPosition() + _player_muzzle);
			_player_as_current = 0.f;
		}
	}

	//Move Bullet And Collision, Pooling
	sf::RectangleShape* bullet = nullptr;
	for (int32_t i = _bullets.Num() - 1; i >= 0; --i)
	{
		//Move
		bullet = _bullets[i];
		bullet->move(sf::Vector2f(0.f, -(_delta_time * _bullet_speed)));

		//Pooling
		if (bullet->getPosition().y <= 50)
		{
			SleepBullet(bullet);
			_bullets.RemoveAtSwap(i);
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

	for (const sf::RectangleShape* bullet : _bullets)
	{
		window.draw(*bullet);
	}
}

sf::RectangleShape* InvadersMain::WakeBullet()
{
	sf::RectangleShape* bullet = nullptr;
	if (_bullet_pool.Num() <= 0)
	{
		bullet = new sf::RectangleShape();
		bullet->setSize(_bullet_size);
		bullet->setFillColor(_bullet_color);
		return bullet;
	}
	else
	{
		bullet = _bullet_pool.Pop();
	}
	_bullets.Add(bullet);
	return bullet;
}
void InvadersMain::SleepBullet(sf::RectangleShape* bullet)
{
	_bullet_pool.Add(bullet);
}