#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>

#include "Box.h"
//init
void Box::initVariables()
{
	this->velocity = { 0 , 0 };
	this->groundStatus = true;
	this->fallingStatus = false;
	this->leftStatus = false;
	this->rightStatus = false;
	this->rightStatusPlayer = false;
	this->leftStatusPlayer = false;
	this->topColision = false;
	this->bottomCollision = false;

	this->wasMoved = false;

	this->bottomBoxCollision = false;

	this->pushedLeft = false;
	this->pushedRight = false;
}

void Box::initTexture()
{
	this->texture = new sf::Texture;
	this->texture->loadFromFile("sprites/Box/box.png");
}

void Box::initSprite()
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(*this->texture);
}

void Box::restart()
{
	this->initVariables();
	this->setPosition(this->spawnPosition);
}

//set - get map position
void Box::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->spawnPosition = position;
	this->sprite->setPosition(this->position * 60.f);
}

void Box::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

sf::Vector2f Box::getPosition()
{
	return this->position;
}

sf::Vector2f Box::getVelocity()
{
	return this->velocity;
}

bool Box::getFallingStatus()
{
	return this->fallingStatus;
}

void Box::repos()
{
	this->velocity.x = 0.1f;
	this->position.x = (this->position.x * 60.f + this->velocity.x) / 60.f;
	this->sprite->move(this->velocity);
}

//update render
void Box::update(sf::Vector2f playerPos, sf::Vector2f &playerVelocity , std::vector<sf::Vector2f> zombiesPos , int**&map ,float deltaTime , bool playerDead , bool pLayerJumping)
{
	//decceleration	
	if ( (!this->pushedLeft && !this->pushedRight) || playerDead)
	{
		this->velocity.x = 0;
	}

	//gravity
	if (this->fallingStatus && !this->groundStatus && !this->bottomBoxCollision)
	{
		this->velocity.y += (25.f * deltaTime);
	}

	//PLAYER COLISIONS
	//left right playerColsion v2

	if (playerPos.x + 0.8 >= this->position.x && playerPos.x  <= this->position.x
		&& playerPos.y - 0.47 <= this->position.y + 0.95 && playerPos.y + 0.5 > this->position.y)
	{
		this->pushedRight = true;
		this->pushedLeft = false;
	}

	if (playerPos.x + 1 >= this->position.x + 1 && playerPos.x <= this->position.x + 1
		&& ( playerPos.y - 0.47 <= this->position.y + 1 && playerPos.y + 0.5 > this->position.y ) )
	{
		this->pushedRight = false;
		this->pushedLeft = true;
	}

	if (playerVelocity.x < 0)
	{
		this->pushedRight = false;
		this->rightStatusPlayer = false;
	}
	else if(playerVelocity.x > 0)
	{
		this->pushedLeft = false;
		this->leftStatusPlayer = false;
	}

	if (playerPos.y + 0.40 < this->position.y || playerPos.y - 0.5 > this->position.y + 1 || playerDead )
	{
		this->pushedRight = false;
		this->pushedLeft = false;
		this->velocity.x = 0;
	}

	if (this->pushedLeft)
	{
		if (!topColision)
		{
			if (this->leftStatus)
			{
				this->leftStatusPlayer = true;
				this->velocity.x = 0;
				this->pushedLeft = false;
			}
			else
			{
				this->velocity.x = playerVelocity.x;
			}
		}			
		else
		{
			this->velocity.x = 0;
			this->pushedLeft = false;
		}
	}
	else if (this->pushedRight)
	{
		if (!topColision)
		{
			if (this->rightStatus)
			{
				this->rightStatusPlayer = true;
				this->velocity.x = 0;
				this->pushedRight = false;
			}
			else
			{
				this->velocity.x = playerVelocity.x;
			}
		}
		else
		{
			this->pushedRight = false;
			this->velocity.x = 0;
		}
	}

	//top player colision
	if (playerPos.y + 0.50 >= position.y && playerPos.y - 0.50 <= this->position.y && playerPos.x + 0.65 >= this->position.x && playerPos.x + 0.1 <= this->position.x + 1)
	{
		this->topColision = true;
	}
	else
	{
		this->topColision = false;
	}

	//bottom player collision
	if (playerPos.y + 0.40 >= position.y + 1 && playerPos.y - 0.40 <= this->position.y + 1 && playerPos.x + 0.6 >= this->position.x && playerPos.x + 0.1 <= this->position.x + 1)
	{
		this->bottomCollision= true;
	}
	else
	{
		this->bottomCollision = false;
	}

	//new position
	sf::Vector2f newPosition;
	newPosition.x = (this->position.x * 60.f + this->velocity.x) / 60.f;
	newPosition.y = (this->position.y * 60.f + this->velocity.y) / 60.f;

	//HERE we can put box bottom collision
	//ground colision 
	if (map[(int)(newPosition.y) + 1][(int)(newPosition.x + 0.1)] != 0 || map[(int)(newPosition.y) + 1][(int)(newPosition.x + 0.90)] != 0 || this->bottomBoxCollision)//bottom
	{
		this->groundStatus = true;
		this->fallingStatus = false;
		this->velocity.y = 0;
	}
	else 
	{
		this->groundStatus = false;
		this->fallingStatus = true;
	}


	//left - right wall 
		if (playerVelocity.x > 0)
		{
			if ((map[(int)(newPosition.y + 0.1)][(int)(newPosition.x + 0.99)] != 0 || map[(int)(newPosition.y + 0.90)][(int)(newPosition.x + 0.99)] != 0 || newPosition.x > 3840 / 60) && playerPos.y + 0.30 >= this->position.y && playerPos.y - 0.50 <= this->position.y + 0.99)
			{
				newPosition.x = this->position.x;
				this->rightStatus = true;
				this->velocity.x = 0;
			}
		}
		else if (playerVelocity.x < 0)
		{
			if ((map[(int)(newPosition.y + 0.1)][(int)(newPosition.x)] != 0 || map[(int)(newPosition.y + 0.90)][(int)(newPosition.x)] != 0 || newPosition.x < 0) && playerPos.y + 0.50 >= this->position.y && playerPos.y - 0.50 <= this->position.y + 0.99)
			{
				newPosition.x = this->position.x;
				this->leftStatus = true;
				this->velocity.x = 0;
			}
		}

		if (this->fallingStatus && this->rightStatus)
		{
			this->rightStatus = false;
		}
		if (this->fallingStatus && this->leftStatus)
		{
			this->leftStatus = false;
		}


		//actualize statuses
		if (this->rightStatus && playerVelocity.x < 0)
		{
			this->rightStatusPlayer = false;
		}

		if (this->leftStatus && playerVelocity.x > 0)
		{
			this->leftStatusPlayer = false;
		}

		if (playerPos.y + 0.5 <= this->position.y || playerPos.y - 0.5 >= this->position.y + 1)
		{
			this->rightStatusPlayer = false;
			this->leftStatusPlayer = false;
		}

		if (rightStatus)
		{
			newPosition.x = position.x;
			this->pushedRight = false;
			this->velocity.x = 0;
		}

		if (leftStatus)
		{
			newPosition.x = position.x;
			this->pushedLeft = false;
			this->velocity.x = 0;
		}

	//set newPosition
	if ( (!rightStatus || !leftStatus) && (!this->topColision || !this->groundStatus ) )
	{
		this->position = newPosition;
	}

	if (groundStatus && this->velocity.x == 0 && !this->pushedLeft && !this->pushedRight)
	{
		this->position.y = (int)(this->position.y + 0.2);
		this->sprite->setPosition(this->position * 60.f);
	}
	
	//ZOMBIES COLISIONS
	//left right colison
	for (int i = 0; i < zombiesPos.size(); i++)
	{
		//left right colision
		if (zombiesPos[i].x + 0.9 > this->position.x && zombiesPos[i].x < this->position.x + 1 && zombiesPos[i].y < this->position.y + 1 && zombiesPos[i].y + 1 > this->position.y)
		{
			this->rightZombiesStatus[i] = true;
		}
		else
		{
			this->rightZombiesStatus[i] = false;
		}

		if (zombiesPos[i].x < this->position.x && zombiesPos[i].x + 1 > this->position.x && zombiesPos[i].y < this->position.y + 1 && zombiesPos[i].y + 1 > this->position.y)
		{
			this->leftZombiesStatus[i] = true;
		}
		else
		{
			this->leftZombiesStatus[i] = false;
		}

		//top bottom zombie colision
		if ( zombiesPos[i].x + 0.8 >= position.x  && zombiesPos[i].x <= position.x + 0.7 && zombiesPos[i].y <= this->position.y + 0.5 && zombiesPos[i].y + 1 >= this->position.y)
		{
			this->topZombiesStatus[i] = true;
		}
		else
		{
			this->topZombiesStatus[i] = false;
		}

		if (zombiesPos[i].x < position.x + 1 && zombiesPos[i].x + 0.8 > position.x && zombiesPos[i].y + 1 >= this->position.y && zombiesPos[i].y <= this->position.y - 0.1 )
		{
			this->bottomZombiesStatus[i] = true;
		}
		else
		{
			this->bottomZombiesStatus[i] = false;
		}
	}

	//move
	this->sprite->move(this->velocity);
}

void Box::render(sf::RenderTarget *target)
{
	target->draw(*this->sprite);
}

//constructor & destructor
Box::Box(sf::Vector2f position)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->setPosition(position);
}

Box::~Box()
{
	delete(this->sprite);
	delete(this->texture);
}
