#include "BasedGame.h"
#include <iostream>

BasedGame::BasedGame()
{

}
BasedGame::~BasedGame()
{

}

void BasedGame::GameInit()
{
	std::cout << "BasedGame::GameInit()" << std::endl;
	/*virtual*/
}
void BasedGame::Tick()
{
	/*virtual*/
}
void BasedGame::Render(sf::RenderWindow& window)
{
	/*virtual*/
}