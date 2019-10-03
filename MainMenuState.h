#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "GameState.h"
#include "CredentialsState.h"
#include "State.h"
#include "Button.h"

class MainMenuState : public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	// мапа имени_кнопки = кнопка
	std::map<std::string, Button *> buttons;

	// ширина и высота кнопки (высота также на высоту текста влияет)
	float btn_w = 0, btn_h = 0;

	void initVariables() noexcept(true);
	void initBackground();
	void initFonts();
	void initKeybinds() override;
	void initButtons();
	// инициализация фоновой музыки
	void initMusic() override;
	void initView() noexcept(true) override;

public:
	MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
	virtual ~MainMenuState();

	// середина экрана по X ,учитывая ширину кнопки
	float getMiddleX() const;
	// середина экрана по Y,учитывая высоту кнопки
	float getMiddleY() const;
	// апдейт нажатий клавиатуры
	void updateInput(const float &dt) override;
	// проверка нажатий на кнопки меню
	void updateButtons();
	void updateView() override;
	// общий апдейт
	void update(const float &dt) override;
	// отрисовка кнопок меню
	void renderButtons(sf::RenderTarget *target);
	// общая отрисовка
	void render(sf::RenderTarget *target) override;
};

#endif
