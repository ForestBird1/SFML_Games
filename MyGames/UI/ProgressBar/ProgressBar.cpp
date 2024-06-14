#include "ProgressBar.h"

ProgressBar::ProgressBar()
{

}
ProgressBar::ProgressBar(const float f_size_x, const float f_size_y, const sf::Color& color_bg, const sf::Color& color_fill)
{
	_shape_bg.setSize(sf::Vector2f(f_size_x, f_size_y));
	_shape_bg.setFillColor(color_bg);

	_shape_fill.setSize(sf::Vector2f(f_size_x, f_size_y));
	_shape_fill.setFillColor(color_fill);

	_size_x_bg = f_size_x;
	//_size_x_fill = f_size_x;

	SetPercent(1.f);
}
void ProgressBar::Draw(sf::RenderWindow& window)
{
	window.draw(_shape_bg);
	window.draw(_shape_fill);
}

void ProgressBar::SetPosition(const sf::Vector2f& v_pos)
{
	_shape_bg.setPosition(v_pos);
	_shape_fill.setPosition(v_pos);
}
void ProgressBar::SetPercent(const float f_percent)
{
	_shape_fill.setSize(sf::Vector2f(_size_x_bg * f_percent, _shape_fill.getSize().y));
}

ProgressBar::~ProgressBar()
{

}