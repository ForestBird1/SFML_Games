#pragma once

#include "../UI.h"

class ProgressBar : public UI
{
public:
	ProgressBar();
	ProgressBar(const float f_size_x, const float f_size_y, const sf::Color& color_bg, const sf::Color& color_fill);
	~ProgressBar();

	void SetPosition(const sf::Vector2f& v_pos);

	void SetPercent(const float f_percent);

	void Draw(sf::RenderWindow& window);
private:
	float _size_x_bg = 0.f;
	//float _size_x_fill = 0.f;
	sf::RectangleShape _shape_bg;
	sf::RectangleShape _shape_fill;
};

