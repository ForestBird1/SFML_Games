#include "SnakeMain.h"
#include "../MyGamesMain.h"

SnakeMain::SnakeMain()
{
	_display_height = 1024;
	_display_width = 768;
	_display_name = "SFML Snake";
	_display_color = sf::Color::Black;
}
SnakeMain::~SnakeMain()
{

}
void SnakeMain::PostInit(MyGamesMain* game_main)
{
	//Init GameOver Font
	_text_gameover.setFont(game_main->GetFont());
	_text_gameover.setString("GameOver");
	_text_gameover.setFillColor(sf::Color::White);
	_text_gameover.setOutlineColor(sf::Color::Black);
	_text_gameover.setOutlineThickness(2.f);
	_text_gameover.setCharacterSize(50);
	_text_gameover.setPosition(sf::Vector2f(_display_width * 0.5f, _display_height * 0.5f));


	//Create Grid
	_rows = _display_height / _tile_size;
	_columns = _display_width / _tile_size;
	_grid.Resize(_rows, MyArray<sf::RectangleShape>(_columns, sf::RectangleShape()));
	sf::RectangleShape* tile = nullptr;
	for (size_t i_row = 0; i_row < _rows; ++i_row)
	{
		for (size_t i_col = 0; i_col < _columns; ++i_col)
		{
			tile = &_grid[i_row][i_col];
			tile->setSize(sf::Vector2f(_tile_size, _tile_size));
			tile->setFillColor(sf::Color::Black);
			tile->setOutlineColor(sf::Color::Blue);
			tile->setOutlineThickness(2.f);
			tile->setPosition(sf::Vector2f(_tile_size * i_col, _tile_size * i_row));
		}
	}

	//Init Snake
	//_snake.resize();
	for (int32_t i = 0; i < 3; ++i)
	{
		SnakeTail tail;
		tail.col = i;
		_snake.push_front(tail);
		SetTileColor(0, i, true);
	}

	//Init Eye
	_eyes.setRadius(8.f);
	_eyes.setFillColor(sf::Color::Red);
	const SnakeTail& tail = _snake.front();
	SetPositionEyes(tail.row, tail.col);

	//Init Food
	_food.setRadius(8.f);
	_food.setFillColor(sf::Color::Green);
	SetRandomPositionFood();
}
void SnakeMain::GameInit()
{
	_is_gameover = false;
	_snake_move_timing_current = 0.f;
	_snake_direction = ESnakeDirection::Right;

	while (_snake.empty() == false)
	{
		const SnakeTail& tail_last = _snake.back();
		SetTileColor(tail_last.row, tail_last.col, false);
		_snake.pop_back();
	}

	_snake.clear();
	for (int32_t i = 0; i < 3; ++i)
	{
		SnakeTail tail;
		tail.col = i;
		_snake.push_front(tail);
		SetTileColor(0, i, true);
	}


	const SnakeTail& tail = _snake.front();
	SetPositionEyes(tail.row, tail.col);

	SetRandomPositionFood();
}
void SnakeMain::LoopEvent(sf::Event& event, sf::RenderWindow& window)
{
	if (_is_gameover == true) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_snake_direction_buffer = ESnakeDirection::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_snake_direction_buffer = ESnakeDirection::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_snake_direction_buffer = ESnakeDirection::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_snake_direction_buffer = ESnakeDirection::Left;
	}
}

//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//	{
//		if(_snake_direction != ESnakeDirection::Down)
//			_snake_direction = ESnakeDirection::Up;
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//	{
//		if (_snake_direction != ESnakeDirection::Up)
//			_snake_direction = ESnakeDirection::Down;
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//	{
//		if (_snake_direction != ESnakeDirection::Left)
//			_snake_direction = ESnakeDirection::Right;
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//	{
//		if (_snake_direction != ESnakeDirection::Right)
//			_snake_direction = ESnakeDirection::Left;
//	}
//}
void SnakeMain::LoopGame(sf::Event& event, sf::RenderWindow& window)
{
	_snake_move_timing_current += _delta_time;

	if (_snake_move_timing_current >= _snake_move_timing)
	{
		//_snake_direction_buffer로 이동방향 결정하기
		if (_snake_direction_buffer != _snake_direction)
		{
			switch (_snake_direction_buffer)
			{
			case Up:
				if (_snake_direction != ESnakeDirection::Down)
					_snake_direction = ESnakeDirection::Up;
				break;
			case Down:
				if (_snake_direction != ESnakeDirection::Up)
					_snake_direction = ESnakeDirection::Down;
				break;
			case Right:
				if (_snake_direction != ESnakeDirection::Left)
					_snake_direction = ESnakeDirection::Right;
				break;
			case Left:
				if (_snake_direction != ESnakeDirection::Right)
					_snake_direction = ESnakeDirection::Left;
				break;
			default:
				break;
			}

		}

		int32_t i_d_row = 0;
		int32_t i_d_col = 0;
		switch (_snake_direction)
		{
		case Up:
			i_d_row = -1;
			break;
		case Down:
			i_d_row = 1;
			break;
		case Right:
			i_d_col = 1;
			break;
		case Left:
			i_d_col = -1;
			break;
		default:
			break;
		}

		const SnakeTail& tail = _snake.front();
		SnakeMove(tail.row + i_d_row, tail.col + i_d_col);
		_snake_move_timing_current = 0.f;
	}
	
}
void SnakeMain::LoopRender(sf::RenderWindow& window)
{
	for (auto& arr : _grid)
	{
		for (const auto& tile : arr)
		{
			window.draw(tile);
		}
	}

	window.draw(_eyes);
	window.draw(_food);

	if(_is_gameover == true)
		window.draw(_text_gameover);
}

void SnakeMain::SnakeMove(const int32_t i_row, const int32_t i_col)
{
	

	//벽에 부딪힌지 체크
	if (i_row < 0 || i_row >_rows)
	{
		_is_gameover = true;
		return;
	}

	if (i_col < 0 || i_col >_columns)
	{
		_is_gameover = true;
		return;
	}

	//꼬리가 있는 곳으로 갔는지 확인합니다
	for (const SnakeTail& tail : _snake)
	{
		if (tail.col == i_col && tail.row == i_row)
		{
			_is_gameover = true;
			return;
		}
	}

	//이동, 먹이를 먹었는지 확인
	if (i_row == _food_row &&
		i_col == _food_col)
	{
		//Eat Food
		//꼬리를 그대로 두고 머리를 만듭니다
		SnakeTail tail_face;
		tail_face.row = i_row;
		tail_face.col = i_col;
		_snake.push_front(tail_face);
		SetTileColor(tail_face.row, tail_face.col, true);
		SetRandomPositionFood();
	}
	else
	{
		//꼬리를 머리로 이동합니다
		_snake.push_front(_snake.back());
		_snake.pop_back();
		SnakeTail& tail_face = _snake.front();
		SetTileColor(tail_face.row, tail_face.col, false);
		tail_face.row = i_row;
		tail_face.col = i_col;
		SetTileColor(tail_face.row, tail_face.col, true);
	}	

	const SnakeTail& tail_face = _snake.front();
	SetPositionEyes(tail_face.row, tail_face.col);

	
}
void SnakeMain::SetPositionEyes(const int32_t i_row, const int32_t i_col)
{
	sf::Vector2f v_pos = _grid[i_row][i_col].getPosition();
	v_pos = sf::Vector2f(v_pos.x + (_tile_size * 0.5f), v_pos.y + (_tile_size * 0.5f));
	v_pos = sf::Vector2f(v_pos.x - _eyes.getRadius(), v_pos.y - _eyes.getRadius());
	_eyes.setPosition(v_pos);
}
void SnakeMain::SetRandomPositionFood()
{
	_food_row = rand() % _grid.Num();
	_food_col = rand() % _grid[_food_row].Num();

	_food.setPosition(_grid[_food_row][_food_col].getPosition());
}
void SnakeMain::SetTileColor(const int32_t i_row, const int32_t i_col, const bool b_is_snake)
{
	if (b_is_snake)
	{
		_grid[i_row][i_col].setFillColor(sf::Color::Green);
	}
	else
	{
		_grid[i_row][i_col].setFillColor(sf::Color::Black);
	}
}