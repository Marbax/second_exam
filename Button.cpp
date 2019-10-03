#include "Button.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Button::Button(float x, float y, float width, float height,
			   sf::Font *font, std::string text, unsigned character_size,
			   sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			   sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	// начальное состояние кнопки
	this->button_states = BTN_IDLE;

	//  начальная позиция , размер и фон кнопки
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setFillColor(idle_color);
	//this->shape.setSize(sf::Vector2f(width,height));

	// загрузка и установка шрифта на текст
	this->font = font;
	this->text.setFont(*this->font);

	// установка текста ,цвета и размера текста в кнопку
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);

	// установка размера кнопки ,относительно размера текста
	this->shape.setSize(sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height));

	// установка текста в центр кнопки
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height + 5); // +5 чтоб текст ровнее ложился в shape

	// установка цветов текста в разных состояниях
	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	// установка цветов фона в разных состояниях
	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	// цвет внешней линии и ее толщина ,для shape так же работает 
	//this->text.setOutlineColor(sf::Color::Green);
	//this->text.setOutlineThickness(0.2);
}

Button::~Button()
{
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

// проверка нажата ли кнопка
const bool Button::isPressed() const
{
	if (this->button_states == BTN_ACTIVE)
		return true;

	return false;
}

// общий апдейт
void Button::update(const sf::Vector2f mousePos)
{
	//Idle
	this->button_states = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->button_states = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->button_states = BTN_ACTIVE;
		}
	}

	switch (this->button_states)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	}
}

// отрисовка общая (кнопки и текста)
void Button::render(sf::RenderTarget *target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
