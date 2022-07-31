#include "GameEngine.h"
#include<fstream>

//init functions
void Game::initVariables()
{
	this->renderWindow = nullptr;
	this->player = nullptr;
	this->level = nullptr;
}

void Game::initRenderWindow()
{
	this->videoMode.height = 1080;
	this->videoMode.width = 1920;
	this->renderWindow = new sf::RenderWindow(videoMode, "Game 2");
	this->renderWindow->setFramerateLimit(60);
}

void Game::initZombies()
{
	this->zombie1 = new Zombie(sf::Vector2f{ 11.f , 3.f }, MALE);
	this->zombie2 = new Zombie(sf::Vector2f{ 20.f , 12.f }, MALE);
	this->zombie3 = new Zombie(sf::Vector2f{ 24.f , 5.f }, MALE);
	this->zombie4 = new Zombie(sf::Vector2f{ 6.f , 15.f }, MALE);
	this->zombie5 = new Zombie(sf::Vector2f{ 15.f , 8.f }, MALE);
}

void Game::initPlayer()
{
	this->player = new Player;
}

void Game::initLevel()
{
	std::ifstream file("level.txt");

	this->level = new Level;
	
	file >> this->level->width >> this->level->height;
	
	this->level->matrix = new char* [this->level->width];

	for (int i = 0; i < this->level->width; i++)
	{
		this->level->matrix[i] = new char[this->level->height];
		for (int j = 0; j < this->level->height; j++)
		{
			file >> this->level->matrix[i][j];
			std::cout << this->level->matrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
	this->level->objects = new char* [this->level->width];

	for (int i = 0; i < this->level->width; i++)
	{
		this->level->objects[i] = new char[this->level->height];
		for (int j = 0; j < this->level->height; j++)
		{
			file >> this->level->objects[i][j];
			std::cout << this->level->objects[i][j] << " ";
		}
		std::cout << "\n";
	}

	file.close();
}

void Game::initMap()
{
	this->map = new Map;
}

const bool Game::isWindow()
{
	return this->renderWindow->isOpen();
}

const bool Game::isEvent()
{
	return this->renderWindow->pollEvent(this->event);
}

//contructor & destructor
Game::Game()
{
	this->initVariables();
	this->initRenderWindow();
	this->initLevel();
	this->initMap();
	this->initPlayer();
	this->initZombies();
}

Game::~Game()
{
	delete(this->player);
	delete(this->zombie1);
	for (int i = 0; i < this->level->width; i++)
	{
		delete(this->level->matrix[i]);
		delete(this->level->objects[i]);
	}
	delete(this->level->matrix);
	delete(this->level->objects);
	delete(this->level);
	delete(this->renderWindow);
}

//pool events
void Game::poolEvents()
{
	while (this->isEvent())
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->renderWindow->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->renderWindow->close();
			}
		default:
			break;
		}
	}
}

//render & update
void Game::renderMap()
{
	this->map->renderMap(this->renderWindow, this->level->matrix,this->level->objects ,this->level->width, this->level->height);
}

void Game::renderZombies()
{
	this->zombie1->render(this->renderWindow);
	this->zombie2->render(this->renderWindow);
	this->zombie3->render(this->renderWindow);
	this->zombie4->render(this->renderWindow);
	this->zombie5->render(this->renderWindow);
}

void Game::updateZombies()
{
	this->zombie1->update(this->level->matrix);
	this->zombie2->update(this->level->matrix);
	this->zombie3->update(this->level->matrix);
	this->zombie4->update(this->level->matrix);
	this->zombie5->update(this->level->matrix);
}

void Game::renderPlayer()
{
	this->player->render(this->renderWindow);
}

void Game::updatePlayer()
{
	this->player->update(this->level->matrix);
}

void Game::render()
{
	this->renderWindow->clear();

	this->renderMap();
	this->renderPlayer();
	this->renderZombies();
	this->renderWindow->display();
}

void Game::update()
{
	this->poolEvents();

	this->updatePlayer();
	this->updateZombies();
}

