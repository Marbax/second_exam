#ifndef CredentialsState_H
#define CredentialsState_H

#include "State.h"

class CredentialsState : public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text *credits = nullptr;
	unsigned short credits_size = 0;
	unsigned short char_size = 0;
	float outl_thick = 0;
	sf::Color txt_color;
	sf::Color outl_color;

	void initVariables() noexcept(true);
	void initBackground();
	// инициализация шрифта
	void initFonts();
	void initKeybinds() override;
	// загрузка из файла строк ,перевод их в sf::Text настройка и позиционирование
	void initThx();
	// инициализация фоновой музыки
	void initMusic() override;
	void initView() noexcept(true) override;

public:
	CredentialsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
	virtual ~CredentialsState();

	// делает плывущий текст
	void textFlow();
	// середина экрана по X
	float getMiddleX() const;
	void updateInput(const float &dt) override;
	void updateView() override;
	void update(const float &dt) override;
	// отрисовует текст только в определенном промежутке
	void renderThx(sf::RenderTarget *target);
	void render(sf::RenderTarget *target) override;
};

#endif
