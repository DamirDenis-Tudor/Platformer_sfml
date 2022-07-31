#pragma once

#include <iostream>
#include"Player.h"
#include"Zombie.h"
#include"Map.h"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

enum zombieType {MALE = 0 , FEMALE};

struct Level {
	int width;
	int height;
	char** matrix;
	char** objects;
};

class Game
{
private:
	//level & map
	Level* level;
	Map* map;

	//Zombies
	Zombie* zombie1;
	Zombie* zombie2;
	Zombie* zombie3;
	Zombie* zombie4;
	Zombie* zombie5;

	//player
	Player *player;
	
	//variables
	sf::Event event;
	sf::VideoMode videoMode;
	sf::RenderWindow* renderWindow;


	//initialization function
	void initVariables();
	void initRenderWindow();
	void initZombies();
	void initPlayer();
	void initLevel();
	void initMap();

public:
	//bool functions
	const bool isEvent();
	const bool isWindow();

	//contructor & destructor 
	Game();
	~Game();

	//main methods

	void poolEvents();

	//update, render for player
	void renderMap();
	void renderZombies();
	void updateZombies();
	void renderPlayer();
	void updatePlayer();

	//main render, update functions
	void render();
	void update();

};

