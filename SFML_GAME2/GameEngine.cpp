#include "GameEngine.h"
#include<fstream>

//init functions
void Game::initVariables()
{
	this->playerInShop = false;
	this->deadZombiesCounter = 0;
	this->renderWindow = nullptr;
	this->player = nullptr;
	this->level = nullptr;
	this->view = nullptr;
	this->menu = nullptr;
	this->font = nullptr;
	this->text = nullptr;
	this->textDisplay = nullptr;
}

void Game::initRenderWindow()
{
	this->videoMode.height = windowHeight;
	this->videoMode.width = windowWidth;
	this->renderWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "The Knight" , sf::Style::Fullscreen  );
	this->renderWindow->setFramerateLimit(144);
}

void Game::initFontAndText()
{
	this->font = new sf::Font;
	this->font->loadFromFile("menu/EvilEmpire-4BBVK.ttf");

	this->text = new sf::Text;
	this->text->setFont(*this->font);
	this->text->setFillColor({ 153 , 102 ,51 });
	this->text->setLetterSpacing(1.f);
	this->text->setOutlineThickness(1.f);

	this->textDisplay = new sf::Text;
	this->textDisplay->setFont(*this->font);
	this->textDisplay->setFillColor({ 153 , 102 ,51 });
	this->textDisplay->setLetterSpacing(1.f);
	this->textDisplay->setOutlineThickness(1.f);

	this->maxTime = 5.f;
	this->time = 0.f;
}

void Game::initZombies()
{
	this->zPositions = this->map->getZombiesPosition(this->level->objects, this->level->widthM, this->level->heightM);
	for (int i = 0; i < this->zPositions.size(); i++)
	{
		this->zombies.push_back(new Zombie( this->zPositions[i] , rand()%2 - 1 ) );
	}
}

void Game::initBoxes()
{
	this->bPositions = this->map->getBoxesPosition(this->level->objects, this->level->widthM, this->level->heightM);
	for (int i = 0; i < this->bPositions.size(); i++)
	{
		this->boxes.push_back(new Box(this->bPositions[i]));
	}

	for (int i = 0; i < this->boxes.size(); i++)
	{
		this->boxes[i]->leftZombiesStatus.resize(this->zPositions.size());
		this->boxes[i]->rightZombiesStatus.resize(this->zPositions.size());
		this->boxes[i]->topZombiesStatus.resize(this->zPositions.size());
		this->boxes[i]->bottomZombiesStatus.resize(this->zPositions.size());

		for (int j = 0; j < this->zPositions.size(); j++)
		{
			this->boxes[i]->leftZombiesStatus[j] = false;
			this->boxes[i]->rightZombiesStatus[j] = false;
			this->boxes[i]->topZombiesStatus[j] = false;
			this->boxes[i]->bottomZombiesStatus[j] = false;
		}
	}
}

void Game::initPlayer()
{
	this->player = new Player( this->map->getPlayerPosition(this->level->objects, this->level->widthM , this->level->heightM) );
}

void Game::initSwitches()
{
	this->swtPositions = this->map->getSwitchPositions(this->level->objects, this->level->widthM ,this->level->heightM );
}

void Game::initDoor()
{
	this->dPosition = this->map->getDoorPosition(this->level->objects, this->level->widthM, this->level->heightM);
}

void Game::initShop()
{
	this->sPosition = this->map->getShopPosition(this->level->objects, this->level->widthM , this->level->heightM);
}

void Game::initView()
{
	this->menuView = new sf::View;
	this->menuView->setSize(sf::Vector2f{ (float)this->videoMode.width ,(float)this->videoMode.height });
	this->menuView->setCenter(960, 540);

	this->view = new sf::View;
	this->view->setSize( sf::Vector2f{(float)this->videoMode.width ,(float) this->videoMode.height });
	this->updateView();
}

void Game::initMap()
{
	this->map = new Map;
}

void Game::initMenu()
{
	this->menu = new Menu;
}

void Game::initLevel()
{
	std::ifstream file("Levels/level1.tmx");

	//get rid of info from file that isn't relevant
	std::string line;
	int iterator = 1;
	while (iterator <= 91)
	{
		std::getline(file, line);
		iterator++;
	}

	this->level = new Level;
	
	this->level->heightM = 27;
	this->level->widthM = 48;
	
	//dirt
	this->level->matrix = new int* [this->level->heightM];

	char check = '\0';
	for (int i = 0; i < this->level->heightM; i++)
	{
		this->level->matrix[i] = new int[this->level->widthM];
		for (int j = 0; j < this->level->widthM; j++)
		{
			file >> check;
			level->matrix[i][j] = check - '0';
			file >> check;
			if (check != ',')
			{
				level->matrix[i][j] = level->matrix[i][j] * 10 + (check - '0');
				file >> check;
			}
		}
	}

	iterator = 1;
	while (iterator <= 4)
	{
		std::getline(file, line);
		iterator++;
	}


	//objects
	this->level->objects = new int* [this->level->heightM];

	for (int i = 0; i < this->level->heightM; i++)
	{
		this->level->objects[i] = new int[this->level->widthM];
		for (int j = 0; j < this->level->widthM; j++)
		{
			file >> check;
			level->objects[i][j] = check - '0';
			file >> check;
			if (check != ',')
			{
				level->objects[i][j] = level->objects[i][j] * 10 + (check - '0');
				file >> check;
			}
		}
	}

	file.close();
}

const bool Game::isWindow()
{
	return this->renderWindow->isOpen();
}

const bool Game::isEvent()
{
	return this->renderWindow->pollEvent(this->event);
}

//retart
void Game::restartLevel()
{
	this->initLevel();
	this->player->restart();
	for (int i = 0; i < this->zombies.size(); i++)
	{
		this->zombies[i]->restart();
	}
	for (int i = 0; i < boxes.size(); i++)
	{
		this->boxes[i]->restart();
	}
	this->menu->restart = false;

	this->openDoor = false;
}

void Game::drawShopLogo()
{
	this->text->setCharacterSize(30);
	this->text->setString("SHOP");
	this->text->setPosition(this->sPosition.x * 60.f + 35, this->sPosition.y * 60.f - 45);
	this->renderWindow->draw(*this->text);
}

void Game::drawShopMessage()
{
	this->text->setCharacterSize(30);
	this->text->setString("Press 'B' to enter in the shop");
	this->text->setPosition(this->view->getCenter().x - 150, this->view->getCenter().y );
	this->renderWindow->draw(*this->text);
}

//pool events
void Game::poolEvents()
{
	while (this->isEvent())
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->renderWindow->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				if (this->menu->menuSelector == Pause || this->menu->menuSelector == Shop)
				{
					this->menu->menuSelector = Start;
				}
				else if(this->menu->menuSelector == Start)
				{
					this->menu->menuSelector = Pause;
				}
			}
		}
		if(this->menu->menuSelector == Exit)
		{
			this->renderWindow->close();
		}

		if (this->event.key.code == sf::Keyboard::R)
		{
			this->player->deadStatus = true;
		}
		if (this->event.key.code == sf::Keyboard::T)
		{
			this->player->deadStatus = true;
			for (int i = 0; i < boxes.size(); i++)
			{
				this->boxes[i]->restart();
			}
		}

		if (this->event.key.code == sf::Keyboard::B && this->playerInShop && this->menu->menuSelector != Pause)
		{
			this->menu->menuSelector = Shop;
		}


	}
}

//draw text
void Game::drawText(std::string message)
{
	this->textDisplay->setString(message);
	this->textDisplay->setPosition({ this->view->getCenter().x - 150 , this->view->getCenter().y + 200});
	this->textDisplay->setCharacterSize(50);

	this->time += 0.01;
	std::cout << time << "\n";

	if (this->time >= this->maxTime)
	{
		this->time = 0.f;
		this->textDrawFinish = true;

	}
}
//render & update
void Game::renderMenu()
{
	if (this->menu->menuSelector == Main || this->menu->menuSelector == Levels)
	{
		this->menu->renderMenu(this->renderWindow , this->menuView->getCenter() , this->player->coins , this->player->diamonts , this->player->lives , this->player->shields , this->player->abilities);
	}
	else
	{
		this->menu->renderMenu(this->renderWindow, this->view->getCenter() , this->player->coins, this->player->diamonts, this->player->lives, this->player->shields, this->player->abilities);
	}
}

void Game::renderMapTiles()
{
	this->map->renderMapLayer1(this->renderWindow, this->level->matrix , this->level->objects, this->level->heightM, this->level->widthM);
}

void Game::renderMapObjects()
{
	this->map->renderMapLayer2(this->renderWindow, this->level->objects, this->level->heightM, this->level->widthM);
}

void Game::renderBoxes()
{
	for (int i = 0; i < this->boxes.size(); i++)
	{
		this->boxes[i]->render(this->renderWindow);
	}
}

void Game::updateBoxes()
{
	bool topStatus = false;
	bool leftStatus = false;
	bool rightStatus = false;
	bool bottomStatus = false;

	bool bottomBoxCollision = false;
	int bottomBoxCollisionIndex = 0;

	bool boxCollision = false;

	int boxCheckIndex;

	std::vector<bool> rightBoxCollisionZombie;
	std::vector<bool> leftBoxCollisionZombie;
	std::vector<bool> topBoxCollisionZombie;
	std::vector<bool> bottomBoxCollisionZombie;

	std::vector<int> rightBoxCollisionZombieIndex;
	std::vector<int> leftBoxCollisionZombieIndex;

	rightBoxCollisionZombie.resize(this->zPositions.size());
	leftBoxCollisionZombie.resize(this->zPositions.size());
	topBoxCollisionZombie.resize(this->zPositions.size());
	bottomBoxCollisionZombie.resize(this->zPositions.size());

	rightBoxCollisionZombieIndex.resize(this->zPositions.size());
	leftBoxCollisionZombieIndex.resize(this->zPositions.size());


	for (int i = 0; i < this->zPositions.size(); i++)
	{
		rightBoxCollisionZombie[i] = false;
		leftBoxCollisionZombie[i] = false;
		topBoxCollisionZombie[i] = false;
		bottomBoxCollisionZombie[i] = false;
	}

	sf::Vector2f position = this -> player->getPos();
	sf::Vector2f velocity = this->player->getVelocity();

	for (int i = 0; i < this->boxes.size(); i++)
	{
		boxCheckIndex = i;
	//	std::cout << "box index (" << i << ") :  ";
		//if (boxes[i]->wasMoved)
		{
			this->boxes[i]->update(position, velocity, this->zPositions, this->level->matrix, this->deltaTime.asSeconds(), this->player->deadStatus, this->player->getJumpingStatus());
		}
	//	std::cout << "pushed  right : " << this->boxes[i]->pushedRight << " , pushed left : " << this->boxes[i]->pushedLeft << "\n";

		//player interaction
		if (this->boxes[i]->topColision)
		{
			topStatus = true;
		}

		if (this->boxes[i]->leftStatusPlayer)
		{
			leftStatus = true;
		}

		if (this->boxes[i]->rightStatusPlayer)
		{
			rightStatus = true;
		}

		if (this->boxes[i]->bottomCollision)
		{
			bottomStatus = true;
			if (this->boxes[i]->getFallingStatus())
			{
				this->player->deadStatus = true;
				this->player->velocity.x = 0;
			}
			this->boxes[i]->bottomCollision = false;
		}

		//zombie interation
		for (int j = 0; j < zPositions.size(); j++)
		{
			if (boxes[i]->leftZombiesStatus[j])
			{
				leftBoxCollisionZombie[j] = true;
				leftBoxCollisionZombieIndex[j] = i;
			}

			if (boxes[i]->rightZombiesStatus[j])
			{
				rightBoxCollisionZombie[j] = true;
				rightBoxCollisionZombieIndex[j] = i;
			}

			if (boxes[i]->topZombiesStatus[j] && !this->zombies[j]->getFallingStatus() && !boxes[i]->bottomZombiesStatus[j])
			{
				this->zombies[j]->setDeadStatus(true);
			}

			if (boxes[i]->bottomZombiesStatus[j])
			{
				bottomBoxCollisionZombie[j] = true;
			}
		}
		


		//box -> boxes interaction
		for (int k = 0; k < boxes.size(); k++)
		{
			this->boxes[k]->checked = false;
			this->boxes[k]->wasMoved = false;
		}

		bool checked = true;
		this->boxes[i]->checked = true;

		//left - right   -> n^3 complexity
		//boxes aren't positioned in order -> need rechecking
		while (checked)
		{
			sf::Vector2f refferenceBoxPos = this->boxes[boxCheckIndex]->getPosition();
			for (int j = 0; j < this->boxes.size(); j++)
			{
				//std::cout << boxCheckIndex << "\n";
				if (j != boxCheckIndex && !this->boxes[j]->checked )
				{
					if (((refferenceBoxPos.x <= this->boxes[j]->getPosition().x && refferenceBoxPos.x + 0.95 >= this->boxes[j]->getPosition().x)
						|| (refferenceBoxPos.x + 1 >= this->boxes[j]->getPosition().x + 1 && refferenceBoxPos.x + 0.05 <= this->boxes[j]->getPosition().x + 1.0))
						&& refferenceBoxPos.y <= this->boxes[j]->getPosition().y + 0.90 && refferenceBoxPos.y + 0.90 >= this->boxes[j]->getPosition().y)
					{
						if (this->boxes[boxCheckIndex]->pushedLeft)
						{
							this->boxes[j]->pushedLeft = true;
						}

						if (this->boxes[boxCheckIndex]->pushedRight)
						{
							this->boxes[j]->pushedRight = true;
						}

						if (this->boxes[j]->rightStatus)
						{
							this->boxes[boxCheckIndex]->rightStatus = true;
						}
						if (this->boxes[j]->leftStatus)
						{
							this->boxes[boxCheckIndex]->leftStatus = true;
						}

						boxCheckIndex = j;
						this->boxes[boxCheckIndex]->checked = true;
						checked = true;
						if (boxCheckIndex != i)
						{
							this->boxes[boxCheckIndex]->update(position, velocity, this->zPositions, this->level->matrix, this->deltaTime.asSeconds(), this->player->deadStatus, this->player->getJumpingStatus());
							this->boxes[boxCheckIndex]->wasMoved = true;
						}

						break;
					}
				}
				else
				{
					checked = false;
				}
			}
		}

		//botoom
		sf::Vector2f refferenceBoxPos = this->boxes[i]->getPosition();
		bottomBoxCollision = false;
		for (int j = 0; j < this->boxes.size(); j++)
		{
			if (j != i)
			{
				if (refferenceBoxPos.x < this->boxes[j]->getPosition().x + 0.97 && refferenceBoxPos.x + 0.97 > this->boxes[j]->getPosition().x
					&& refferenceBoxPos.y + 1.05 >= this->boxes[j]->getPosition().y && refferenceBoxPos.y <= this->boxes[j]->getPosition().y)
				{
					bottomBoxCollision = true;
				}
			}
			if (bottomBoxCollision)
			{
				this->boxes[i]->bottomBoxCollision = true;
			}
			else
			{
				this->boxes[i]->bottomBoxCollision = false;
			}
		}
	}

	//actualize statutes with player
	if (topStatus)
	{
		this->player->topBoxColision = true;
	}
	else
	{
		this->player->topBoxColision = false;
	}

	if (rightStatus)
	{
		this->player->rightBoxCol = true;
	}
	else
	{
		this->player->rightBoxCol = false;
	}

	if (leftStatus)
	{
		this->player->leftBoxCol = true;
	}
	else
	{
		this->player->leftBoxCol = false;
	}

	if (bottomStatus && !this->player->getFallingStatus())
	{
		this->player->bottomBoxCollision = true;
	}
	else
	{
		this->player->bottomBoxCollision = false;
	}

	//actualize zombies statuses
	for (int i = 0; i < this->zPositions.size(); i++)
	{
		if (!this->zombies[i]->getDeadStatus())
		{
			if (leftBoxCollisionZombie[i] && !this->zombies[i]->getFallingStatus())
			{
				this->zombies[i]->leftBoxCollision = true;
				if (this->zombies[i]->getWaitingStatus() || abs(this->zombies[i]->getVelocity().x) < abs(this->boxes[leftBoxCollisionZombieIndex[i]]->getVelocity().x))
				{
					this->zombies[i]->zombieBoxCol = true;
					if (this->boxes[leftBoxCollisionZombieIndex[i]]->getVelocity().x != 0)
					{
						this->zombies[i]->setVelocityHorizontally({ this->boxes[leftBoxCollisionZombieIndex[i]]->getVelocity().x });
					}
				}
				else
				{
					this->zombies[i]->direction.x = -1.f;
					this->zombies[i]->zombieBoxCol = false;
				}
			}
			else
			{
				this->zombies[i]->leftBoxCollision = false;
			}

			if (rightBoxCollisionZombie[i] && !this->zombies[i]->getFallingStatus())
			{
				this->zombies[i]->rightBoxCollision = true;

				if (this->zombies[i]->getWaitingStatus() || abs(this->zombies[i]->getVelocity().x) < abs(this->boxes[rightBoxCollisionZombieIndex[i]]->getVelocity().x))
				{
					this->zombies[i]->zombieBoxCol = true;
					if (this->boxes[rightBoxCollisionZombieIndex[i]]->getVelocity().x != 0)
					{
						this->zombies[i]->setVelocityHorizontally({ this->boxes[rightBoxCollisionZombieIndex[i]]->getVelocity().x });
					}
				}
				else
				{
					this->zombies[i]->direction.x = 1.f;
					this->zombies[i]->zombieBoxCol = false;
				}
			}
			else
			{
				this->zombies[i]->rightBoxCollision = false;
			}

			if (bottomBoxCollisionZombie[i])
			{
				this->zombies[i]->bottomBoxCollision = true;
			}
			else
			{
				this->zombies[i]->bottomBoxCollision = false;
			}
		}
	}
}

void Game::renderZombies()
{
	for (int i = 0; i < this->zombies.size(); i++)
	{
		this->zombies[i]->render(this->renderWindow);
	}
}

void Game::updateZombies()
{		
	bool hit = false;
	int deadZ = 0;

	for (int i = 0; i < this->zombies.size(); i++)
	{
		//update and check player collision
		
		hit = this->zombies[i]->update(this->level->matrix, this->player->getPos(), this->player->getAttackStatus(), this->player->getGroundStatus(), this->player->getShieldStatus(), this->deltaTime.asSeconds());
		if (hit)
		{
			if (this->player->getShieldStatus())
			{
				this->player->shieldBreakStatus = hit;
			}
			else
			{
				this->player->deadStatus = hit;
			}
		}
		//zombie attack hasn't effect immediately
		if (this->zombies[i]->getFreezeStatus() && this->zombies[i]->prevFreezeStatus != this->zombies[i]->getFreezeStatus())
		{
			if (this->player->getShieldStatus())
			{
				this->player->decShieds();
			}
		}
		this->zombies[i]->prevFreezeStatus = this->zombies[i]->getFreezeStatus();

		//update positions
		this->zPositions[i] = this->zombies[i]->getPosition();

		//update collision with objects
		this->zombies[i]->updateTrapCollision(this->level->objects);

		//reward spawn
		if (this->zombies[i]->getDeadStatus() && this->level->objects[(int)this->zombies[i]->getSpawnPosition().y][(int)this->zombies[i]->getSpawnPosition().x] != 0)
		{
			//here randomaze reward
			this->level->objects[(int)this->zombies[i]->getSpawnPosition().y][(int)this->zombies[i]->getSpawnPosition().x] = 37;
		}
		
		//conter for dead zombies
		if (this->zombies[i]->getDeadStatus())
		{
			deadZ++;
		}
	}
	this->deadZombiesCounter = deadZ;

	this->deadZombies = true;
	for (int i = 0; i < zombies.size(); i++)
	{
		if (!this->zombies[i]->getDeadStatus())
		{
			this->deadZombies = false;
		}
	}
}


void Game::renderTabInfo()
{
	this->text->setCharacterSize(30);
	this->text->setString("Zombie killed : ");
	
	this->text->setPosition(this->view->getCenter().x - 1920/2 + 20 , this->view->getCenter().y - 350 );

	this->renderWindow->draw(*this->text);

	char zombies[4];
	if (this->zPositions.size() > 10)
	{
		zombies[2] = '\0';
		zombies[1] = this->deadZombiesCounter % 10 + 48;
		zombies[0] = this->deadZombiesCounter / 10 + 48;
	}
	else
	{
		zombies[0] = this->deadZombiesCounter / 10 + 48;
		zombies[1] = '\0';
		zombies[2] = '\0';
	}

	this->text->setString((std::string)zombies);

	this->text->setPosition(this->view->getCenter().x - 1920 / 2 + 220, this->view->getCenter().y - 350);

	this->renderWindow->draw(*this->text);

	//char zombies[4];
	if (this->zPositions.size() > 10)
	{
		zombies[3] = '\0';
		zombies[0] = '/';
		zombies[2] = this->zPositions.size() % 10 + 48;
		zombies[1] = this->zPositions.size() / 10 + 48;
	}
	else
	{
		zombies[0] = this->zPositions.size() / 10 + 48;
		zombies[1] = '/';
		zombies[2] = '\0';
	}

	this->text->setString((std::string)zombies);

	this->text->setPosition(this->view->getCenter().x - 1920 / 2 + 250, this->view->getCenter().y - 350);

	this->renderWindow->draw(*this->text);


	this->text->setString("Switches opened : ");

	this->text->setPosition(this->view->getCenter().x - 1920 / 2 + 20, this->view->getCenter().y - 300);

	this->renderWindow->draw(*this->text);

	char switches[3];

	switches[0] = this->openSwtCounter % 10 + 48;
	switches[1] = '\0';
	switches[2] = '\0';

	this->text->setString((std::string)switches);

	this->text->setPosition(this->view->getCenter().x - 1920 / 2 + 250, this->view->getCenter().y - 300);

	this->renderWindow->draw(*this->text);

	//char switches[3];
	
	switches[1] = this->swtPositions.size() % 10 + 48;
	switches[0] = '/';
	switches[2] = '\0';

	this->text->setString((std::string)switches);

	this->text->setPosition(this->view->getCenter().x - 1920 / 2 + 270, this->view->getCenter().y - 300);

	this->renderWindow->draw(*this->text);
}

void Game::renderPlayer()
{
	this->player->renderPlayer(this->renderWindow );
}

void Game::renderPlayerInfo()
{
	this->player->renderPlayerInfo(this->renderWindow, this->view->getCenter());
}

void Game::updatePlayer()
{
	this->player->updateMovement(this->level->matrix ,this->deltaTime.asSeconds() );
	this->player->updateInfo(this->level->objects);
	this->player->updateObjectsCollision(this->level->objects);
	if (this->player->position.x < this->sPosition.x + 2 && this->player->position.x + 1 > this->sPosition.x && this->player->position.y < this->sPosition.y + 1 && this->player->position.y + 1 > this->sPosition.y)
	{
		this->playerInShop = true;
	}
	else
	{
		this->playerInShop = false;
	}
}

void Game::updateSwitchesAndDoor()
{
	int openS = 0;
	//switches
	for (int i = 0; i < swtPositions.size(); i++)
	{
		for (int j = 0; j < boxes.size(); j++)
		{
			if ((int)this->boxes[j]->getPosition().y == (int)swtPositions[i].y && this->boxes[j]->getPosition().x + 1 >= swtPositions[i].x + 0.4 && this->boxes[j]->getPosition().x <= swtPositions[i].x + 0.6)
			{
				this->level->objects[(int)swtPositions[i].y][(int)swtPositions[i].x] = switchOpen;
				break;
			}
			else
			{
				this->level->objects[(int)swtPositions[i].y][(int)swtPositions[i].x] = switchClose;
			}
		}
		if (this->level->objects[(int)swtPositions[i].y][(int)swtPositions[i].x] == switchOpen)
		{
			openS++;
		}
	}
	this->openSwtCounter = openS;

	//door
	bool doorUnlk = true;
	for (int i = 0; i < swtPositions.size(); i++)
	{
		if (this->level->objects[(int)swtPositions[i].y][(int)swtPositions[i].x] == switchClose)
		{
			doorUnlk = false;
		}
	}

	//std::cout << this->textDrawFinish << "\n";
	this->openDoor = false;
	if (doorUnlk)
	{
		this->level->objects[(int)this->dPosition.y][(int)this->dPosition.x] = doorUnlocked;
		this->drawEvent = true;
		if(!this->textDrawFinish && !this->playerDoorCheck)
		{
			this->drawText((std::string)"Door unlocked!");
		}

		if (this->player->position.y + 1 >= this->dPosition.y - 1 && this->player->position.y  <= this->dPosition.y + 1 && this->player->position.x + 1 >= this->dPosition.x + 0.8 && this->player->position.x <= this->dPosition.x + 0.4 )
		{
			this->level->objects[(int)this->dPosition.y][(int)this->dPosition.x] = doorOpen;
			this->openDoor = true;

			if (!this->deadZombies && !this->textDrawFinish )
			{
				this->drawText((std::string)"Kill the zombies!");
				this->playerDoorCheck = true;
			}
			else
			{
				this->time = 0.f;
				textDrawFinish = false;
				this->drawEvent = false;
				this->playerDoorCheck = false;
			}
		}
		else
		{
			if (this->playerDoorCheck)
			{
				this->drawEvent = false;
			}
		}
	}
	else
	{
		this->playerDoorCheck = false;
		this->drawEvent = false;
		this->textDrawFinish = false;
		this->level->objects[(int)this->dPosition.y][(int)this->dPosition.x] = doorLocked;
	}
}

void Game::updateTime()
{
	this->deltaTime = this->clock.restart();
}

void Game::updateView()
{
	//down - top - left - right borders
	float vertical = (float)this->player->sprite->getPosition().y , horizoltal = (float)this->player->sprite->getPosition().x ;
	if (this->player->sprite->getPosition().y / 60 <=  viewTilesH / 2 )//top 
	{
		vertical = viewTilesH / 2 * 60;
	}

	if (this->player->sprite->getPosition().y / 60 >= this->level->heightM- viewTilesH / 2)//down 
	{
		vertical = (float)(this->level->heightM * 60 - viewTilesH * 60 / 2);
	}

	if (this->player->sprite->getPosition().x / 60 <= viewTilesW / 2)//left
	{
		horizoltal = viewTilesW / 2 * 60;
	}

	if (this->player->sprite->getPosition().x / 60 >= this->level->widthM -  viewTilesW / 2)//right
	{
		horizoltal = this->level->widthM * 60 - viewTilesW / 2 * 60;
	}

	this->view->setCenter(horizoltal , vertical);
}

void Game::renderView()
{
	this->renderWindow->setView(*this->view);
}

void Game::renderMenuView()
{
	this->renderWindow->setView(*this->menuView);
}

void Game::render()
{
	this->renderWindow->clear();

	if (this->menu->menuSelector != Main && this->menu->menuSelector != Exit)
	{
		this->renderMapTiles();
		this->renderBoxes();
		this->drawShopLogo();
		this->renderZombies();
		this->renderPlayer();
		this->renderMapObjects();
		this->renderPlayerInfo();
		
		if (!this->textDrawFinish && this->drawEvent)
		{
			this->renderWindow->draw(*this->textDisplay);
		}	

		if (this->playerInShop && this->menu->menuSelector != Shop)
		{
			this->drawShopMessage();
		}
		
		this->renderTabInfo();
		this->renderView();
	}
	if( !this->menu->menuSelector == Start )
	{
		if (this->menu->menuSelector == Main || this->menu->menuSelector == Levels || this->menu->menuSelector == Controls)
		{
			this->renderMenuView();
		}
		this->renderMenu(); //i can pas view pos for pause menu
	}

	if (this->menu->menuSelector == Start)
	{
		this->renderWindow->setMouseCursorVisible(false);
	}
	else
	{
		this->renderWindow->setMouseCursorVisible(true);

	}

	this->renderWindow->display();
}

void Game::update()
{
	this->poolEvents();
	this->updateTime();
	
	if (this->menu->menuSelector == Start)
	{
		this->updateView();
		this->updatePlayer();
		this->updateZombies();
		this->updateBoxes();
		this->updateSwitchesAndDoor();
		this->updateView();

	}
	
	if(this->menu->menuSelector == Main || this->menu->menuSelector == Start)
	{
		if (this->menu->restart)
		{
			this->restartLevel();
		}
	}

	if (!this->player->getLivesStatus())
	{
		this->menu->menuSelector = GameOver;
	}

	if (this->openDoor && this->deadZombies)
	{
		this->menu->menuSelector = WinLevel;
	}
}

//contructor & destructor
Game::Game()
{
	this->initVariables();
	this->initMenu();
	this->initRenderWindow();
	this->initFontAndText();
	this->initLevel();
	this->initMap();
	this->initSwitches();
	this->initDoor();
	this->initShop();
	this->initZombies();
	this->initBoxes();
	this->initPlayer();
	this->initView();
}

Game::~Game()
{

	delete(this->player);
	for (int i = 0; i < this->zombies.size(); i++)
	{
		delete(this->zombies[i]);
	}
	for (int i = 0; i < this->level->heightM; i++)
	{
		delete(this->level->matrix[i]);
		delete(this->level->objects[i]);
	}
	delete(this->level->matrix);
	delete(this->level->objects);
	delete(this->level);
	delete(this->renderWindow);
	delete(this->view);
	delete(this->menu);
}

