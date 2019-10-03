#ifndef BUTTON_H
#define BUTTON_H

#include "SFML-2.5.1/include/SFML/Graphics.hpp"

class Button
{
private:
	// состояния кнопки: простой , навели мышь, нажали
	enum button_states
	{
		BTN_IDLE,
		BTN_HOVER,
		BTN_ACTIVE
	} button_states;

	sf::RectangleShape shape;
	sf::Font *font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height,
		   sf::Font *font, std::string text, unsigned character_size,
		   sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		   sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
	~Button();
	// проверка нажата ли кнопка
	const bool isPressed() const;
	// общий апдейт
	void update(const sf::Vector2f mousePos);
	// отрисовка общая (кнопки и текста)
	void render(sf::RenderTarget *target);
};

#endif
