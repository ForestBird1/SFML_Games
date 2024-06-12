#pragma once

#include <SFML/Graphics.hpp>

//class Button;
#include "Button/Button.h"

#include "BasedGame.h"
#include "BreakoutGame/BreakoutGameMain.h"
#include "AStarTest/AStarTestMain.h"
#include "Invaders/InvadersMain.h"

enum EGameType {
	Title,
	Breakout_Game,
	AStarTest,
};


class MyGamesMain
{

#pragma region Init
public:
	MyGamesMain();
	~MyGamesMain();

	const sf::Font& GetFont() const;
public:
	void Main();
private:
	sf::Font _font;
#pragma endregion

#pragma region Loop
private:
	void Loop();
	void LoopEvent(sf::Event& event);
	void LoopGame(sf::Event& event);
	void LoopRender();
private:
	/*
	* 생성자에서 초기화되고 렌더됩니다
	*/
	sf::RenderWindow _window;

	bool _can_render = true;
#pragma endregion

#pragma region Game
public:
	void ClosedGameWindow();
private:
	EGameType _selected_game_type = EGameType::Title;

	BasedGame* _selected_game = nullptr;
	BreakoutGameMain _breakoutgame_main;
	AStarTestMain _astartest_main;
	InvadersMain _invaders_main;
#pragma endregion


#pragma region UI
private:
	void OnClickedDoBreakoutGame(const EGameType e_game_type);
private:
	std::vector<Button> _rendering_buttons;

	Button _btn_do_breakout_game;
	Button _btn_do_astar_test;
#pragma endregion


};

