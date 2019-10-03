#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "Player.h"

class GameState : public State
{
private:
	Player *player = nullptr;
	sf::Texture tBkg;
	sf::Sprite sBkg;

	void initVariables() noexcept(true);
	// настройка клавиш
	void initKeybinds() override;
	// загрузка картинок из файла
	void initImages();
	// создание игрока
	void initPlayers();
	// создание фона
	void initLvl();
	// инициализация фоновой музыки
	void initMusic() override;
	// инициализация камеры
	void initView() noexcept(true) override;

public:
	GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
	virtual ~GameState();
	void updateView() override;
	void updateInput(const float &dt) override;
	void update(const float &dt) override;
	void render(sf::RenderTarget *target) override;
};

#endif