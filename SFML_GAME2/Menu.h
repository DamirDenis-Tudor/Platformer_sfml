#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>

#define windowWidth 1920
#define windowHeight 1080

enum menuState {Main , Levels , Controls , Exit , Start , Pause , GameOver , WinLevel , Shop };

class Menu
{
private:
	//
	bool clicked;
	float time;
	float maxTime;


	sf::Vector2f mousePos = { 0 , 0 };
	//texture and sprites
	sf::Texture* bgTexture;
	sf::Sprite* bgSprite;

	sf::Texture* windowTexture;
	sf::Sprite* windowSprite;

	sf::Font *font;
	sf::Text *text;


	//init
	void initVariables();
	void initTextures();
	void initSprites();
	void initFont();
	void initText();
		

	//button pozition
	sf::Vector2f buttonPos;

public:
	bool inMenu;

	//selector
	menuState menuSelector;
	bool restart;

	//contructor & destructor
	Menu();
	~Menu();

	//render
	void renderMenu(sf::RenderTarget *target , sf::Vector2f viewPos , int &coins , int &diamonds , int&heath , int &shiends , int &attacks );
};

