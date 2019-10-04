#include "GameState.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------
void GameState::initVariables() noexcept(true)
{
	music_volume = 10;
}

void GameState::initKeybinds() noexcept(false)
{
	std::ifstream ifs(R"(./confs/gamestate_keybinds.conf)");

	if (!ifs.is_open())
		throw std::system_error(errno, std::system_category(), "Failed to open ./confs/gamestate_keybinds.conf");

	std::string key = "";
	std::string key2 = "";

	while (ifs >> key >> key2)
	{
		this->keybinds[key] = this->supportedKeys->at(key2);
	}

	ifs.close();
}

void GameState::initImages() noexcept(false)
{
	if (!this->images["TARMA_TEXTURE"].loadFromFile(R"(./img/Guls_latem_Tarma.png)"))
		throw std::system_error(errno, std::system_category(), "Failed to open ./img/Guls_latem_Tarma.png");
	//images["TARMA_TEXTURE"].createMaskFromColor(sf::Color(86, 177, 222)); // убираем фон спрайту

	if (!this->images["BKG_LVL1"].loadFromFile(R"(./img/bkg_lvl1.png)"))
		throw std::system_error(errno, std::system_category(), "Failed to open ./img/bkg_lvl1.png");
}

void GameState::initPlayers() noexcept(false)
{
	this->player = new Player(terrain.at(0).left, 50, this->images.at("TARMA_TEXTURE"), "Tarma");
	if (!player)
		throw std::logic_error("Player wasn't created !");
}

void GameState::initLvl() noexcept(false)
{
	if (!this->tBkg.loadFromImage(images.at("BKG_LVL1")))
		throw std::logic_error("Can't load texture From Image !");
	this->tBkg.setSmooth(true);
	this->sBkg.setTexture(tBkg, true);

	// загрузка обьектов карты
	terrain.push_back(sf::FloatRect(2259.f, 220.f, 1565.f, 20.f));

	terrain.push_back(sf::FloatRect(2250.f, 0.f, 20.f, 240.f));

	terrain.push_back(sf::FloatRect(3814.f, 0.f, 20.f, 240.f));
}

void GameState::initMusic() noexcept(false)
{
	if (!music.openFromFile(R"(./sounds/GameTheme.ogg)"))
		throw std::system_error(errno, std::system_category(), "Failed to open ./sounds/GameTheme.ogg");

	music.setLoop(true);
	music.setVolume(10);
	music.play();
}

void GameState::initView() noexcept(true)
{
	view.setSize(1240, 720);
	view.setCenter(this->view.getSize().x / 2, this->player->getPosY());
}

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states) try : State(window, supportedKeys, states)
{
	try
	{
		this->initVariables();
		this->initMusic();
		this->initKeybinds();
		this->initImages();
		this->initLvl();
		this->initPlayers();
		this->initView();
	}
	catch (const std::system_error &ex)
	{
		std::cerr << "Error in GameState.cpp." << ex.what() << " (" << ex.code() << ")" << std::endl;
	}
	catch (const std::logic_error &ex)
	{
		std::cerr << "Error in GameState.cpp. " << ex.what() << std::endl;
	}
}
catch (const std::logic_error &ex)
{
	std::cerr << "Error in GameState.cpp. " << ex.what() << std::endl;
}

GameState::~GameState()
{
	delete this->player;
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

void GameState::checkCollisions(const float &dt)
{
	for (size_t i = 0; i < terrain.size(); i++)
	{
		if (this->player->getRect().intersects(this->terrain[i]))
		{
			if ((this->player->getPosY() >= this->terrain[i].top - this->terrain[i].height) && (this->player->getPosY() <= this->terrain[i].top - this->terrain[i].height * 0.5f))
			{
				this->player->setOnGround(true);
				this->player->setPosY(this->terrain[i].top - this->terrain[i].height - 20);
				std::cout << "\nINTERSECTS top "
						  << "\nposX= " << this->player->getPosX() << " posY= " << this->player->getPosY() << std::endl;
			}
			if ((this->player->getPosX() <= this->terrain[i].left) && (this->player->getPosX() >= this->terrain[i].left - this->terrain[i].width * 0.5f))
			{
				this->player->setPosX(this->terrain[i].left);
				std::cout << "\nINTERSECTS right "
						  << "\nposX= " << this->player->getPosX() << " posY= " << this->player->getPosY() << std::endl;
			}
			if ((this->player->getPosX() >= this->terrain[i].left - this->terrain[i].width) && (this->player->getPosX() <= this->terrain[i].left - this->terrain[i].width * 0.5f))
			{
				this->player->setPosX(this->terrain[i].left - this->terrain[i].width);
				std::cout << "\nINTERSECTS left "
						  << "\nposX= " << this->player->getPosX() << " posY= " << this->player->getPosY() << std::endl;
			}
		}
		//if (!this->player->getRect().intersects(this->terrain[i]))
		//{
		//	this->player->setOnGround(false);
		//	std::cout << "\nNOT INTERSECTS " << this->terrain[i].top << std::endl;
		//}
	}
}

void GameState::updateView()
{
	if (this->player->getPosX() >= this->view.getSize().x / 2 && this->player->getPosX() <= (this->sBkg.getGlobalBounds().width - this->view.getSize().x / 2))
	{
		view.setCenter(this->player->getPosX(), this->view.getCenter().y);
	}

	this->window->setView(view);
}

void GameState::updateInput(const float &dt)
{
	// атака
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player->atack();
	}
	// выход
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
	//--------------------------------------------------------------------------------------------------------------
	// проверка на движения
	if (sf::Keyboard::isKeyPressed)
	{ // если в лево
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		{
			// вниз и влево
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SIT")))))
				player->move(-0.2f, 0.2f, dt);
			// влево
			else
				player->move(-0.2f, 0.f, dt);
		}
		// если в вправо
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		{
			// вниз и вправо
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SIT")))))
				player->move(0.2f, 0.2f, dt);
			// вправо
			else
				player->move(0.2f, 0.f, dt);
		}

		// вниз
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SIT"))))
			player->move(0.f, 0.2f, dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP"))))
		{ // вверх и вправо
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP")))))
				player->move(1.2f, -1.2f, dt);
			// вверх и влево
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("JUMP")))))
				player->move(-1.2f, -1.2f, dt);
			// вверх
			else
				player->move(0.f, -1.2f, dt);
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	else
	{
		// обнуление движения
		player->setMove(false);
	}
}

void GameState::update(const float &dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->checkCollisions(dt);
	this->updateMusic();

	this->player->update(dt);
	this->updateView();

	//std::cout << dt << "\nposX= " << this->player->getPosX() << " posY= " << this->player->getPosY() << std::endl;
}

void GameState::render(sf::RenderTarget *target)
{
	if (!target)
		target = this->window;
	target->draw(sBkg);
	this->player->render(target);
}
