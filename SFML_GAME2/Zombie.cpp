#include "Zombie.h"

//init 
void Zombie::setPhisics()
{
	this->frameIndexIdle = 0;
	this->frameIndexWalk = 0;
	this->frameIndexAttack = 0;
	this->frameIndexDead = 0;
	this->maxTime = 0.7f;
	this->time = maxTime;
	this->reverse = false;
	this->direction = { 1.f , 0.f };
	this->velocity = { 0.f , 0.f };
	this->leftCollision = false;
	this->rightCollision = false;
	this->groundCollision = true;
	this->falling = false;
}

void Zombie::setTexture(bool type)
{
	this->texture = new sf::Texture;
	if (type == 0)
	{
		this->texture->loadFromFile("sprites/zombieMale.png");
	}
	else
	{
		this->texture->loadFromFile("sprites/caracter.png");
	}
	this->texture->setSmooth(true);

}

void Zombie::setSprite(sf::Vector2f position)
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(*this->texture);
	this->position = position;
	this->sprite->setPosition(sf::Vector2f(this->position * 60.f));
}

void Zombie::animation(movementZombie move, bool reverse)
{
	int sign = 0;
	int unit = 0;
	reverse ? sign = -1, unit = 1 : sign = 1;
	this->time += 0.1f;
	if (this->time > this->maxTime)
	{
		this->time = 0;
		switch (move)
		{
		case IDLEZ:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexIdle) * 50 , 120 , 50 , 60 });
			this->frameIndexIdle++;
			if (this->frameIndexIdle >= 15)
			{
				this->frameIndexIdle = 0;
			}
			break;
		case WALKZ:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexWalk + unit) * 50 , 180 , sign * 50 , 60 });
			this->frameIndexWalk++;
			if (this->frameIndexWalk > 9)
			{
				this->frameIndexWalk = 0;
			}

			break;
		case ATTACKZ:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexAttack + unit) * 50 , 0 , sign * 50 , 60 });
			this->frameIndexAttack++;
			if (this->frameIndexAttack > 6)
			{
				this->frameIndexAttack = 0;
			}
			break;
		case DEADZ:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexDead +unit)* 72 , 60 , sign * 72 , 60 });
			this->frameIndexDead++;
			if (this->frameIndexDead > 10)
			{
				this->frameIndexDead = 0;
			}
			break;
		}

	}
}

//update and render
void Zombie::update(char**& map)
{
	this->animation(DEADZ, reverse);
	
	//acceleration
	if ( this->direction.x < 0) //left
	{
		this->reverse = true;
		this->velocity.x -= 0.5f;
		if (this->velocity.x < -1.5f)
		{
			this->velocity.x = -1.5f;
		}
	}
	else if(this->direction.x > 0)
	{
		this->reverse = false;
		this->velocity.x += 0.5f;
		if (this->velocity.x > 1.5f)
		{
			this->velocity.x = 1.5f;
		}
	}

	//decceleration
	if (this->groundCollision)
	{
		if (this->velocity.x < 0)
		{
			this->velocity.x += 0.25f;
			if (this->velocity.x > 0)
			{
				this->velocity.x = 0.f;
			}
		}
		else
		{
			this->velocity.x -= 0.25f;
			if (this->velocity.x < 0)
			{
				this->velocity.x = 0.f;
			}
		}
	}

	//gravity
	if ( this->falling)
	{
		this->velocity.y += 0.5;
	}

	//collision
	sf::Vector2f newPosition;
	newPosition.x = (this->position.x * 60.f + this->velocity.x ) / 60.f;
	newPosition.y = (this->position.y * 60.f + this->velocity.y) / 60.f;

	this->leftCollision = false;
	this->rightCollision = false;
	if (this->velocity.x < 0)
	{
		if (map[(int)(this->position.y + 0.1)][(int)newPosition.x] != '.' || map[(int)(this->position.y + 0.9)][(int)newPosition.x] != '.' || newPosition.x <= 0)//left
		{
			newPosition.x = this->position.x;
			this->leftCollision = true;
			this->velocity.x = 0.f;
			//std::cout << "left\n";
		}
	}
	if (this->velocity.x > 0)
	{
		if (map[(int)(this->position.y + 0.1)][(int)(newPosition.x) + 1] != '.' || map[(int)(this->position.y + 0.9)][(int)(newPosition.x) + 1] != '.' || newPosition.x + 1 >= mapWidth)//right
		{
			newPosition.x = this->position.x;
			this->velocity.x = 0.f;
			this->rightCollision = true;
			
			//std::cout << "right\n";
		}
	}

	bool border = false;
	groundCollision = false;
	if (this->velocity.y >= 0)
	{
		if (map[(int)(newPosition.y + 1)][(int)(newPosition.x + 0.f)] != '.' || map[(int)(newPosition.y + 1)][(int)(newPosition.x + 0.9)] != '.')//bottom
		{
			newPosition.y = this->position.y;
			this->velocity.y = 0;
			this->falling = false;
			this->groundCollision = true;
			//std::cout << "ground\n";
		}
		else
		{
			this->falling = true;
			border = true;
		}
	}
	
	if (map[(int)(newPosition.y + 1)][(int)(newPosition.x)] == '.' && this->direction.x == -1.f)
	{
		this->leftCollision = true;
		this->velocity.x += 0.5f;
	}
	else if (map[(int)(newPosition.y + 1)][(int)(newPosition.x + 0.9)] == '.' && this->direction.x == 1.f)
	{
		this->rightCollision = true;
		this->velocity.x -= 0.5f;
	}

	if (this->rightCollision )
	{
		this->direction.x = -1.f;
	}
	else if (this->leftCollision )
	{
		this->direction.x = 1.f;
	}


	//update
	this->position = newPosition;

	//move
	this->sprite->move(this->velocity);
	
}

void Zombie::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);
}

//contructor & destructor
Zombie::Zombie(sf::Vector2f position, bool type)
{
	this->setPhisics();
	this->setTexture(type);
	this->setSprite(position);
}

Zombie::~Zombie()
{
	delete(this->sprite);
	delete(this->texture);
}
