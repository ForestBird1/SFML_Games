#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
    Button();
    Button(const float width, const float height, const sf::Color& color, const std::string& text, const sf::Font& font);
    void SetSize(const float width, const float height);
    void SetText(const std::string& text);
    void SetTextPosition(const sf::Vector2f& v2_pos);
    void SetFont(const sf::Font& font);
    void SetColor_Shape(const sf::Color& color);
    void SetOutline(const sf::Color& color, const float f_thickness);
    void SetVisible(const bool b_is_visible);

    void setPosition(float x, float y);

    void draw(sf::RenderWindow& window);


    void setCallback(std::function<void()> callback);

    void handleEvent(sf::Event event, sf::RenderWindow& window);

    bool isClicked(sf::Vector2i mousePos);

    const sf::Vector2f GetTextPosition() const;
    const sf::Color GetColor() const;
private:
    bool _is_visible = true;
    bool _is_pressed = false;
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    std::function<void()> callback;
};
