#include "BreakoutGameMain.h"
#include <SFML/Graphics.hpp>

BreakoutGameMain::BreakoutGameMain()
{

}

void BreakoutGameMain::GameInit()
{
    //Paddle
    _paddle.setSize(sf::Vector2f(_paddle_size_x, _paddle_size_y));
    _paddle.setFillColor(_paddle_color);
    _paddle.setPosition((1920 - _paddle_size_x) *0.5f, 1080 - 100);

    //Ball
    _ball.setRadius(_ball_size_radius);
    _ball.setFillColor(_ball_color);
    _ball.setPosition(_paddle.getPosition().x + _paddle_size_x * 0.5f, _paddle.getPosition().y - 100);
    _ball_velocity = sf::Vector2f(_ball_speed, -_ball_speed);

    //Bricks
    const int8_t i_coloum = 18;
    const int8_t i_row = 10;

    _bricks.reserve(_brick_count_max);
    sf::RectangleShape brick(sf::Vector2f(_brick_size_x, _brick_size_y));
    brick.setFillColor(_brick_color);
    brick.setOutlineColor(sf::Color::Black); // �׵θ� ���� ����
    brick.setOutlineThickness(5.0f);         // �׵θ� �β� ����

    for (int32_t i = 0; i < i_coloum; ++i) {
        for (int32_t j = 0; j < i_row; ++j) {
            sf::RectangleShape b = brick;
            //b.setPosition(60 * i + 50, 30 * j + 50);
            b.setPosition(60+ i*_brick_size_x + i* 6, 100+_brick_size_y * j + j * 6);
            _bricks.push_back(b);
        }
    }
}
void BreakoutGameMain::Tick()
{
    //Move Paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && _paddle.getPosition().x > 0)
    {
        _paddle.move(-_paddle_speed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && _paddle.getPosition().x < 1920 - _paddle_size_x)
    {
        _paddle.move(_paddle_speed, 0);
    }

    //Move Ball And UpdateVelocity
    _ball.move(_ball_velocity);

    //�����¿� ���� �ε����� �ݴ�� �����Դϴ�
    if (_ball.getPosition().x < 0 || _ball.getPosition().x > 1920)
        _ball_velocity.x = -_ball_velocity.x;
    if (_ball.getPosition().y < 0)
        _ball_velocity.y = -_ball_velocity.y;

    //Paddle�� �ε������� �ݴ�� �̵��մϴ�
    if (_ball.getGlobalBounds().intersects(_paddle.getGlobalBounds()))
        _ball_velocity.y = -_ball_velocity.y;

    //Brick�� �ε������� Ȯ���մϴ�
    for (auto it = _bricks.begin(); it != _bricks.end();)
    {
        if (_ball.getGlobalBounds().intersects(it->getGlobalBounds())) {
            _ball_velocity.y = -_ball_velocity.y;
            it = _bricks.erase(it);
            break;
        }
        else {
            ++it;
        }
    }
}
void BreakoutGameMain::Render(sf::RenderWindow& window)
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