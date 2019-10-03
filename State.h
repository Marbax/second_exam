#ifndef STATE_H
#define STATE_H
#include <stack>
#include <unordered_map>
#include <fstream>
#include "Entity.h"
#include "SFML-2.5.1/include/SFML/Audio.hpp"

// абстрактный класс состояния игры
class State
{
private:
protected:
    // стак состояний игры
    std::stack<State *> *states;
    // ссылка на окно
    sf::RenderWindow *window;
    // мапа клавиш управления с их понятными названиями
    std::map<std::string, int> *supportedKeys;
    // кнопки по назначениям ,импользуемые в игре ,в разных стейтах ,переписываются с тех что выше
    std::map<std::string, int> keybinds;
    bool quit;

    // камера
    sf::View view;

    // фоновая музыка
    sf::Music music;
    unsigned short music_volume = 5;

    // позиция курсора на экране
    sf::Vector2i mousePosScreen;
    // позиция курсора в окне приложения
    sf::Vector2i mousePosWindow;
    // позиция курсора в зоне видимости игрока
    sf::Vector2f mousePosView;

    // мапа картинок/ игры
    std::unordered_map<std::string, sf::Image> images;

    // чисто виртуальная ф-я раскладки для каждого стейта
    virtual void initKeybinds() = 0;
    // инициализация фоновой музыки
    virtual void initMusic() = 0;
    // инициализация камеры
    virtual void initView() = 0;

public:
    State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~State();

    // проверка текущего стейта
    const bool &getQuit() const;

    // закрытие стейта
    virtual void endState();

    // апдейт состояния музыки
    virtual void updateMusic();
    // апдейт координатов мыши , (3 разных)
    virtual void updateMousePositions();
    // апдейт польз. ввода
    virtual void updateInput(const float &dt) = 0;
    // обновление камеры
    virtual void updateView() = 0;
    // апдейт всего
    virtual void update(const float &dt) = 0;
    // отрисовка всего
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

#endif