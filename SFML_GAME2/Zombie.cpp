#include <iostream>
#include<SFML/Graphics.hpp>

#include "Zombie.h"

//init 
void Zombie::setPhisics()
{
	this->position = spawnPosition;
	this->frameIndexIdle = 0;
	this->frameIndexWalk = 0;
	this->frameIndexAttack = 0;
	this->frameIndexDead = 0;

	this->deadStatus = false;
	this->dead = false;
	
	this->maxTime = 0.1f;
	this->time = maxTime;
	bool randZ = rand()%2;
	if (randZ)
	{
		this->direction.x = 1.f;
		this->reverse = false;
	}
	else
	{
		this->direction.x = -1.f;
		this->reverse = true;
	}
	this->direction.y = 0;
	this->velocity = { 0.f , 0.f };
	this->leftCollision = false;
	this->rightCollision = false;
	this->groundCollision = true;
	this->falling = false;
	this->wasFalling = false;

	this->zombieBoxCol = false;

	this->waiting = false;
	this->blocked = false;

	this->leftBoxCollision = false;
	this->rightBoxCollision = false;

	this->freeze = false;
	this->attackFinish = true;
	this->prevFreezeStatus = true;
}

void Zombie::setTexture(bool type)
{
	this->type = type;
	this->texture = new sf::Texture;
	if (type == 0)
	{
		this->texture->loadFromFile("sprites/Zombies/zombieMale1.png");
	}
	else
	{
		this->texture->loadFromFile("sprites/Zombies/zombieFemale1.png");
	}
	this->texture->setSmooth(true);

}

void Zombie::setSprite(sf::Vector2f position)
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(*this->texture);
	this->position = position;
	this->spawnPosition = position;
	this->sprite->setPosition(sf::Vector2f(this->position * 60.f));
}

void Zombie::animation(movementZombie move, bool reverse, float deltaTime)
{
	int sign = 0;
	int unit = 0;

	reverse ? sign = -1, unit = 1 : sign = 1;

	this->time += deltaTime;
	if (this->time > this->maxTime)
	{
		this->time = 0;
		switch (move)
		{
		case IDLEZ:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexIdle + unit) * (50 + 4 * this->type) , 120 + 60 + 5*type, sign * (50 + type*4) , 60 });
			this->frameIndexIdle++;
			this->frameIndexAttack = 0;
			if (this->frameIndexIdle >= 15)
			{
				this->frameIndexIdle = 0;
				this->freeze = false;
			}

			break;
		case WALKZ:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexWalk + unit) * (50  + 4 * this->type), 180 + 60 + 5 * type, sign * (50 + type * 4) , 60 });
			this->frameIndexWalk++;
			this->frameIndexAttack = 0;
			if (this->frameIndexWalk > 9)
			{
				this->frameIndexWalk = 0;
			}

			break;
		case ATTACKZ:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexAttack + unit) *( 50 + 4 * this->type), 60 + 5 * type, sign * (50 + type*4) , 60 });
			this->frameIndexAttack++;
			this->frameIndexDead = 0;
			if (this->frameIndexAttack > 6)
			{
				this->freeze = true;
				this->attackFinish = true;
				this->frameIndexAttack = 0;
			}
			break;
		case DEADZ://65 zombie girl
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexDead + unit) * 72  , 0 , sign * 72  , 65 });
			this->frameIndexDead++;
			this->frameIndexAttack = 0;
			if (this->frameIndexDead >= 11) // set > for disapear
			{
				this->dead = true;
				this->frameIndexDead = 0;
			}
			break;
		}

	}
}

//get
sf::Vector2f Zombie::getPosition()
{
	return this->position;
}

bool Zombie::getFreezeStatus()
{
	return this->freeze;
}

int Zombie::getAttackIndex()
{
	return this->frameIndexAttack;
}

bool Zombie::getWaitingStatus()
{
	return this->waiting;
}

bool Zombie::getGroundStatus()
{
	return this->groundCollision;
}

sf::Vector2f Zombie::getVelocity()
{
	return this->velocity;
}

bool Zombie::getFallingStatus()
{
	return this->falling;
}

bool Zombie::getBlockedStatus()
{
	return this->blocked;
}

bool Zombie::getDeadStatus()
{
	return this->deadStatus;
}

sf::Vector2f Zombie::getSpawnPosition()
{
	return this->spawnPosition;
}

//set
void Zombie::setVelocityHorizontally(float velocity)
{
	this->velocity.x = velocity;
}

void Zombie::setDeadStatus(bool val)
{
	this->deadStatus = val;
}

void Zombie::setWaitingStatus(bool val)
{
	this->waiting = val;
}

//restart
void Zombie::restart()
{
	this->setPhisics();
	this->sprite->setPosition(this->spawnPosition * 60.f);
}

//update and render
bool Zombie::update(int**& map , sf::Vector2f playerPosition , bool playerAtack , bool groundStatus ,bool shieldStatus, float deltaTime)
{		
	//waiting
	if (!this->deadStatus)
	{
		if (((playerPosition.y - 0.4 <= this->position.y + 1 && playerPosition.y + 0.4 >= this->position.y) && (this->leftCollision || this->rightCollision || this->leftBoxCollision || this->rightBoxCollision)) 
			&& !this->deadStatus && ((playerPosition.x < this->position.x && !this->rightCollision) || (playerPosition.x > this->position.x && !this->leftCollision)) )
		{
			this->waiting = true;
		}
		else
		{
			this->waiting = false;
		}

		//blocked situations
		if ((map[(int)this->position.y][(int)this->position.x + 1] != 0 || map[(int)(this->position.y + 0.9)][(int)this->position.x + 1] != 0) && (this->rightBoxCollision) ||
			(map[(int)this->position.y][(int)(this->position.x + 0.1)] != 0 || map[(int)(this->position.y + 0.9)][(int)(this->position.x + 0.1)] != 0) && (this->leftBoxCollision)
			)
		{
			this->blocked = true;
		}
		else
		{
			this->blocked = false;
		}
	}
	else
	{
		this->blocked = false;
		this->waiting = false;
	}

	//box push movemwnt
	if (this->zombieBoxCol && !this->deadStatus && !this->blocked)
	{
		this->position.x = (this->position.x * 60.f + this->velocity.x) / 60.f;
		this->position.y = (this->position.y * 60.f + this->velocity.y) / 60.f;
		this->sprite->move(this->velocity);
	}

	//follow player
	if ( !this->leftBoxCollision && !this->rightBoxCollision && !this->leftCollision  && !this->rightCollision && !this->waiting) //change waiting
	{
		if (playerPosition.x - this->position.x > 0 && this->direction.x < 0 && (unsigned)playerPosition.y == (unsigned int)this->position.y)
		{
			this->direction.x = 1.f;
		}

		if (playerPosition.x - this->position.x < 0 && this->direction.x > 0 && (unsigned)playerPosition.y == (unsigned int)this->position.y)
		{
			this->direction.x = -1.f;
		}
	}

	//attack
	if (this->deadStatus && !dead)
	{
		this->animation(DEADZ, reverse, deltaTime);
	}

	//attack animation until finish
	if (!this->attackFinish && !this->deadStatus)
	{
		this->animation(ATTACKZ, reverse, deltaTime);
	}

	//
	if ((freeze && !this->deadStatus) || this->waiting || (this->blocked && !waiting))
	{
		this->animation(IDLEZ, reverse, deltaTime);
	}

	//player contact
	if (abs(playerPosition.x - this->position.x) < 0.7f && groundStatus && (unsigned)playerPosition.y == (unsigned int)this->position.y && !this->falling)
	{
		this->velocity.x = 0;
		if (playerAtack)
		{
			this->deadStatus = true;
			if (this->frameIndexDead == 0)
			{
				this->animation(DEADZ, reverse, deltaTime);
			}
			return false;
		}
		else if ( !this->deadStatus && !freeze  )
		{
			if (this->frameIndexAttack == 0)
			{
				this->attackFinish = false;
			}
			this->animation(ATTACKZ, reverse, deltaTime);
			if (this->frameIndexAttack >= 2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	 //normal movemnt
	if (!deadStatus && !this->freeze && this->attackFinish && !this->blocked )
	{
		if (!this->waiting && (!this->falling || this->bottomBoxCollision) )
		{
			if (this->direction.x == 0 || (this->falling && !this->bottomBoxCollision))
				this->animation(IDLEZ, reverse, deltaTime);
			else
				this->animation(WALKZ, reverse, deltaTime);



			//acceleration
			if (this->direction.x < 0) //left
			{
				this->reverse = true;
				this->velocity.x -= (40.f * deltaTime);
				if (this->velocity.x < -120.f * deltaTime)
				{
					this->velocity.x = -120.f * deltaTime;
				}
			}
			else if (this->direction.x > 0)
			{
				this->reverse = false;
				this->velocity.x += (40.f * deltaTime);
				if (this->velocity.x > 120.f * deltaTime)
				{
					this->velocity.x = 120.f * deltaTime;
				}
			}

		}

		//deccleration
		if (this->velocity.x < 0)
		{
			this->velocity.x += (20.f * deltaTime);
			if (this->velocity.x > 0)
			{
				this->velocity.x = 0.f;
			}
		}
		else
		{
			this->velocity.x -= (20.f * deltaTime);
			if (this->velocity.x < 0)
			{
				this->velocity.x = 0.f;
			}
		}

		//gravity
		if (this->falling)
		{
			this->velocity.y += 10 * deltaTime;
			this->velocity.x = 0;
		}

		if (this->groundCollision && this->wasFalling)
		{
			direction.x = 1.f;
			this->leftBoxCollision = false;
			this->rightBoxCollision = false;
			this->rightCollision = false;
			this->leftCollision = false;
			this->position.y = int(position.y);
			this->sprite->setPosition(this->position * 60.f);//reposition after falling
		}

		if (!falling)
		{
			this->wasFalling = false;
		}

		//collisions
		sf::Vector2f newPosition;
		newPosition.x = (this->position.x * 60.f + this->velocity.x) / 60.f;
		newPosition.y = (this->position.y * 60.f + this->velocity.y) / 60.f;

		if ((map[(int)(newPosition.y + 1)][(int)(newPosition.x + 0.1 )] != 0 || map[(int)(newPosition.y + 1)][(int)(newPosition.x + 0.8)] != 0) || (this->bottomBoxCollision) )//bottom
		{
			this->velocity.y = 0;
			this->groundCollision = true;
			this->falling = false;
		}
		else 
		{
			this->groundCollision = false;
			this->bottomBoxCollision = false;
			this->falling = true;
			this->leftBoxCollision = false;
			this->rightBoxCollision = false;
			this->waiting = false;
			this->wasFalling = true;
			this->velocity.x = 0;
		}

		if (!this->waiting && !falling)
		{
			this->leftCollision = false;
			this->rightCollision = false;

			if (this->velocity.x > 0)
			{
				if (map[(int)(newPosition.y + 0.1)][(int)(newPosition.x + 0.90)] != 0 || map[(int)(newPosition.y + 0.9)][(int)(newPosition.x + 0.90)] != 0 || newPosition.x + 1 >= mapWidth)//right
				{
					newPosition.x = this->position.x;
					this->rightCollision = true;
				}
			}
			if (this->velocity.x < 0)
			{
				if (map[(int)(newPosition.y + 0.1)][(int)(newPosition.x + 0.1)] != 0 || map[(int)(newPosition.y + 0.9)][(int)(newPosition.x + 0.1)] != 0 || newPosition.x <= 0)//left
				{
					newPosition.x = this->position.x;
					this->leftCollision = true;
				}
			}
			//bottom borders colisions
			if (!this->bottomBoxCollision)
			{
				if (map[(int)(newPosition.y + 1)][(int)(newPosition.x)] == 0 && this->direction.x == -1.f)
				{
					this->leftCollision = true;
				}
				else if (map[(int)(newPosition.y + 1)][(int)(newPosition.x + 0.9)] == 0 && this->direction.x == 1.f)
				{
					this->rightCollision = true;
				}
			}
			if (this->rightCollision)
			{
				this->velocity.x = 0;
				newPosition.x = this->position.x;
				if (falling)
				{
					newPosition.x = position.x;
				}
				else
				{
					this->direction.x = -1.f;
				}
			}
			else if (this->leftCollision)
			{
				newPosition.x = this->position.x;
				this->velocity.x = 0;
				if (falling)
				{
					newPosition.x = position.x;
				}
				else
				{
					this->direction.x = 1.f;
				}
			}
		}

	 if ( !this->waiting  || this->falling ) // this condition is requaired beacause the movement  can be made by boxes
		{
			this->position = newPosition;
			this->sprite->move(this->velocity);
		}
	}

	return false;
}

void Zombie::updateTrapCollision(int**& objects)
{
	if (objects[(int)(position.y + 0.4 )][(int)(position.x + 0.3)] == water || objects[(int)(position.y + 0.4)][(int)(position.x + 0.8)] == water)
	{
		this->deadStatus = true;
	}

	if (objects[(int)(position.y )][(int)(position.x+ 0.3)] == damegeBush || objects[(int)(position.y )][(int)(position.x + 0.8)] == damegeBush )
	{
		this->deadStatus = true;
	}

	if (objects[(int)(position.y)][(int)(position.x + 0.3)] == spikes || objects[(int)(position.y)][(int)(position.x + 0.8)] == spikes)
	{
		this->deadStatus = true;
	}
}

void Zombie::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);
}

//contructor & destructor
Zombie::Zombie(sf::Vector2f position, bool type)
{
	this->spawnPosition = position;
	this->setPhisics();
	this->setTexture(type);
	this->setSprite(position);
}

Zombie::~Zombie()
{
	delete(this->sprite);
	delete(this->texture);
}
