#include "AStarTile.h"
#include "AStarTestMain.h"
#include "../MyGamesMain.h"
#include <iostream>

AStarTile::AStarTile()
{
	//std::cout << "Construct: Index: " << _index << std::endl;
}

//AStarTile::AStarTile(const AStarTile& other)
//{
//	std::cout << "Construct: Index: " << _index << std::endl;
//	CopyFrom(other);
//}
//
//AStarTile& AStarTile::operator=(const AStarTile& other)
//{
//	if (this != &other)
//	{
//		CopyFrom(other);
//	}
//	return *this;
//}
//
//AStarTile::AStarTile(AStarTile&& other) noexcept
//{
//	std::cout << "Construct: Index: " << _index << std::endl;
//	MoveFrom(std::move(other));
//}
//
//AStarTile& AStarTile::operator=(AStarTile&& other) noexcept
//{
//	if (this != &other)
//	{
//		MoveFrom(std::move(other));
//	}
//	return *this;
//}

//void AStarTile::CopyFrom(const AStarTile& other)
//{
//	_row = other._row;
//	_column = other._column;
//	_button = other._button;
//	_index = other._index;
//}
//
//void AStarTile::MoveFrom(AStarTile&& other)
//{
//	_row = other._row;
//	_column = other._column;
//	_button = std::move(other._button);
//
//	other._row = 0;
//	other._column = 0;
//}

AStarTile::~AStarTile()
{
	//std::cout << "Destruct: Index: " << _index << std::endl;
}


void AStarTile::PostInit(int32_t i_size, int32_t i_index, int32_t i_row, int32_t i_column, AStarTestMain* main, MyGamesMain* game_main)
{
	_astar_main = main;
	_row = i_row;
	_column = i_column;
	_index = i_index;

	_is_wall = false;
	_button.SetColor_Shape(_color_road);

	_button.SetSize((float )i_size, (float)i_size);
	_button.setPosition((float)(i_size * i_row), (float)(i_size * i_column));
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