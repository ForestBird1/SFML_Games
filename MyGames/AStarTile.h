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
	~AStarTile();
	void PostInit(const uint8_t i_size, const uint16_t i_index, const uint8_t i_row, const uint8_t i_column, AStarTestMain* main, MyGamesMain* game_main);
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
	uint8_t _row = 0;
	uint8_t _column = 0;

	AStarTestMain* _astar_main = nullptr;
	bool _is_wall = false;
	sf::Color _color_wall = sf::Color::Red;
	sf::Color _color_road = sf::Color::Blue;
	sf::Color _color_path = sf::Color::Green;
	Button _button;
};

