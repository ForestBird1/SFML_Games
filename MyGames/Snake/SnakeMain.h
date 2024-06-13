#pragma once

#include "../BasedGame.h"
#include "../Containers/MyArray.h"
#include <deque>

class MyGamesMain;

struct SnakeTail
{
public:
	int32_t row = 0;
	int32_t col = 0;
};

enum ESnakeDirection
{
	Up,
	Down,
	Right,
	Left,
};

class SnakeMain : public BasedGame
{
#pragma region Init
public:
	SnakeMain();
	~SnakeMain();
	void PostInit(MyGamesMain* game_main);
	void GameInit() override;
	void LoopEvent(sf::Event& event, sf::RenderWindow& window) override;
	void LoopGame(sf::Event& event, sf::RenderWindow& window) override;
	void LoopRender(sf::RenderWindow& window) override;
private:
	sf::Text _text_gameover;
	bool _is_gameover = false;
#pragma endregion

#pragma region Snake
private:
	void SnakeMove(const int32_t i_row, const int32_t i_col);

	void SetPositionEyes(const int32_t i_row, const int32_t i_col);
private:
	//0번이 앞(얼굴)입니다
	std::deque<SnakeTail> _snake;
	sf::CircleShape _eyes;

	ESnakeDirection _snake_direction = ESnakeDirection::Right;

	float _snake_move_timing = 0.3f;
	float _snake_move_timing_current = 0.f;
#pragma endregion


#pragma region Grid
private:
	void SetRandomPositionFood();

	void SetTileColor(const int32_t i_row, const int32_t i_col, const bool b_is_snake);
private:
	int32_t _rows = 0;
	int32_t _columns = 0;
	int32_t _tile_size = 64;
	MyArray<MyArray<sf::RectangleShape>> _grid;

	sf::CircleShape _food;
	int32_t _food_row = 0;
	int32_t _food_col = 0;
#pragma endregion

};

