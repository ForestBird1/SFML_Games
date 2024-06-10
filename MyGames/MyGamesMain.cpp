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
    //Init
    _rendering_buttons.reserve(10);

    //Check Font File
    std::string fontPath = "../x64/NotoSansKR.ttf";
    if (!std::filesystem::exists(fontPath)) {
        std::cerr << "Font file does not exist at path: " << fontPath << std::endl;
        return;
    }

    //Load Font File
    if (!_font.loadFromFile(fontPath)) { // 적절한 폰트 파일 경로 사용
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }


    //Init Button
    _btn_do_breakout_game.SetSize(200, 50);
    _btn_do_breakout_game.SetColor_Shape(sf::Color::Blue);
    _btn_do_breakout_game.SetFont(_font);
    _btn_do_breakout_game.SetText("Breakout Game");
    _btn_do_breakout_game.setPosition(300, 275);
    _btn_do_breakout_game.setCallback(std::bind(&MyGamesMain::OnClickedDoBreakoutGame, this, EGameType::Breakout_Game));
    _rendering_buttons.push_back(_btn_do_breakout_game);


    _btn_do_astar_test.SetSize(200, 50);
    _btn_do_astar_test.SetColor_Shape(sf::Color::Blue);
    _btn_do_astar_test.SetFont(_font);
    _btn_do_astar_test.SetText("AStarTest");
    _btn_do_astar_test.setPosition(600, 275);
    _btn_do_astar_test.setCallback(std::bind(&MyGamesMain::OnClickedDoBreakoutGame, this, EGameType::AStarTest));
    _rendering_buttons.push_back(_btn_do_astar_test);
    
    //Init GameClass
    _astartest_main.PostInit(this);
    _breakoutgame_main.PostInit();

    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();

            if (_selected_game_type == EGameType::Title)
            {
                for (Button& button : _rendering_buttons)
                    button.handleEvent(event, _window);
            }

            UpdateGame(event);
        }

        if (_selected_game_type != EGameType::Title &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            _selected_game_type = EGameType::Title;
            for (Button& button : _rendering_buttons)
                button.SetVisible(true);
        }

        

        _window.clear(sf::Color(128, 128, 128));
        Render();
        _window.display();
    }
}

void MyGamesMain::UpdateGame(sf::Event& event)
{
    if (_selected_game_type == EGameType::Title) return;

    _selected_game->Tick(event,_window);
}
void MyGamesMain::Render()
{
    switch (_selected_game_type)
    {
    case Title:
    {
        for(Button& button : _rendering_buttons)
            button.draw(_window);
    }
        break;
    default:
        _selected_game->Render(_window);
        break;
    }
}

void MyGamesMain::OnClickedDoBreakoutGame(const EGameType e_game_type)
{
    //std::cerr << "Clicked" << std::endl;
    _selected_game_type = e_game_type;

    switch (_selected_game_type)
    {
    case Title:
        break;
    case Breakout_Game:
        _selected_game = &_breakoutgame_main;
        break;
    case AStarTest:
        _selected_game = &_astartest_main;
        break;
    default:
        break;
    }

    if (_selected_game_type != EGameType::Title)
    {
        for (Button& button : _rendering_buttons)
            button.SetVisible(false);
    }

    _selected_game->GameInit();
}


const sf::Font& MyGamesMain::GetFont() const { return _font; }

MyGamesMain::~MyGamesMain()
{

}