#include "Button.h"
#include <SFML/Graphics.hpp>


Button::Button()
{
	_is_visible = true;
}
Button::Button(const float width, const float height, const sf::Color& color, const std::string& text, const sf::Font& font)
{
	_is_visible = true;
	SetSize(width, height);
	SetColor_Shape(color);
	SetText(text);
	SetFont(font);
}

void Button::SetSize(const float width, const float height)
{
	// 버튼 모양 설정
	buttonShape.setSize(sf::Vector2f(width, height));

	buttonText.setCharacterSize(24);
	
	buttonText.setPosition(
		buttonShape.getPosition().x + (width / 2) - (buttonText.getGlobalBounds().width / 2),
		buttonShape.getPosition().y + (height / 2) - (buttonText.getGlobalBounds().height / 2)
	);
}
void Button::SetText(const std::string& text)
{
	buttonText.setString(text);
}
void Button::SetTextPosition(const sf::Vector2f& v2_pos)
{
	buttonText.setPosition(v2_pos);
}
void Button::SetFont(const sf::Font& font)
{
	buttonText.setFont(font);
}
void Button::SetColor_Shape(const sf::Color& color)
{
	buttonShape.setFillColor(color);
}
void Button::SetOutline(const sf::Color& color, const float f_thickness)
{
	buttonShape.setOutlineColor(color); // 외곽선 색상 설정
	buttonShape.setOutlineThickness(f_thickness); // 외곽선 두께 설정
}

void Button::setPosition(float x, float y)
{
	buttonShape.setPosition(x, y);
	buttonText.setPosition(
		x + (buttonShape.getSize().x / 2) - (buttonText.getGlobalBounds().width / 2),
		y + (buttonShape.getSize().y / 2) - (buttonText.getGlobalBounds().height / 2)
	);
}

const sf::Vector2f Button::GetTextPosition() const { return buttonText.getPosition(); }
const sf::Color Button::GetColor() const { return buttonShape.getFillColor(); }

void Button::Draw(sf::RenderWindow& window)
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
	if (_is_visible)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
				{
					if (!_is_pressed) // 버튼이 이미 눌려 있는지 확인
					{
						_is_pressed = true; // 버튼이 눌린 상태로 설정
						if (callback)
						{
							callback();
						}
					}
				}
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				_is_pressed = false; // 버튼이 눌리지 않은 상태로 설정
			}
		}
	}
}

bool Button::isClicked(sf::Vector2i mousePos)
{
	return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::SetVisible(const bool b_is_visible) { _is_visible = b_is_visible; }