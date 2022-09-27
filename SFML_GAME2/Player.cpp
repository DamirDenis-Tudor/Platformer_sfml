#include "Player.h"

//init 

void Player::initFont()
{
	this->font = new sf::Font;
	this->font->loadFromFile("menu/EvilEmpire-4BBVK.ttf");
}

void Player::initCapabilities()
{
	this->maxTime = 0.06f;
	this->time = maxTime;
	this->jumpHeight = 180.f;

}

void Player::initInfo()
{
	this->coins = 90;
	this->diamonts = 90;
	this->lives = 2;
	this->shields = 0;
	this->abilities = 2;
}

void Player::initText()
{
	this->text = new sf::Text;
	this->text->setFont(*this->font);
	this->text->setFillColor({ 255 , 255 ,255 , 200 });
	this->text->setLetterSpacing(1.f);
	this->text->setOutlineThickness(1.f);
}

void Player::setPhisics()
{
	this->frameIndex = 0;
	this->frameIndexJumping = 0;
	this->frameIndexDead = 0;
	this->frameIndexAttack = 0;
	this->frameIndexJumpAttack = 0;

	this->position = spawnPosition;

	this->reverse = false;

	this->velocity = { 0.f , 0.f };
	this->currentGroungHeight = 0.f;

	this->rightBoxCol = false;
	this->leftBoxCol = false;
	this->topBoxColision = false;
	this->bottomBoxCollision = false;

	this->leftCollision = false;
	this->rightCollision = false;
	this->groundCollision = true;
	this->topCollision = true;

	this->topBoxColision = false;

	this->isJumping = true;

	this->maxHeightReached = false;
	this->falling = false;

	this->deadStatus = false;
	this->shieldBreakStatus = false;
}

void Player::setTexture()
{
	this->texture = new sf::Texture;
	this->texture->loadFromFile("sprites/spriteSheets/knightCaracter.png");

	this->infoTexture = new sf::Texture;
	this->infoTexture->loadFromFile("sprites/spriteSheets/playerInfo.png");
	this->texture->setSmooth(true);
}

void Player::setSprite()
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(*this->texture);
	this->sprite->setPosition(sf::Vector2f(this->position * 60.f));

	this->infoSprite = new sf::Sprite;
	this ->infoSprite->setTexture(*this->infoTexture);

	this->infoSprite->setColor({ 255 , 255 , 255 ,  200 });
}


//animation
void Player::animation(movement move , bool reverse , float deltaTime)
{
	int sign = 0;
	int unit = 0;
	reverse ? sign = -1 , unit = 1 : sign = 1;
	this->time += deltaTime;
	if (this->time > this->maxTime)
	{
		this->time = 0;
		switch (move)
		{
		case IDLE:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndex) * 50 + 50 * unit , 60 * 1 , sign * 50 , 60 });
			this->frameIndexJumping = 0;
			this->frameIndex++;
			this->frameIndexDead = 0;
			if (this->frameIndex >= 10)
			{
				this->frameIndex = 0;
			}
			break;
		case WALK:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndex) * 50 + 50 * unit , 60 * 5 , sign * 50 , 60 });
			this->frameIndexJumping = 0;
			this->frameIndex++;
			this->frameIndexDead = 0;
			if (this->frameIndex >= 10)
			{
				this->frameIndex = 0;
			}
			break;
		case RUN:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndex) * 50 + 50 * unit , 60 * 4 , sign * 50 , 60 });
			this->frameIndexJumping = 0;
			this->frameIndex++;
			this->frameIndexDead = 0;
			if (this->frameIndex >= 10)
			{
				this->frameIndex = 0;
			}
			break;
		case ATTACK:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexAttack) * 50 + 50 * unit , 60 * 0 , sign * 50 , 60 });
			this->frameIndexJumping = 0;
			this->frameIndexDead = 0;
			this->frameIndexAttack++;
			if (this->frameIndexAttack >= 9)
			{
				this->frameIndexAttack = 0;
				if (this->abilities != 0)
				{
					this->abilities--;
				}
			}
			break;
		case JUMP:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexJumping) * 50 + 50 * unit , 60 * 2 , sign * 50 , 60 });
			this->frameIndexJumping++;
			this->frameIndexDead = 0;
			if (this->frameIndexJumping >= 9)
			{
				this->frameIndexJumping = 0;
			}
			break;
		case JUMPATTACK:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexJumping) * 50 + 50 * unit , 60 * 3 , sign * 50 , 60 });
			this->frameIndexJumping++;
			this->frameIndexDead = 0;
			if (this->frameIndexJumpAttack >= 10)
			{
				this->frameIndexJumpAttack = 0;
			}
			break;
		case DEAD:
			this->sprite->setTextureRect(sf::IntRect{ (this->frameIndexDead) * 75 + 75 * unit , 60 * 6 , sign * 75 , 60 });
			this->frameIndexJumping = 0;
			if (this->frameIndexDead >= 10)
			{
				this->frameIndexDead = 0;
			}
			this->frameIndexDead++;
			break;
		}

	}
}

//respawn
void Player::respawn()
{
	this->setPhisics();
	this->sprite->setPosition(this->spawnPosition * 60.f);
}
//restart
void Player::restart()
{
	this->respawn();
	this->initInfo();
}

//function for colision
sf::Vector2f Player::getPos()
{
	/*
		-> function for collizion detection with enemy
	*/
	sf::Vector2f possition = { (this->sprite->getPosition().x / 60), ( (this->sprite->getPosition().y + 30) / 60) }; //middle
	return possition;
}

//function
sf::Vector2i Player::getMapPosition()
{
	/*
		->function for view position
	*/
	sf::Vector2i position;
	position.x = ((int)this->sprite->getPosition().x  ) / 60;
	position.y = ((int)this->sprite->getPosition().y  ) / 60;

	return position;
}

//zombie detection mecanism
unsigned int Player::getGroundStatus()
{
	return this->groundCollision;
}

sf::Vector2f Player::getVelocity()
{
	return this->velocity;
}

bool Player::getAttackStatus()
{
	return (this->frameIndexAttack > 0 && this->abilities > 0) ? true : false;
}

bool Player::getShieldStatus()
{
	return this->shields == 0 ? false : true;
}

void Player::decShieds()
{
	this->shields--;
}

//set
void Player::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Player::leftBoxColision()
{
	this->velocity.x = 0;
	this->leftBoxCol = true;
}

void Player::rightBoxColision()
{
	this->velocity.x = 0;
	this->rightBoxCol = true;
	
}

//update & render functions
void Player::updateMovement(int **&map , float deltaTime)
{
	//std::cout << "player : " << leftBoxCol << "\n\n";
	if (this->deadStatus)
	{
		{
			if (this->lives != 0)
			{
				this->animation(DEAD, this->reverse, deltaTime);
			}
			if (this->frameIndexDead == 10)
			{
				if (this->lives != 0)
				{
					this->lives--;
				}

				if (this->lives != 0)
				{
					this->respawn();
				}
			}
		}
	}
	else
	{
		if (this->velocity.x == 0.f && this->velocity.y == 0.f && this->frameIndexAttack == 0)
		{
			this->animation(IDLE, this->reverse,deltaTime);
		}

		//attack
		if (this->frameIndexAttack == 0)
		{
			if (this->abilities > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			{
				this->animation(ATTACK, reverse, deltaTime);
			}
		}
		else
		{
			this->animation(ATTACK, reverse, deltaTime);
		}

		//acceration
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !leftBoxCol )//left
		{
			this->reverse = true;
			this->velocity.x -= (80.f * deltaTime);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				if (!this->isJumping && !this->falling && !this->leftCollision && this->frameIndexAttack == 0) //when jump and moving left || right  - > jumping animation > run & walk animation
				{
					this->animation(RUN, reverse , deltaTime);
				}

				if (this->falling) // when jump -> limit left & right control
				{
					if (this->velocity.x < -320.f * deltaTime)
					{
						this->velocity.x = -320.f * deltaTime;
					}
				}
				else
				{
					if (this->velocity.x < -480.f * deltaTime)
					{
						this->velocity.x = -480.f * deltaTime;
					}
				}
			}
			else //walk
			{
				if (!this->isJumping && !this->falling && !this->leftCollision && this->frameIndexAttack == 0 )
				{
					this->animation(WALK, reverse , deltaTime);
				}

				if (this->falling)
				{
					if (this->velocity.x < -240.f * deltaTime)
					{
						this->velocity.x = -240.f * deltaTime;
					}
				}
				else
				{
					if (this->velocity.x < -320.f * deltaTime)
					{
						this->velocity.x = -320.f * deltaTime;
					}
				}
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !rightBoxCol )//right
		{
			this->reverse = false;
			this->velocity.x += (80.f * deltaTime);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))//run
			{
				if (!this->isJumping && !this->falling && !this->rightCollision && this->frameIndexAttack == 0)
				{
					this->animation(RUN, reverse , deltaTime);
				}

				if (this->falling)
				{
					if (this->velocity.x > 320.f * deltaTime)
					{
						this->velocity.x = (320.f * deltaTime);
					}
				}
				else
				{
					if (this->velocity.x > (480.f * deltaTime) )
					{
						this->velocity.x = 480.f * deltaTime;
					}
				}
			}
			else //walk
			{
				if (!this->isJumping && !this->falling && !this->rightCollision && this->frameIndexAttack == 0)
				{
					this->animation(WALK, reverse , deltaTime);
				}

				if ( this->falling)
				{
					if (this->velocity.x > 240.f * deltaTime)
					{
						this->velocity.x = 240.f * deltaTime;
					}
				}
				else
				{
					if (this->velocity.x > 320.f * deltaTime)
					{
						this->velocity.x = 320.f * deltaTime;
					}
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !this->maxHeightReached && !this->falling )//jump
		{
			isJumping = true;
			groundCollision = false;
			this->velocity.y -= (120.f * deltaTime);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) //run jump
			{
				if (this->velocity.y < -600.f * deltaTime) //make calculus and see why
				{
					this->velocity.y = -600.f * deltaTime;
				}
				if (this->currentGroungHeight - (this->getMapPosition().y) * 60.f >= this->jumpHeight)
				{
					this->velocity.y = 0;
					this->maxHeightReached = true;
					this->falling = true;
				}
			}
			else//walk jump
			{
				if (this->velocity.y < -480.f * deltaTime )
				{
					this->velocity.y = -480.f * deltaTime;
				}
				if (this->currentGroungHeight - (this->getMapPosition().y) *60.f >= this->jumpHeight *2/3)
				{
					this->velocity.y = 0;
					this->maxHeightReached = true;
					this->falling = true;
				}
			}
		}

		if ((int)this->currentGroungHeight - (this->getMapPosition().y) * 60.f >= this->jumpHeight )
		{
			this->velocity.y = 0;
			this->maxHeightReached = true;
			this->falling = true;
		}

		//jumping animation
		if ( (this->isJumping || this->falling) && !this->topBoxColision )
		{
			this->animation(JUMP, this->reverse , deltaTime);
		}

		//decceleration 	
		if (!this->rightCollision && !this->leftCollision)
		{
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
		}

		if (this->velocity.x > 0)
		{
			this->leftBoxCol = false;
		}
		else if(this->velocity.x < 0)
		{
			this->rightBoxCol = false;
		}

		if (this->velocity.y>0)
		{
			this->bottomBoxCollision = false;
		}

		//gravity

		this->velocity.y += (20.f * deltaTime );

		//nextPos
		sf::Vector2f newPosition;
		newPosition.x = (this->position.x * 60.f + this->velocity.x ) / 60.f;
		newPosition.y = (this->position.y * 60.f + this->velocity.y ) / 60.f;

		/*
			coliision
		*/
		this->leftCollision = false;
		this->rightCollision = false;
		if (this->velocity.x <= 0)
		{
			if (map[(int)(this->position.y + 0.1)][(int)(newPosition.x + 0.1)] != 0 || map[(int)(this->position.y + 0.9)][(int)(newPosition.x + 0.1)] != 0 || newPosition.x <= 0 || this->leftBoxCol)//left
			{
				float leftOffSet = ((int)newPosition.x) * 60.f;
				newPosition.x = this->position.x;
				if (leftOffSet >= this->sprite->getPosition().x - 75)
					this->velocity.x = 0.f;

				this->leftCollision = true;
			}
		}
		else if (this->velocity.x > 0)
		{
			if (map[(int)(this->position.y + 0.1 )][(int)(newPosition.x + 0.9)] != 0 || map[(int)(this->position.y + 0.9)][(int)(newPosition.x + 0.9)] != 0 || newPosition.x >= mapWidth || this->rightBoxCol)//right
			{
				float rightOffSet = ((int)newPosition.x + 1) * 60.f;
				newPosition.x = this->position.x;
				//
				if (this->sprite->getPosition().x + 50.f >= rightOffSet)
					this->velocity.x = 0.f;

				this->rightCollision = true;
			}
		}
		if (this->velocity.y >= 0)
		{
			if (map[(int)(newPosition.y + 1.01) ][(int)(newPosition.x + 0.35)] != 0 || map[(int)(newPosition.y +1.01) ][(int)(newPosition.x + 0.65)] != 0 || ( int(newPosition.y) == mapHeight-2 ) || this->topBoxColision )//bottom
			{
				newPosition.y = this->position.y;
				this->groundCollision = true;
				this->currentGroungHeight = this->getMapPosition().y * 60;
			}
			else
			{
				this->groundCollision = false;
				this->bottomBoxCollision = false;
				this->falling = true;
			}
		}
		else if (this->velocity.y < 0)
		{
			if ( map[(int)(newPosition.y + 0.1)][(int)(newPosition.x + 0.35)] != 0 || map[(int)(newPosition.y + 0.1)][(int)(newPosition.x + 0.65)] != 0 ||  newPosition.y  <= 0 )//top
			{
				newPosition.y = this->position.y;
				this->velocity.y = 0;
				this->isJumping = false;
				this->falling = true;
				this->topCollision = true;
				this->groundCollision = false;
			}
		}
		//ground col
		if (this->groundCollision)
		{
			this->currentGroungHeight = this->getMapPosition().y * 60;
			this->velocity.y = 0;
			this->isJumping = false;
			this->maxHeightReached = false;
			this->falling = false;
		}

		if (this->bottomBoxCollision)
		{
			this->falling = true;
			this->groundCollision = false;
			this->velocity.y = 1.f;
		}
		//reactualize newPos
		if (this->isJumping || this->bottomBoxCollision ) //velocity modifies in these cases -> new position recalculation
		{
			newPosition.x = (this->position.x * 60.f + this->velocity.x) / 60.f;
			newPosition.y = (this->position.y * 60.f + this->velocity.y) / 60.f;
		}

		//update position
		this->position = newPosition;


		if (this->topBoxColision)
		{
			this->currentGroungHeight = this->getMapPosition().y * 60 - 60;
		}

		//move
		this->sprite->move(this->velocity);

	}
}

void Player::updateInfo(int**&objects)
{
	//coin colision -> is made wth the middle of player
	if (objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5 )] == coin)
	{
		objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] = 0 ;
		this->coins++;
	}

	if (objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] == diamond)
	{
		objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] = 0;
		this->diamonts++;
	}

	if (objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] == health && this->lives != max )
	{
		objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] = 0;
		this->lives++;
	}

	if (objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] == shield && this->shields != max)
	{
		objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] = 0;
		this->shields++;
	}

	if (objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] == attackAbility && this->abilities != max)
	{
		objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] = 0;
		this->abilities++;
	}

}

void Player::updateObjectsCollision(int**& objects)
{
	if (objects[(int)(this->position.y + 0.05)][(int)(this->position.x + 0.5)] == damegeBush && !this->getShieldStatus())
	{
		deadStatus = true;
	}

	if (objects[(int)(this->position.y + 0.05)][(int)(this->position.x + 0.5)] == spikes && !this->deadStatus)
	{
		deadStatus = true;
		if (this->shields > 0)
		{
			this->shields--;
		}
	}

	if ( objects[(int)(this->position.y + 0.5)][(int)(this->position.x + 0.5)] == water )
	{
		deadStatus = true;
	}
}

void Player::renderPlayer(sf::RenderTarget* target )
{
	target->draw(*this->sprite);
}

void Player::renderPlayerInfo(sf::RenderTarget* target, sf::Vector2f viewPos)
{

	//health
	this->infoSprite->setTextureRect({ 0 , 295  , 253 , 60 });
	this->infoSprite->setPosition(viewPos.x - 960, viewPos.y - 540);
	target->draw(*this->infoSprite);

	this->infoSprite->setTextureRect({ 0 , 241  , 167 * this->lives / 4 , 27 }); // here procent multplier per width 
	this->infoSprite->setPosition(viewPos.x - 960 + 65, viewPos.y - 540 + (60 - 27) / 2);
	target->draw(*this->infoSprite);

	//shield
	this->infoSprite->setTextureRect({ 0 , 181  , 253 , 60 });
	this->infoSprite->setPosition(viewPos.x - 960 + 253, viewPos.y - 540 + 60);
	this->infoSprite->setScale(-1, 1);
	target->draw(*this->infoSprite);

	this->infoSprite->setScale(1, 1);

	this->infoSprite->setTextureRect({ 0 , 154  , 167 * this->shields / 4 , 27 }); // here procent multplier per width 
	this->infoSprite->setPosition(viewPos.x - 960 + 65, viewPos.y - 540 + (60 - 27) / 2 + 60);
	target->draw(*this->infoSprite);

	//ability
	this->infoSprite->setTextureRect({ 0 , 355  , 253 , 60 });
	this->infoSprite->setPosition(viewPos.x - 960, viewPos.y - 540 + 120);
	target->draw(*this->infoSprite);

	this->infoSprite->setTextureRect({ 0 , 268  , 167 * this->abilities / 4 , 27 }); // here procent multplier per width 
	this->infoSprite->setPosition(viewPos.x - 960 + 65, viewPos.y - 540 + (60 - 27) / 2 + 120);
	target->draw(*this->infoSprite);


	char number[3] = { '\0' };
	//coins
	this->infoSprite->setTextureRect({ 0 , 0  , 210 , 77 });
	this->infoSprite->setPosition(viewPos.x + 960, viewPos.y - 540);
	this->infoSprite->setScale(-1, 1);
	target->draw(*this->infoSprite);
	this->infoSprite->setScale(1, 1);


	number[1] = this->coins % 10 + 48;

	if (this->coins >= 10)
	{
		number[0] = this->coins / 10 + 48;
		number[2] = '\0';
	}
	else
	{
		number[2] = '\0';
		number[0] = ' ';
	}

	this->text->setString((sf::String)(number));
	this->text->setPosition(viewPos.x + 960 - 140, viewPos.y - 535);
	this->text->setCharacterSize(50);
	target->draw(*this->text);


	//diamonts
	this->infoSprite->setTextureRect({ 0 , 77  , 210 , 77 });
	this->infoSprite->setPosition(viewPos.x + 960 - 210, viewPos.y - 540 + 77);
	target->draw(*this->infoSprite);

	char numberD[3];
	numberD[1] = this->diamonts % 10 + 48;

	if (this->diamonts >= 10)
	{
		numberD[0] = this->diamonts / 10 + 48;
		numberD[2] = '\0';
	}
	else
	{
		numberD[0] = ' ';
		numberD[2] = '\0';
	}
	this->text->setString((sf::String)(numberD));
	this->text->setPosition(viewPos.x + 960 - 140, viewPos.y - 535 + 77);
	this->text->setCharacterSize(50);
	target->draw(*this->text);
}

bool Player::getLivesStatus()
{
	return this->lives>0?true:false;
}

bool Player::getJumpingStatus()
{
	return this->isJumping;
}

bool Player::getFallingStatus()
{
	return this->falling;
}

//contructor & destructor
Player::Player(sf::Vector2f position)
{
	this->spawnPosition = position;
	this->initInfo();
	this->initFont();
	this->initText();
	this->initCapabilities();
	this->setPhisics();
	this->setTexture();
	this->setSprite();
}

Player::~Player()
{
	delete(this->sprite);
	delete(this->texture);
	delete(this->infoSprite);
	delete(this->infoTexture);
	delete(this->text);
	delete(this->font);
}
