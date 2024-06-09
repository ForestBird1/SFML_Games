#pragma once

#include <SFML/Graphics.hpp>

//class Button;
#include "Button.h"

#include "BasedGame.h"
#include "BreakoutGameMain.h"

enum EGameType {
	Title,
	Breakout_Game,
};


class MyGamesMain
{

#pragma region Init
public:
	MyGamesMain();
	~MyGamesMain();
public:
	void Main();
#pragma endregion

#pragma region Render
private:
	void Render();
private:
	/*
	* 생성자에서 초기화되고 렌더됩니다
	*/
	sf::RenderWindow _window;
#pragma endregion


#pragma region Game
private:
	EGameType _selected_game_type = EGameType::Title;

	BasedGame* _selected_game = nullptr;
	BreakoutGameMain _breakoutgame_main;
#pragma endregion


#pragma region UI
private:
	void OnClickedDoBreakoutGame();
	Button _btn_do_breakout_game;
#pragma endregion


};

