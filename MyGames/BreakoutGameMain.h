#pragma once

#include <stdlib.h>
#include <vector>

#include "BasedGame.h"

class BreakoutGameMain : public BasedGame
{
#pragma region Init,Render
public:
	BreakoutGameMain();
	~BreakoutGameMain();
public:
	void PostInit();

	//Tick이 먼저 호출되고 렌더링합니다
	void Tick(sf::Event& event, sf::RenderWindow& window) override;
	void Render(sf::RenderWindow& window) override;
#pragma endregion

#pragma region Data
private:
	uint8_t _ball_size_radius = 10;
	sf::Color _ball_color = sf::Color::Red;
	sf::Vector2f _ball_velocity = sf::Vector2f(0.3f, -0.3f);
	float _ball_speed = 0.4f;

	sf::CircleShape _ball;
private:
	uint8_t _paddle_size_x = 140;
	uint8_t _paddle_size_y = 30;
	sf::Color _paddle_color = sf::Color::Green;
	float _paddle_speed = 0.7f;

	sf::RectangleShape _paddle;
private:
	uint8_t _brick_count_max = 200;
	uint8_t _brick_size_x = 94;
	uint8_t _brick_size_y = 30;
	sf::Color _brick_color = sf::Color::Blue;

	std::vector<sf::RectangleShape> _bricks;
#pragma endregion



};

