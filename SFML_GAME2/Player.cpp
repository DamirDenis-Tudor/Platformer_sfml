#include "Player.h"

//init 
void Player::setPhisics()
{
	this->frameIndex = 0;

	this->maxTime = 0.3f;
	this->time = maxTime;
	this->reverse = false;

	this->velocity = { 0.f , 0.f };
	this->position = { 8 , 10 };
	this->leftCollision = false;
	this->rightCollision = false;
	this->groundCollision = true;
	this->topCollision = true;
	this->isJumping = true;
	this->bouncingR = false;
	this->bouncingL = false;
	this->bouncingD = false;
	this->maxHeightReached = false;
	this->falling = false;
}

void Player::setTexture()
{
	this->texture = new sf::Texture;
	this->texture->loadFromFile("sprites/caracter.png");
	this->texture->setSmooth(true);

}

void Player::setSprite()
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(*this->texture);
	this->sprite->setPosition(sf::Vector2f(this->position * 60.f));
}

void Player::animation(movement move , bool reverse)
{
	int sign = 0;
	int unit = 0;
	reverse ? sign = -1 , unit = 1 : sign = 1;
	this->time += 0.1f;
	if (this->time > this->maxTime)
	{
		this->time = 0;
		switch (move)
		{
		case IDLE:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndex) * 77 + 45 * unit , 1 * 71 + 3 , sign * 45 , 60 });
			break;
		case WALK:
			this->sprite->setTextureRect(sf::IntRect{ this->frameIndex * 77 + 45 * unit, 4 * 71 + 3 , sign * 45 , 60 });
			break;
		case RUN:
			this->sprite->setTextureRect(sf::IntRect{ this->frameIndex * 77 + 45 * unit , 3 * 71 + 3 , sign * 45 , 60 });
			break;
		case JUMP:
			this->sprite->setTextureRect(sf::IntRect{ this->frameIndex * 77 + 45 * unit , 2 * 71 + 3 , sign * 45 , 60 });
			break;
		case DEAD:
			this->sprite->setTextureRect(sf::IntRect{ this->frameIndex * 77 + 45 * unit , 0 , sign * 75 , 65 });
			break;
		}
		this->frameIndex++;
		if (this->frameIndex >= 15 )
		{
			this->frameIndex = 0;
		}
	}
}

//update & render functions
void Player::update(char **&map)
{
	//animation :: velocity = 0 -> idle animation
	if (this->velocity.x == 0.f && this->velocity.y == 0.f)
		this->animation(IDLE, this->reverse);

	//acceration
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !this->leftCollision)//left
	{
		this->reverse = true;
		this->velocity.x -= 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (!this->isJumping) //when jump and moving left || right  - > jumping animation > run & walk animation
			{
				this->animation(RUN, reverse);
			}

			if (this->bouncingL || this->falling) // when jump -> limit left & right control
			{ 
				if (this->velocity.x < -4.f)
				{
					this->velocity.x = -4.f;
				}
			}
			else
			{
				if (this->velocity.x < -6.f)
				{
					this->velocity.x = -6.f;
				}
			}
		}
		else //walk
		{
			if (!this->isJumping)
			{
				this->animation(WALK, reverse);
			}

			if (this->bouncingL || this->falling)
			{
				if (this->velocity.x < -3.f)
				{
					this->velocity.x = -3.f;
				}
			}
			else
			{
				if (this->velocity.x < -4.f)
				{
					this->velocity.x = -4.f;
				}
			}
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !this->rightCollision)//right
	{
		this->reverse = false;
		this->velocity.x += 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))//run
		{
			if (!this->isJumping)
			{
				this->animation(RUN, reverse);
			}

			if (this->bouncingR || this->falling)
			{
				if (this->velocity.x > 4.f)
				{
					this->velocity.x = 4.f;
				}
			}
			else
			{
				if (this->velocity.x > 6.f)
				{
					this->velocity.x = 6.f;
				}
			}
		}
		else //walk
		{
			if (!this->isJumping) 
			{
				this->animation(WALK, reverse);
			}

			if (this->bouncingR || this->falling)
			{
				if (this->velocity.x > 3.f)
				{
					this->velocity.x = 3.f;
				}
			}
			else
			{
				if (this->velocity.x > 4.f)
				{
					this->velocity.x = 4.f;
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !this->maxHeightReached  && !this->falling && this->groundCollision )//jump
	{
		isJumping = true;
		this->velocity.y -= 2.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) //run jump
		{
			if (this->velocity.y < -12.f)
			{
				this->maxHeightReached = true;
				this->velocity.y = -12.f;
			}
		}
		else//walk jump
		{
			if (this->velocity.y < -10.f)
			{
				this->maxHeightReached = true;
				this->velocity.y = -10.f;
			}
		}
	}
	//jumping animation
	if (this->isJumping || this->falling)
	{
		this->animation(JUMP, this->reverse);
	}

	//decceleration 	
	if (!this->rightCollision && !this->leftCollision)
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
	if (!groundCollision || topCollision || isJumping)
	{
		this->velocity.y += 0.5;
	}

	//nextPos
	sf::Vector2f newPosition;
	newPosition.x = (this->position.x * 60.f + this->velocity.x) / 60.f;
	newPosition.y = (this->position.y * 60.f + this->velocity.y) / 60.f;

	//collision
	/*
		-> made with an error on 0.1
		-> player has 45 width , collision mecanism take it like 60 -> we need to move with 15 pixels right
		->>play with that values
	*/
	this->leftCollision = false;
	this->rightCollision = false;
	if (this->velocity.x <= 0)
	{
		if (map[(int)(this->position.y+0.1)][(int)newPosition.x] != '.' || map[(int)(this->position.y + 0.9)][(int)newPosition.x] != '.' || newPosition.x <= 0)//left
		{
			float leftOffSet = ((int)newPosition.x ) * 60.f;
			newPosition.x = this->position.x;
			std::cout << leftOffSet  << " " << this->sprite->getPosition().x - 75 << "\n";
			if (leftOffSet >= this->sprite->getPosition().x - 75  )
				this->velocity.x = 0.f;

			if (this->isJumping) // when it hit the wall -> player bounce back 
			{
				bouncingL = true;
				this->velocity.x += 0.25f;
			}
			this->leftCollision = true;
			//std::cout << "left\n";
		}
	}
	if(this->velocity.x > 0)
	{
		if (map[(int)(this->position.y+0.1)][(int)(newPosition.x) + 1 ] != '.' || map[(int)(this->position.y + 0.9)][(int)(newPosition.x) + 1] != '.' || newPosition.x + 1 >= mapWidth )//right
		{
			float rightOffSet = ((int)newPosition.x + 1) * 60.f;
			newPosition.x = this->position.x ;
			std::cout << rightOffSet << " " << this->sprite->getPosition().x + 50.f << "\n";
			if(this->sprite->getPosition().x + 50.f >= rightOffSet )
				this->velocity.x = 0.f;
			if (this->isJumping)
			{
				bouncingR = true;
				this->velocity.x -= 0.25f;
			}
			this->rightCollision = true;
			std::cout << "right\n";
		}
	}
	if (this->velocity.y >= 0)
	{
		if (map[(int)(newPosition.y + 1)][(int)(newPosition.x + 0.1)] != '.' || map[(int)(newPosition.y + 1)][(int)(newPosition.x + 0.9)] != '.')//bottom
		{
			newPosition.y = this->position.y ;
			this->velocity.y = 0;
			if (this->isJumping)
			{
				this->bouncingD = true;
				this->velocity.y -= 0.5f;
			}
			this->isJumping = false;

			this->groundCollision = true;
			
			this->maxHeightReached = false;

			this->bouncingR = false;
			this->bouncingL = false;

			this->falling = false;

			//std::cout << "ground\n";
		}
		else
		{
			this->falling = true;
		}
	}
	else if(this->velocity.y < 0)
	{
		if (map[(int)newPosition.y][(int)(newPosition.x+0.1)] != '.' || map[(int)(newPosition.y)][(int)(newPosition.x + 0.9)] != '.')//top
		{
			newPosition.y = this->position.y;
			this->velocity.y = 0;
			this->isJumping = false;
			this->falling = true;
			this->topCollision = true;
			this->groundCollision = false;
			//std::cout << "top\n";
		}
	}
	
	//reactualize newPos
	if (this->isJumping || this->bouncingD) //velocity modifies in these cases -> new position recalculation
	{
		newPosition.x = (this->position.x * 60.f + this->velocity.x) / 60.f;
		newPosition.y = (this->position.y * 60.f + this->velocity.y) / 60.f;
	}
	this->bouncingD = false;

	//update position
	this->position = newPosition;

	//move
	this->sprite->move(this->velocity);

	//std::cout << newPosition.x << " " << newPosition.y << "\n";
	//std::cout << "jump : " << this->velocity.y << "\n";
}


void Player::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);
}

//contructor & destructor
Player::Player()
{
	this->setPhisics();
	this->setTexture();
	this->setSprite();
}

Player::~Player()
{
	delete(this->sprite);
	delete(this->texture);
}
