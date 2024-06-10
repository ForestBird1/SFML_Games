#pragma once

#include "BasedGame.h"
#include "AStarTile.h"
#include <SFML/Graphics.hpp>

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
	void Tick(sf::Event& event, sf::RenderWindow& window) override;
	void Render(sf::RenderWindow& window) override;

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

	std::vector< std::vector<AStarTile>> _tiles;
	std::vector<int32_t> _tile_nearest_x_indexes;
	std::vector<int32_t> _tile_nearest_y_indexes;

	std::vector<AStarTile*> _draw_tiles;
	std::vector<uint8_t> _draw_row;
	std::vector<uint8_t> _draw_col;
#pragma endregion
};

