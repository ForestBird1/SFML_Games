#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
    Button();
    Button(const float width, const float height, const std::string& text, const sf::Font& font);
    void SetStyle(const float width, const float height, const std::string& text, const sf::Font& font);

    void setPosition(float x, float y);

    void draw(sf::RenderWindow& window);


    void setCallback(std::function<void()> callback);

    void handleEvent(sf::Event event, sf::RenderWindow& window);

    bool isClicked(sf::Vector2i mousePos);
private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    std::function<void()> callback;
};
