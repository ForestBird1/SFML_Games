#include "AStarTestMain.h"
#include <iostream>

#include <algorithm>
#include <unordered_set>

AStarTestMain::AStarTestMain()
{

}
AStarTestMain::~AStarTestMain()
{

}

void AStarTestMain::PostInit(MyGamesMain* game_main)
{
	_draw_tiles.Reserve(100);
	_draw_row.Reserve(100);
	_draw_col.Reserve(100);
	_tile_nearest_x_indexes.Reserve(4);
	_tile_nearest_y_indexes.Reserve(4);
	_tile_nearest_x_indexes = { 0,1,-1,0 };
	_tile_nearest_y_indexes = { 1,0,0,-1 };

	int16_t i_index = 0;
	_tiles.Resize(_row, MyArray<AStarTile>(_column, AStarTile()));
	AStarTile* tile = nullptr;
	for (size_t i_row = 0; i_row < _row; ++i_row)
	{
		for (size_t i_col = 0; i_col < _column; ++i_col)
		{
			tile = &_tiles[i_row][i_col];
			tile->PostInit(_tile_size, ++i_index, i_row, i_col, this, game_main);
			if (i_index == 129)
			{
				_nd_start = tile;
			}
			else if (i_index == 469)
			{
				_nd_dest = tile;
			}
		}
	}

	UpdateAStar();
}
void AStarTestMain::GameInit()
{

}
void AStarTestMain::LoopEvent(sf::Event& event, sf::RenderWindow& window)
{
	//Ÿ�� Ŭ���̺�Ʈ ����(��<->��)
	for (size_t i_row = 0; i_row < _row; ++i_row)
	{
		for (size_t i_col = 0; i_col < _column; ++i_col)
		{
			_tiles[i_row][i_col].TileHandlingEvent(event, window);
		}
	}
}
void AStarTestMain::LoopGame(sf::Event& event, sf::RenderWindow& window)
{
	
}
void AStarTestMain::LoopRender(sf::RenderWindow& window)
{
	//��ü Ÿ�� �׸���
	for (size_t i_row = 0; i_row < _row; ++i_row)
	{
		for (size_t i_col = 0; i_col < _column; ++i_col)
		{
			_tiles[i_row][i_col].GetTileButton().Draw(window);
		}
	}

	//Ÿ�� �� ����
	for (AStarTile* tile : _draw_tiles)
	{
		tile->TileUpdatePathColor();
	}

}

void AStarTestMain::UpdateAStar()
{
	for (size_t i_row = 0; i_row < _row; ++i_row)
	{
		for (size_t i_col = 0; i_col < _column; ++i_col)
		{
			_tiles[i_row][i_col].TileInit();
		}
	}

	//<algorithm> �� ȣȯ�� ���� MyArray<>�� �ƴ� std::vector<>�� ����߽��ϴ�
	std::vector<AStarTile*> openList;
	std::unordered_set<AStarTile*> closedList;
	std::vector<AStarTile*> near_list;
	near_list.reserve(_row * _column);
	openList.reserve(_row * _column);
	closedList.reserve(_row * _column);
	openList.push_back(_nd_start);

	_draw_tiles.Clear();

	while (openList.empty() == false)
	{
		// ���¸���Ʈ���� F������ ���� ���� ��带 ã���ϴ�
		std::sort(openList.begin(), openList.end(), [](AStarTile* a, AStarTile* b) {
			return a->f < b->f;
			});
		AStarTile* nd_current = openList.front();
		openList.erase(openList.begin());

		//�������� Ȯ��
		if (nd_current == _nd_dest)
		{
			while (nd_current->_parent != nullptr)
			{
				//_draw_tiles.Add(nd_current);
				_draw_tiles.Insert(0, nd_current);
				nd_current = nd_current->_parent;
			}

			//std::reverse(_draw_tiles.begin(), _draw_tiles.end());
			return;
		}


		//������ ��� ��� ��������
		closedList.insert(nd_current);
		near_list.clear();
		for (size_t i = 0; i < 4; ++i)
		{
			int8_t i_nearest_row = nd_current->_row + _tile_nearest_x_indexes[i];
			int8_t i_nearest_col = nd_current->_column + _tile_nearest_y_indexes[i];

			if (i_nearest_row >= 0 && i_nearest_row < _row &&
				i_nearest_col >= 0 && i_nearest_col < _column)
			{
				AStarTile* tile = &_tiles[i_nearest_row][i_nearest_col];
				if(tile->IsWall() == false)
					near_list.emplace_back(&_tiles[i_nearest_row][i_nearest_col]);
			}
				
		}


		for (AStarTile* neighbor : near_list)
		{
			if (closedList.find(neighbor) != closedList.end())
				continue;

			float tentative_g = nd_current->g + 1;

			auto openNode = std::find(openList.begin(), openList.end(), neighbor);
			if (openNode == openList.end())
			{
				neighbor->g = tentative_g;
				neighbor->h = std::abs(neighbor->_row - _nd_dest->_row) + std::abs(neighbor->_column - _nd_dest->_column);
				neighbor->f = neighbor->g + neighbor->h;
				neighbor->_parent = nd_current;
				openList.push_back(neighbor);
			}
			else if (tentative_g < (*openNode)->g)
			{
				(*openNode)->g = tentative_g;
				(*openNode)->f = (*openNode)->g + (*openNode)->h;
				(*openNode)->_parent = nd_current;
			}

		}
	}
}
