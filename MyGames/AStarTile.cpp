#include "AStarTile.h"
#include "AStarTestMain.h"
#include "MyGamesMain.h"
#include <iostream>

AStarTile::AStarTile()
{
	
}
AStarTile::~AStarTile()
{

}
void AStarTile::PostInit(const uint8_t i_size, const uint16_t i_index, const uint8_t i_row, const uint8_t i_column, AStarTestMain* main, MyGamesMain* game_main)
{
	_astar_main = main;
	_row = i_row;
	_column = i_column;
	_index = i_index;

	_is_wall = false;
	_button.SetColor_Shape(_color_road);

	_button.SetSize(i_size, i_size);
	_button.setPosition(i_size * i_row, i_size * i_column);
	_button.SetOutline(sf::Color::Black, 2.f);
	_button.SetText(std::to_string(i_index));
	_button.SetTextPosition(_button.GetTextPosition() + sf::Vector2f(-14.f, -12.f));
	_button.SetFont(game_main->GetFont());

	_button.setCallback(std::bind(&AStarTile::ToggleWall, this));
}
void AStarTile::TileHandlingEvent(sf::Event& event, sf::RenderWindow& window)
{
	_button.handleEvent(event, window);
}
void AStarTile::ToggleWall()
{
	_is_wall = !_is_wall;
	if(_is_wall)
		_button.SetColor_Shape(_color_wall);
	else
		_button.SetColor_Shape(_color_road); 

	_astar_main->UpdateAStar();
}
void AStarTile::TileUpdatePathColor()
{
	_button.SetColor_Shape(_color_path);
}
void AStarTile::TileInit()
{
	if (_is_wall)
		_button.SetColor_Shape(_color_wall);
	else
		_button.SetColor_Shape(_color_road);
	h = 0;
	g = 0;
	f = 0;
	_parent = nullptr;
}

Button& AStarTile::GetTileButton() { return _button; }
const bool AStarTile::IsWall() const { return _is_wall; }