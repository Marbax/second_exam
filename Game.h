#ifndef GAME_H
#define GAME_H
#include <time.h>
#include <iostream>
#include <fstream>
#include <stack>
#include "MainMenuState.h"

class Game
{
private:
    sf::RenderWindow *window = nullptr;
    sf::Event sfEvent;

    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen = false;

    sf::Clock dtClock;
    // delta time ,для рендера
    float dt = 0.f;
    // состояния игры , обновляет верхний
    std::stack<State *> states;
    //настройка кнопок через название=цифр. знач.
    std::map<std::string, int> supportedKeys;

    //------------------Inits

    // настройки SFML окна
    void initWindow();
    // загрузка клавиш из файла конфигурации
    void initKeys();
    // пуш состояния (меню)
    void initStates();

public:
    //------------------Constructors/Destructors

    Game();
    virtual ~Game();

    //------------------Methods

    // закрытие стейта (просто вывод)
    void endApplication();
    // апдейт времени (миллисекунды)
    void updateDt();
    // закртие окна SFML
    void updateSFMLEvents();
    // обновление всего в верхнем стейте
    void update();
    // отрисовка всего в верхнем стейте
    void render();
    // запуск
    void run();
};

#endif