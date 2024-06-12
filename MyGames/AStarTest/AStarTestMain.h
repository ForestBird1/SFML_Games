#pragma once

#include "../BasedGame.h"
#include "AStarTile.h"
#include <SFML/Graphics.hpp>
#include "../Containers/MyArray.h"
#include <vector>

class MyGamesMain;

class AStarTestMain : public BasedGame
{
#pragma region Init,Render
public:
	AStarTestMain();
	~AStarTestMain();
public:
	void PostInit(MyGamesMain* game_main);
	void GameInit() override;
	void LoopEvent(sf::Event& event, sf::RenderWindow& window) override;
	void LoopGame(sf::Event& event, sf::RenderWindow& window) override;
	void LoopRender(sf::RenderWindow& window) override;

	void UpdateAStar();

private:
	//void Draw(const std::vector<uint8_t>& arr_result_row, const std::vector<uint8_t>& arr_result_col);

	//void GetCoordinateToIndex(const int32_t i_index, uint8_t& i_out_row, uint8_t& i_out_column);
#pragma endregion

#pragma region Data
private:
	uint8_t _tile_size = 50;
	uint8_t _row = 30;
	uint8_t _column = 20;

	AStarTile* _nd_start = nullptr;
	AStarTile* _nd_dest = nullptr;

	MyArray<MyArray<AStarTile>> _tiles;
	//std::vector<std::vector<AStarTile>> _tiles;
	MyArray<int32_t> _tile_nearest_x_indexes;
	MyArray<int32_t> _tile_nearest_y_indexes;

	MyArray<AStarTile*> _draw_tiles;
	MyArray<uint8_t> _draw_row;
	MyArray<uint8_t> _draw_col;
#pragma endregion
};

