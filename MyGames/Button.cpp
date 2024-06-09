#include "Button.h"
#include <SFML/Graphics.hpp>

Button::Button()
{

}
Button::Button(const float width, const float height, const std::string& text, const sf::Font& font)
{
	SetStyle(width, height, text, font);
}

void Button::SetStyle(const float width, const float height, const std::string& text, const sf::Font& font)
{
	// 버튼 모양 설정
	buttonShape.setSize(sf::Vector2f(width, height));
	buttonShape.setFillColor(sf::Color::Blue);

	// 버튼 텍스트 설정
	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(24);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setPosition(
		buttonShape.getPosition().x + (width / 2) - (buttonText.getGlobalBounds().width / 2),
		buttonShape.getPosition().y + (height / 2) - (buttonText.getGlobalBounds().height / 2)
	);
}
void Button::setPosition(float x, float y)
{
	buttonShape.setPosition(x, y);
	buttonText.setPosition(
		x + (buttonShape.getSize().x / 2) - (buttonText.getGlobalBounds().width / 2),
		y + (buttonShape.getSize().y / 2) - (buttonText.getGlobalBounds().height / 2)
	);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(buttonShape);
	window.draw(buttonText);
}

void Button::setCallback(std::function<void()> callback)
{
	this->callback = callback;
}

void Button::handleEvent(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (isClicked(sf::Mouse::getPosition(window))) {
				if (callback) {
					callback();
				}
			}
		}
	}
}

bool Button::isClicked(sf::Vector2i mousePos)
{
	return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
