#pragma once

#include <SFML/Graphics.hpp>
//#include "MyGamesMain.h"
class MyGamesMain;

class BasedGame
{
public:
	BasedGame();
	~BasedGame();

	virtual void GameInit();
	virtual void LoopEvent(sf::Event& event, sf::RenderWindow& window);
	virtual void LoopGame(sf::Event& event, sf::RenderWindow& window);
	virtual void LoopRender(sf::RenderWindow& window);

	//GameInit()안에 Loop를 호출해도 되지만
	//자식게임에서 __super()를 일일히 호출해야하므로 MyGamesMain.cpp에서 명시적으로 호출합니다
	void DoLoop(MyGamesMain* main);
private:
	void Loop();
protected:
	MyGamesMain* _main = nullptr;

	unsigned int _display_width = 1920;
	unsigned int _display_height = 1080;
	std::string _display_name = "SFML Game";
	sf::Color _display_color = sf::Color(128, 128, 128);

	float _delta_time = 0.f;
private:
	sf::Time _time;
	sf::Text _frame_text;

};

