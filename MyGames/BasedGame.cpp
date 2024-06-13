#include "BasedGame.h"
#include "MyGamesMain.h"

BasedGame::BasedGame()
{

}
BasedGame::~BasedGame()
{

}

void BasedGame::GameInit()
{
	/*virtual*/
}
void BasedGame::DoLoop(MyGamesMain* main)
{
    _main = main;
    Loop();
}

void BasedGame::Loop()
{
    sf::RenderWindow window(sf::VideoMode(_display_width, _display_height), _display_name);
    sf::Clock clock;
    _frame_text.setFont(_main->GetFont());
    _frame_text.setPosition(sf::Vector2f(2.f, 2.f));
    _frame_text.setFillColor(sf::Color::Green);
    _frame_text.setCharacterSize(30);
    _frame_text.setOutlineThickness(2.f);

    while (window.isOpen())
    {
        sf::Event event;

        //이벤트처리 루프
        while (window.pollEvent(event))
        {
            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
            //    event.type == sf::Event::Closed)
            //{
            //    window.close();
            //    _main->ClosedGameWindow();
            //}
            if (event.type == sf::Event::Closed)
            {
                window.close();
                _main->ClosedGameWindow();
            }

            LoopEvent(event,window);
        }

        // DeltaTime 계산
        _time = clock.restart();
        _delta_time = _time.asSeconds();
        _frame_text.setString(std::to_string(1.f / _delta_time));

        //게임루프
        LoopGame(event, window);

        //렌더링루프
        window.clear(_display_color);
        LoopRender(window);
        window.draw(_frame_text);
        window.display();
    }
}

void BasedGame::LoopEvent(sf::Event& event, sf::RenderWindow& window)
{
    /*virtual*/
}
void BasedGame::LoopGame(sf::Event& event, sf::RenderWindow& window)
{
	/*virtual*/
}
void BasedGame::LoopRender(sf::RenderWindow& window)
{
	/*virtual*/
}