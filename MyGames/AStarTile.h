#pragma once

#include <stdint.h>
#include "Button.h"

class MyGamesMain;
class AStarTestMain;

class AStarTile
{
public:
	friend class AStarTestMain;

	AStarTile();
	//AStarTile(const AStarTile& other); // 복사 생성자
	//AStarTile& operator=(const AStarTile& other); // 복사 할당 연산자
	//AStarTile(AStarTile&& other) noexcept; // 이동 생성자
	//AStarTile& operator=(AStarTile&& other) noexcept; // 이동 할당 연산자
	~AStarTile();
private:
	//void CopyFrom(const AStarTile& other);
	//void MoveFrom(AStarTile&& other);
public:

	void PostInit(int32_t i_size, int32_t i_index, int32_t i_row, int32_t i_column, AStarTestMain* main, MyGamesMain* game_main);
	void TileInit();
	void TileHandlingEvent(sf::Event& event, sf::RenderWindow& window);
	void TileUpdatePathColor();

	const bool IsWall() const;
	Button& GetTileButton();
private:
	void ToggleWall();
private:
	float h = 0;
	float g = 0;
	float f = 0;
	AStarTile* _parent = nullptr;
	int32_t _index = 0;
	int32_t _row = 0;
	int32_t _column = 0;

	AStarTestMain* _astar_main = nullptr;
	bool _is_wall = false;
	sf::Color _color_wall = sf::Color::Red;
	sf::Color _color_road = sf::Color::Blue;
	sf::Color _color_path = sf::Color::Green;
	Button _button;
};

