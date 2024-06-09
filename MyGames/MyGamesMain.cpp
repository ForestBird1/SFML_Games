#include "MyGamesMain.h"
#include <filesystem>
#include <iostream>
#include <functional>

//SFML


//UI
//#include "Button.h"

//Class
//#include "BreakoutGameMain.h"

MyGamesMain::MyGamesMain()
    : _window(sf::VideoMode(1920, 1080), "SFML MyGames")

{

}


void MyGamesMain::Main()
{
    //Create Games

    //Check Font File
    std::string fontPath = "../x64/NotoSansKR.ttf";
    if (!std::filesystem::exists(fontPath)) {
        std::cerr << "Font file does not exist at path: " << fontPath << std::endl;
        return;
    }

    //Load Font File
    sf::Font font;
    if (!font.loadFromFile(fontPath)) { // 적절한 폰트 파일 경로 사용
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }


    _btn_do_breakout_game.SetStyle(200, 50, "Breakout Game", font);
    _btn_do_breakout_game.setPosition(300, 275);
    _btn_do_breakout_game.setCallback(std::bind(&MyGamesMain::OnClickedDoBreakoutGame, this));

    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();

            _btn_do_breakout_game.handleEvent(event, _window);
        }

        if (_selected_game_type != EGameType::Title &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            _selected_game_type = EGameType::Title;
        }

        _window.clear(sf::Color(128, 128, 128));
        Render();
        _window.display();
    }
}
void MyGamesMain::Render()
{
    switch (_selected_game_type)
    {
    case Title:
    {
        _btn_do_breakout_game.draw(_window);
    }
        break;
    default:
        _selected_game->Tick();
        _selected_game->Render(_window);
        break;
    }
}

void MyGamesMain::OnClickedDoBreakoutGame()
{
    //std::cerr << "Clicked" << std::endl;
    _selected_game_type = EGameType::Breakout_Game;

    switch (_selected_game_type)
    {
    case Title:
    break;
    case Breakout_Game:
    {
        _selected_game = &_breakoutgame_main;
    }
    break;
    default:
        break;
    }

    _selected_game->GameInit();
}


MyGamesMain::~MyGamesMain()
{

}