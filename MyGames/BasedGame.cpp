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

    while (window.isOpen())
    {
        sf::Event event;

        //이벤트처리 루프
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
                event.type == sf::Event::Closed)
            {
                window.close();
                _main->ClosedGameWindow();
            }

            //if ()
            //{
            //    window.close();
            //    _main->ClosedGameWindow();
            //}

            LoopEvent(event,window);
        }

        //게임루프
        LoopGame(event, window);

        //렌더링루프
        window.clear(sf::Color(128, 128, 128));
        LoopRender(window);
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