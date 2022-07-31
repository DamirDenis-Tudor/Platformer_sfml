#pragma once

#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

enum movementZombie { IDLEZ = 0, WALKZ, ATTACKZ, DEADZ };

#define mapWidth 32

class Zombie{

	//texture & sprite
	sf::Texture* texture;
	sf::Sprite* sprite;

	//game physics
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f direction;

	//init
	void setPhisics();
	void setTexture(bool type);
	void setSprite(sf::Vector2f position);

	//animation
	float maxTime;
	float time;
	int frameIndexIdle;
	int frameIndexWalk;
	int frameIndexAttack;
	int frameIndexDead;
	bool reverse;

	void animation(movementZombie move, bool reverse);

	//bool phisics
	bool leftCollision;
	bool rightCollision;
	bool groundCollision;
	bool falling;

	public:

	//render & update
	void update(char**& map);
	void render(sf::RenderTarget* target);

	//contructor and destructor
	Zombie(sf::Vector2f position , bool type);
	~Zombie();

};

