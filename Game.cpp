#include "Game.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Game::initWindow() noexcept(false)
{
    // начальная инициализация дэфолтными параметрами
    std::string title = "Game";
    sf::VideoMode window_bounds(800, 242);
    this->videoModes = sf::VideoMode::getFullscreenModes();
    this->fullscreen = false;
    unsigned int frame_limit = 60;
    bool vertical_sync = false;
    unsigned antialiasing_level = 0;

    // загрузка конфигурации из файла
    std::ifstream ifs;
    ifs.open(R"(./confs/window.conf)");
    if (!ifs.is_open())
        throw std::system_error(errno, std::system_category(), "Failed to open ./confs/window.conf");

    std::getline(ifs, title);
    ifs >> window_bounds.width >> window_bounds.height;
    ifs >> frame_limit;
    ifs >> vertical_sync;
    ifs >> this->fullscreen;
    ifs >> antialiasing_level;
    ifs.close();
    this->windowSettings.antialiasingLevel = antialiasing_level;

    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title);

    this->window->setFramerateLimit(frame_limit);
    this->window->setVerticalSyncEnabled(vertical_sync);
}

void Game::initKeys() noexcept(false)
{
    std::ifstream ifs(R"(./confs/supported_keys.conf)");

    if (!ifs.is_open())
        throw std::system_error(errno, std::system_category(), "Failed to open ./confs/supported_keys.conf");

    std::string key = "";
    int key_value = 0;

    while (ifs >> key >> key_value)
    {
        this->supportedKeys[key] = key_value;
    }
    ifs.close();
}

void Game::initStates() noexcept(false)
{

    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
    if (states.empty())
        throw std::logic_error("GameState wasn't pushed in Game.cpp !");
}

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Game::Game()
{
    try
    {
        this->initWindow();
        this->initKeys();
        this->initStates();
    }
    catch (const std::system_error &ex)
    {
        std::cerr << "Error in Game.cpp.cpp." << ex.what() << " (" << ex.code() << ")" << std::endl;
    }
    catch (const std::logic_error &ex)
    {
        std::cerr << "Error in Game.cpp. " << ex.what() << std::endl;
    }
}

Game::~Game()
{
    delete this->window;

    //пока есть стек состояний , то удаляет по одному сверху
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

//---------------------------------------------------------------------------------------------------
//---------------------------------Methods-----------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Game::endApplication()
{
    std::cout << "Ending Application!" << std::endl;
}

void Game::updateDt()
{
    this->dt = this->dtClock.getElapsedTime().asMilliseconds();
    this->dtClock.restart();
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    //если есть состояния
    if (!this->states.empty())
    {
        //если окно выбрано
        if (this->window->hasFocus())
        {
            // апдейт всего в в верхнем стейте
            this->states.top()->update(this->dt);

            //если из состояния вышли - удалить его
            if (this->states.top()->getQuit())
            {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    //очищает окно
    this->window->clear();

    //рендерит все в верхнем стейте
    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
