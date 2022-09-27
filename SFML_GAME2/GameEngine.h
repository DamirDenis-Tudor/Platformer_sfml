#pragma once

#include <iostream>
#include"Player.h"
#include"Zombie.h"
#include"Box.h"
#include"Map.h"
#include"Menu.h"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

#define windowWidth 1920
#define windowHeight 1080

#define viewTilesW 1920 / 60
#define viewTilesH 1080 / 60 

#define switchClose 40
#define switchOpen 43

#define doorLocked 39
#define doorUnlocked 41
#define doorOpen 42

enum zombieType {MALE = 0 , FEMALE};

struct Level {
	int heightM;
	int widthM;
	int ** matrix;
	int **objects;
};

class Game
{
private:
	//time 
	sf::Clock clock;
	sf::Time deltaTime;

	//menu
	bool inMenu;
	Menu* menu;

	//view
	sf::View* view;
	sf::View* menuView;

	//level & map
	Level* level;
	Map* map;

	//Zombies
	int deadZombiesCounter;
	std::vector<Zombie*> zombies;
	std::vector<sf::Vector2f> zPositions;
	
	//boxes
	std::vector<Box*> boxes;
	std::vector<sf::Vector2f> bPositions;

	//door adn switch
	int openSwtCounter;
	std::vector<sf::Vector2f> swtPositions;
	sf::Vector2f dPosition;

	//shop
	sf::Vector2f sPosition;

	//player
	Player *player;
	
	//variables
	sf::Event event;
	sf::VideoMode videoMode;
	sf::RenderWindow* renderWindow;


	//initialization function
	void initVariables();
	void initRenderWindow();
	void initFontAndText();
	void initZombies();
	void initBoxes();
	void initPlayer();
	void initSwitches();
	void initDoor();
	void initShop();
	void initView();
	void initLevel();
	void initMap();
	void initMenu();

	//restart
	void restartLevel();

	void drawShopLogo();
	void drawShopMessage();

	//text
	sf::Font* font;
	sf::Text* text;
	sf::Text* textDisplay;

	void drawText(std::string message);
	bool drawEvent = true;
	bool textDrawFinish = true;;
	bool playerDoorCheck = false;
	float time;
	float maxTime;

	//draw tab info
	void renderTabInfo();

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
	void updateView();
	void renderMenu();

	void renderMapTiles();
	void renderMapObjects();
	
	void renderBoxes();
	void updateBoxes();

	void renderZombies();
	void updateZombies();
	
	void renderPlayer();
	void renderPlayerInfo();
	void updatePlayer();

	bool openDoor;
	bool deadZombies;

	bool playerInShop;

	void updateSwitchesAndDoor();

	void updateTime();

	void renderView();
	void renderMenuView();

	//main render, update functions
	void render();
	void update();

};

