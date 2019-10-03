#include "CredentialsState.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------

void CredentialsState::initVariables() noexcept(true)
{
	char_size = this->window->getSize().x / 100 + this->window->getSize().y / 100;
	outl_thick = 0.5f;
	txt_color = sf::Color(207, 122, 0, 250);
	outl_color = sf::Color(0, 0, 0, 255);
	music_volume = 10;
}

void CredentialsState::initBackground() noexcept(false)
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("./img/Select_Screen.png"))
		throw std::system_error(errno, std::system_category(), "Failed to open img/Select_Screen.png");

	this->background.setTexture(&this->backgroundTexture);
}

void CredentialsState::initFonts() noexcept(false)
{
	if (!this->font.loadFromFile("Fonts/METAL KINGDOM.ttf"))
		throw std::system_error(errno, std::system_category(), "Failed to open Fonts/METAL KINGDOM.ttf");
}

void CredentialsState::initKeybinds() noexcept(false)
{
	std::ifstream ifs("confs/credentialsstate_keybinds.conf");

	if (!ifs.is_open())
		throw std::system_error(errno, std::system_category(), "Failed to open confs/credentialsstate_keybinds.conf");

	std::string key = "";
	std::string key2 = "";

	while (ifs >> key >> key2)
	{
		this->keybinds[key] = this->supportedKeys->at(key2);
	}

	ifs.close();
}

void CredentialsState::initThx() noexcept(false)
{
	std::fstream fs;
	fs.open(R"(./confs/credits.conf)", std::ios::in);
	if (!fs.is_open())
		throw std::system_error(errno, std::system_category(), "Failed to open ./confs/credits.conf");
	std::vector<std::string> rows;
	std::string buf;
	int i = 0;
	while (std::getline(fs, buf))
	{
		rows.push_back(buf);
		i++;
	}
	fs.close();

	credits_size = static_cast<unsigned short>(rows.size());
	credits = new sf::Text[credits_size];
	unsigned short indent = this->window->getSize().y / 1.15f;
	for (unsigned short i = 0; i < credits_size; i++)
	{
		credits[i].setString(rows.at(i));
		credits[i].setFont(this->font);
		credits[i].setFillColor(txt_color);
		credits[i].setCharacterSize(char_size);
		credits[i].setOutlineThickness(outl_thick);
		credits[i].setOutlineColor(outl_color);
		credits[i].setPosition(getMiddleX() - this->credits[i].getGlobalBounds().width / 2, this->credits[i].getGlobalBounds().height / 2 + indent);
		indent += this->credits[i].getGlobalBounds().height + char_size / 2;
	}
}

void CredentialsState::initMusic() noexcept(false)
{
	if (!music.openFromFile(R"(./sounds/CredentialsTheme.ogg)"))
		throw std::system_error(errno, std::system_category(), "Failed to open ./sounds/CredentialsTheme.ogg");

	music.setLoop(true);
	music.setVolume(10);
	music.play();
}

void CredentialsState::initView() noexcept(true)
{
	view.reset(sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y));
	view.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
}

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

CredentialsState::CredentialsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
	: State(window, supportedKeys, states)
{
	try
	{
		this->initVariables();
		this->initBackground();
		this->initFonts();
		this->initKeybinds();
		this->initThx();
		this->initMusic();
		this->initView();
	}
	catch (const std::system_error &ex)
	{
		std::cerr << "Error in CredentialsState.cpp." << ex.what() << " (" << ex.code() << ")" << std::endl;
	}
}

CredentialsState::~CredentialsState()
{
	if (credits_size > 0)
		delete[] credits;
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

void CredentialsState::textFlow()
{
	for (unsigned short i = 0; i < this->credits_size; i++)
	{
		this->credits[i].setPosition(this->credits[i].getPosition().x, this->credits[i].getPosition().y - 0.3f);
	}

	if (this->credits[credits_size - 1].getPosition().y < 0)
	{
		delete[] credits;
		credits_size = 0;
	}
}

// середина экрана по X
float CredentialsState::getMiddleX() const { return this->window->getSize().x / 2; }

void CredentialsState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void CredentialsState::updateView()
{
	this->window->setView(view);
}

void CredentialsState::update(const float &dt)
{
	this->updateInput(dt);
	this->updateMusic();
	this->textFlow();
	this->updateView();
}

void CredentialsState::renderThx(sf::RenderTarget *target)
{
	for (unsigned short i = 0; i < credits_size; i++)
	{
		if (this->credits[i].getPosition().y > this->window->getSize().y / 7 && this->credits[i].getPosition().y < this->window->getSize().y / 1.15f)
		{
			target->draw(credits[i]);
		}
	}
}

void CredentialsState::render(sf::RenderTarget *target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderThx(target);
}