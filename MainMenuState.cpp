#include "MainMenuState.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------

void MainMenuState::initVariables() noexcept(true)
{
	this->btn_w = 250.f;
	this->btn_h = 50.f;
	music_volume = 30;
}

void MainMenuState::initBackground() noexcept(false)
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("./img/Select_Screen.png"))
		throw std::logic_error("Can't open Select_Screen.png !");

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts() noexcept(false)
{
	if (!this->font.loadFromFile("Fonts/GunmetalRegular.ttf"))
		throw std::logic_error("Can't open GunmetalRegular.ttf !");
}

void MainMenuState::initKeybinds() noexcept(false)
{
	std::ifstream ifs("./confs/mainmenustate_keybinds.conf");

	if (!ifs.is_open())
		throw std::system_error(errno, std::system_category(), "Failed to open confs/mainmenustate_keybinds.conf");

	std::string key = "";
	std::string key2 = "";

	while (ifs >> key >> key2)
	{
		this->keybinds[key] = this->supportedKeys->at(key2);
	}

	ifs.close();
}

void MainMenuState::initButtons() noexcept(false)
{
	this->buttons["GAME_STATE"] = new Button(this->getMiddleX(), this->getMiddleY() - btn_h - 10, btn_w, btn_h,
											 &this->font, "New Game", btn_h,
											 sf::Color(200, 184, 160, 230), sf::Color(207, 122, 0, 250), sf::Color(225, 31, 40, 255),
											 sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["CREDENTIALS"] = new Button(this->getMiddleX(), this->getMiddleY(), btn_w, btn_h,
											  &this->font, "Credentials", btn_h,
											  sf::Color(200, 184, 160, 230), sf::Color(207, 122, 0, 250), sf::Color(225, 31, 40, 255),
											  sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["QUIT"] = new Button(this->getMiddleX(), this->getMiddleY() + btn_h + 10, btn_w, btn_h,
									   &this->font, "Quit", btn_h,
									   sf::Color(200, 184, 160, 230), sf::Color(207, 122, 0, 250), sf::Color(225, 31, 40, 255),
									   sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::initMusic() noexcept(false)
{
	if (!music.openFromFile(R"(./sounds/MainMenuTheme.ogg)"))
		throw std::system_error(errno, std::system_category(), "Failed to open ./sounds/MainMenuTheme.ogg");

	music.setLoop(true);
	music.setVolume(music_volume);
	music.setPlayingOffset(sf::seconds(5));
	music.play();
}

void MainMenuState::initView() noexcept(true)
{
	view.reset(sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y));
	view.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
}

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
	: State(window, supportedKeys, states)
{
	try
	{
		this->initVariables();
		this->initBackground();
		this->initFonts();
		this->initKeybinds();
		this->initButtons();
		this->initMusic();
		this->initView();
	}
	catch (const std::system_error &ex)
	{
		std::cerr << "Error in MainMenuState.cpp." << ex.what() << " (" << ex.code() << ")" << std::endl;
	}
	catch (const std::logic_error &ex)
	{
		std::cerr << "Error in MainMenuState. " << ex.what() << std::endl;
	}
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

// середина экрана по X ,учитывая ширину кнопки
float MainMenuState::getMiddleX() const { return this->window->getSize().x / 2 - btn_w / 2; }

// середина экрана по Y,учитывая высоту кнопки
float MainMenuState::getMiddleY() const { return this->window->getSize().y / 2 - btn_h / 2; }

// апдейт нажатий клавиатуры (обновление слишком быстрое ,закрывает все стейты)
void MainMenuState::updateInput(const float &dt)
{
	// выход
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	//	this->endState();
}

// проверка нажатий на кнопки меню
void MainMenuState::updateButtons()
{

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->music.stop();
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Credits
	if (this->buttons["CREDENTIALS"]->isPressed())
	{
		this->music.stop();
		this->states->push(new CredentialsState(this->window, this->supportedKeys, this->states));
	}

	//Quit the game
	if (this->buttons["QUIT"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::updateView()
{
	this->window->setView(view);
}

// общий апдейт
void MainMenuState::update(const float &dt)
{
	this->updateMusic();
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
	this->updateView();
}

// отрисовка кнопок меню
void MainMenuState::renderButtons(sf::RenderTarget *target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

// общая отрисовка
void MainMenuState::render(sf::RenderTarget *target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);
}
