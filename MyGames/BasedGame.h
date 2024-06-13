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
	//GameInit()�ȿ� Loop�� ȣ���ص� ������
	//�ڽİ��ӿ��� __super()�� ������ ȣ���ؾ��ϹǷ� MyGamesMain.cpp���� ��������� ȣ���մϴ�
	void DoLoop(MyGamesMain* main);

	virtual void LoopEvent(sf::Event& event, sf::RenderWindow& window);
	virtual void LoopGame(sf::Event& event, sf::RenderWindow& window);
	virtual void LoopRender(sf::RenderWindow& window);
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

