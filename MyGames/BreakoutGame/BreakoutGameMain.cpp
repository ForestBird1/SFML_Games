#include "BreakoutGameMain.h"
#include <SFML/Graphics.hpp>
#include <iostream>

BreakoutGameMain::BreakoutGameMain()
{
    _display_name = "SFML BreaoutGame";
}

void BreakoutGameMain::PostInit()
{
    _paddle.setSize(sf::Vector2f(_paddle_size_x, _paddle_size_y));
    _paddle.setFillColor(_paddle_color);

    _ball.setRadius(_ball_size_radius);
    _ball.setFillColor(_ball_color);

    _bricks.Reserve(_brick_count_max);
}
void BreakoutGameMain::GameInit()
{
    //Paddle
    _paddle.setPosition((1920 - _paddle_size_x) * 0.5f, 1080 - 100);

    //Ball
    _ball.setPosition(_paddle.getPosition().x + _paddle_size_x * 0.5f, _paddle.getPosition().y - 100);
    _ball_velocity = sf::Vector2f(_ball_speed_max, -_ball_speed_max);

    //Bricks
    _bricks.Clear();

    const int8_t i_coloum = 18;
    const int8_t i_row = 10;

    sf::RectangleShape brick(sf::Vector2f(_brick_size_x, _brick_size_y));
    brick.setFillColor(_brick_color);
    brick.setOutlineColor(sf::Color::Black); // 테두리 색상 설정
    brick.setOutlineThickness(5.0f);         // 테두리 두께 설정

    for (int32_t i = 0; i < i_coloum; ++i) {
        for (int32_t j = 0; j < i_row; ++j) {
            sf::RectangleShape b = brick;
            b.setPosition(60 + i * _brick_size_x + i * 6, 100 + _brick_size_y * j + j * 6);
            _bricks.Add(b);
        }
    }
}
void BreakoutGameMain::LoopEvent(sf::Event& event, sf::RenderWindow& window)
{

}
void BreakoutGameMain::LoopGame(sf::Event& event, sf::RenderWindow& window)
{
    //std::cout << _ball_velocity.x << std::endl;
    //Move Paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (_paddle.getPosition().x > 0)
            _paddle.move(-_paddle_speed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (_paddle.getPosition().x < 1920 - _paddle_size_x)
            _paddle.move(_paddle_speed, 0);
    }

    //Move Ball And UpdateVelocity
    _ball.move(_ball_velocity);

    //상하좌우 벽에 부딪히면 반대로 움직입니다
    if (_ball.getPosition().x < 0 || _ball.getPosition().x > 1920)
        _ball_velocity.x = -_ball_velocity.x;
    if (_ball.getPosition().y < 0)
        _ball_velocity.y = -_ball_velocity.y;

    //Paddle과 부딪혔으면 반대로 이동합니다
    if (_ball.getGlobalBounds().intersects(_paddle.getGlobalBounds()))
        _ball_velocity.y = -_ball_velocity.y;

    //Brick과 부딪혔는지 확인합니다
    for (size_t i = 0, i_len = _bricks.Num(); i < i_len; ++i)
    {
        sf::RectangleShape& brick = _bricks[i];

        //공은 한번에 2개이상 부딪힐 일이 없기 때문에 부딪히면 루프를 종료합니다
        if (_ball.getGlobalBounds().intersects(brick.getGlobalBounds())) {
            _ball_velocity.y = -_ball_velocity.y;
            _bricks.RemoveAtSwap(i);
            break;
        }
    }
}
void BreakoutGameMain::LoopRender(sf::RenderWindow& window)
{
    //Draw
    window.draw(_paddle);
    window.draw(_ball);
    for (const auto& b : _bricks) {
        window.draw(b);
    }
}

BreakoutGameMain::~BreakoutGameMain()
{

}