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
	// ��ư ��� ����
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
	buttonShape.setOutlineColor(color); // �ܰ��� ���� ����
	buttonShape.setOutlineThickness(f_thickness); // �ܰ��� �β� ����
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
					if (!_is_pressed) // ��ư�� �̹� ���� �ִ��� Ȯ��
					{
						_is_pressed = true; // ��ư�� ���� ���·� ����
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
				_is_pressed = false; // ��ư�� ������ ���� ���·� ����
			}
		}
	}
}

bool Button::isClicked(sf::Vector2i mousePos)
{
	return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::SetVisible(const bool b_is_visible) { _is_visible = b_is_visible; }