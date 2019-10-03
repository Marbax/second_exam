#include "State.h"

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states) try
{
    this->window = window;
    if (window == nullptr)
    {
        throw std::logic_error("Window points to nowhere !");
    }
    this->supportedKeys = supportedKeys;
    if (supportedKeys == nullptr)
    {
        throw std::logic_error("supportedKeys points to nowhere !");
    }
    this->states = states;
    this->quit = false;
}
catch (const std::logic_error &ex)
{
    std::cerr << "Error in State.cpp. " << ex.what() << std::endl;
}

State::~State()
{
}

const bool &State::getQuit() const
{
    return this->quit;
}

// нужно добавить вопросик проверки ,а то завршает все стейты
void State::endState()
{
    this->quit = true;
}

void State::updateMusic()
{
    if (this->music.getStatus() != sf::SoundSource::Playing)
    {
        music.play();
    }
}
void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
