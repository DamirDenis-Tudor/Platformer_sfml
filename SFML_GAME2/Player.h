#pragma once

#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

#define mapWidth 32
#define mapHeight 18

enum movement { IDLE, RUN , JUMP , WALK , DEAD };

class Player
{
private:
	//texture & sprite
	sf::Texture *texture;
	sf::Sprite *sprite;

	//game physics
	sf::Vector2f velocity;
	sf::Vector2f position;

	//init
	void setPhisics();
	void setTexture();
	void setSprite();

	//animation
	float maxTime;
	float time;
	int frameIndex;
	bool reverse;
	void animation(movement move, bool reverse);

	//bool phisics
	bool leftCollision;
	bool rightCollision;
	bool groundCollision;
	bool topCollision;

	bool isJumping;

	bool bouncingR;
	bool bouncingL;
	bool bouncingD;

	bool maxHeightReached;
	bool falling;



public:

	//render & update
	void update(char**&map);
	void render(sf::RenderTarget* target);
	
	//contructor & destructor
	Player();
	~Player();
};

