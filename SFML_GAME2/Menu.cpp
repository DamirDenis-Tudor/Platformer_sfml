#include "Menu.h"

//init
void Menu::initVariables()
{
	this->menuSelector = Main;
	this->inMenu = true;
	this->bgTexture = nullptr;
	this->bgSprite = nullptr;
	this->windowTexture = nullptr;
	this->windowSprite = nullptr;
	this->font = nullptr;
	this->text = nullptr;
	this->restart = false;
	this->maxTime = 1.f;
	this->time = this->maxTime;

}

void Menu::initTextures()
{
	this->windowTexture = new sf::Texture;
	this->windowTexture->loadFromFile("menu/menu.png");

	this->bgTexture = new sf::Texture;
	this->bgTexture->loadFromFile("menu/bgMenu.png");
}

void Menu::initSprites()
{
	this->windowSprite = new sf::Sprite;
	this->windowSprite->setTexture(*this->windowTexture);

	this->bgSprite = new sf::Sprite;
	this->bgSprite->setTexture(*this->bgTexture);
}

void Menu::initFont()
{
	this->font = new sf::Font;
	this->font->loadFromFile("menu/EvilEmpire-4BBVK.ttf");
}

void Menu::initText()
{
	this->text = new sf::Text;
	this->text->setFont(*this->font);
	this->text->setFillColor({ 153 , 102 ,51 });
	this->text->setLetterSpacing(1.f);
	this->text->setOutlineThickness(1.f);
}

//render and also update
void Menu::renderMenu(sf::RenderTarget* target  , sf::Vector2f viewPos, int& coins, int& diamonds, int& heath, int& shiends, int& attacks)
{
	this->restart = false;
	switch (this->menuSelector)
	{
	case Main:
		target->draw(*bgSprite);
		//title
		//crown
		this->windowSprite->setTextureRect({ 354 , 534 , 320 , 219 });
		this->windowSprite->setPosition({ (windowWidth - 320) / 2 , 200 });
		target->draw(*this->windowSprite);

		//
		this->windowSprite->setTextureRect({ 525 , 0 , 714 , 162 });
		this->windowSprite->setPosition({ (windowWidth - 714) / 2 , 419 });
		target->draw(*this->windowSprite);

		//text
		this->text->setString("THE KNIGHT");
		this->text->setPosition({ windowWidth / 2 - 230 , 419 });
		this->text->setCharacterSize(120);
		target->draw(*this->text);

		//start button
		this->buttonPos = { (windowWidth - 363) / 2 - 363 , 519 + 50 + 100 };
		if (sf::Mouse::getPosition(*(sf::RenderWindow*)target).x >= this->buttonPos.x && sf::Mouse::getPosition(*(sf::RenderWindow*)target).x <= this->buttonPos.x + 363
			&& sf::Mouse::getPosition(*(sf::RenderWindow*)target).y >= this->buttonPos.y && sf::Mouse::getPosition(*(sf::RenderWindow*)target).y <= this->buttonPos.y + 178)//hover
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				this->menuSelector = Start;
				this->windowSprite->setTextureRect({ 363 , 178 , 363 , 178 });
			}
			else
			{
				this->windowSprite->setTextureRect({ 0 , 178 , 363 , 178 });
			}
		}
		else
		{
			this->windowSprite->setTextureRect({ 1239 , 0 , 363 , 178 });
		}
		this->windowSprite->setPosition(this->buttonPos);
		target->draw(*this->windowSprite);

		this->text->setString("START");
		this->text->setPosition({ windowWidth / 2 - 100 - 353, 519 + 70 + 100 });
		this->text->setCharacterSize(100);
		target->draw(*this->text);

		//levels 

		this->buttonPos = { (windowWidth - 363) / 2 , 519 + 50 + 100 } ;
		if (sf::Mouse::getPosition(*(sf::RenderWindow*)target).x >= this->buttonPos.x && sf::Mouse::getPosition(*(sf::RenderWindow*)target).x <= this->buttonPos.x + 363
			&& sf::Mouse::getPosition(*(sf::RenderWindow*)target).y >= this->buttonPos.y && sf::Mouse::getPosition(*(sf::RenderWindow*)target).y <= this->buttonPos.y + 178)//hover
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				this->menuSelector = Levels;
				this->windowSprite->setTextureRect({ 363 , 178 , 363 , 178 });
			}
			else
			{
				this->windowSprite->setTextureRect({ 0 , 178 , 363 , 178 });
			}
		}
		else
		{
			this->windowSprite->setTextureRect({ 1239 , 0 , 363 , 178 });
		}
		this->windowSprite->setPosition( this->buttonPos );
		target->draw(*this->windowSprite);

		this->text->setString("LEVELS");
		this->text->setPosition({ windowWidth / 2 - 120 , 519 + 70 + 100 });
		this->text->setCharacterSize(100);
		target->draw(*this->text);

		//exit
		
		this->buttonPos = { (windowWidth - 363)/2  + 363, 519 + 50 + 100 } ;
		if (sf::Mouse::getPosition(*(sf::RenderWindow*)target).x >= this->buttonPos.x && sf::Mouse::getPosition(*(sf::RenderWindow*)target).x <= this->buttonPos.x + 363
			&& sf::Mouse::getPosition(*(sf::RenderWindow*)target).y >= this->buttonPos.y && sf::Mouse::getPosition(*(sf::RenderWindow*)target).y <= this->buttonPos.y + 178)//hover
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				this->menuSelector = Exit;
				this->windowSprite->setTextureRect({ 363 , 178 , 363 , 178 });
			}
			else
			{
				this->windowSprite->setTextureRect({ 0 , 178 , 363 , 178 });
			}
		}
		else
		{
			this->windowSprite->setTextureRect({ 1239 , 0 , 363 , 178 });
		}
		this->windowSprite->setPosition(this->buttonPos);
		target->draw(*this->windowSprite);

		this->text->setString("EXIT");
		this->text->setPosition({ windowWidth / 2 - 80 + 363 , 519 + 70  + 100 });
		this->text->setCharacterSize(100);
		target->draw(*this->text);
		
		break;

	case Pause:

		//title
		this->windowSprite->setTextureRect({ 0 , 0 , 525 , 107 });
		this->windowSprite->setPosition(viewPos.x - 525 / 2, viewPos.y - 717 / 2 + 170);
		target->draw(*this->windowSprite);

		this->text->setCharacterSize(60);
		this->text->setString("Pause");
		this->text->setPosition(viewPos.x - 525 / 2 + 195, viewPos.y - 717 / 2 + 170);
		target->draw(*this->text);

		if (viewPos.x * 2 > 1920)
		{
			mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x + (viewPos.x - 960);
		}
		else
		{
			mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x;
		}

		if (viewPos.y * 2 > 1080)
		{
			mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y + (viewPos.y - 540);
		}
		else if(viewPos.y * 2 == 1080)
		{
			mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y;
		}
		

		//exit
		this->buttonPos = { viewPos.x - 178/2 - 178 , viewPos.y - 717/2  + 278};

		if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
			&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				this->menuSelector = Main;
				this->restart = true;
				this->windowSprite->setTextureRect({ 353 , 356 , 176 , 178 });
			}
			else
			{
				this->windowSprite->setTextureRect({ 176 , 356 , 176 , 178 });
			}
		}
		else
		{
			this->windowSprite->setTextureRect({ 0 , 356 , 176 , 178 });
		}
		this->windowSprite->setPosition(this->buttonPos);
		target->draw(*this->windowSprite);


		//restart
		this->buttonPos = { viewPos.x - 178 / 2  , viewPos.y - 717 / 2 + 278 };

		if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
			&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				this->menuSelector = Start;
				this->restart = true;
				this->windowSprite->setTextureRect({ 176 , 534 , 176 , 178 });
			}
			else
			{
				this->windowSprite->setTextureRect({ 0 , 534 , 176 , 178 });
			}
		}
		else
		{
			this->windowSprite->setTextureRect({ 1588 , 356 , 176 , 178 });
		}
		this->windowSprite->setPosition(this->buttonPos);
		target->draw(*this->windowSprite);

		//continue
		this->buttonPos = { viewPos.x - 178/2 + 176 , viewPos.y - 717 / 2 + 278};

		if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
			&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				this->menuSelector = Start;
				this->windowSprite->setTextureRect({ 1605 , 178 , 176 , 178 });
			}
			else
			{
				this->windowSprite->setTextureRect({ 1429 , 178 , 176 , 178 });
			}
		}
		else
		{
			this->windowSprite->setTextureRect({ 1253 , 178 , 176 , 178 });
		}
		this->windowSprite->setPosition(this->buttonPos);
		target->draw(*this->windowSprite);


		break;
		case Shop:
			//design
			this->windowSprite->setTextureRect({ 0, 1674, 612, 716 });
			this->windowSprite->setPosition(viewPos.x - 612 /2 , viewPos.y - 716/2);
			target->draw(*this->windowSprite);

			this->windowSprite->setTextureRect({ 0, 2390, 715, 144 });
			this->windowSprite->setPosition(viewPos.x - 715 / 2, viewPos.y - 716 / 2 - 50);
			target->draw(*this->windowSprite);


			this->windowSprite->setTextureRect({ 612, 1674, 393, 523 });
			this->windowSprite->setPosition(viewPos.x - 393 / 2, viewPos.y - 523 / 2 );
			target->draw(*this->windowSprite);

			this->text->setCharacterSize(70);
			this->text->setString("SHOP");
			this->text->setPosition(viewPos.x - 50, viewPos.y - 783 / 2 - 5);
			target->draw(*this->text);


			this->windowSprite->setTextureRect({ 715, 2390, 473, 142 });

			this->windowSprite->setScale(0.75f , 0.75);

			this->windowSprite->setPosition((float)(viewPos.x - 473 * 0.75f / 2.f), (float)(viewPos.y - 716 / 2.f + 120));
			target->draw(*this->windowSprite);

			this->windowSprite->setPosition(viewPos.x - 473 * 0.75 / 2, viewPos.y - 716 / 2 + 120 + 142 + 30);
			target->draw(*this->windowSprite);

			this->windowSprite->setPosition(viewPos.x - 473 * 0.75 / 2, viewPos.y - 716 / 2 + 120 + 142 * 2 + 60);
			target->draw(*this->windowSprite);


			this->windowSprite->setScale(0.45f, 0.45);

			//health
			this->windowSprite->setTextureRect({ 1422, 2390, 115, 115 });
			this->windowSprite->setPosition(viewPos.x - 473 / 2 + 90, viewPos.y - 716 / 2 + 140);
			target->draw(*this->windowSprite);

			//shield
			this->windowSprite->setTextureRect({ 1537, 2390, 98, 115 });
			this->windowSprite->setPosition(viewPos.x - 473 / 2 + 90, viewPos.y - 716 / 2 + 140 + 150 + 30);
			target->draw(*this->windowSprite);

			//attack
			this->windowSprite->setTextureRect({ 1307, 2390, 115, 127 });
			this->windowSprite->setPosition(viewPos.x - 473 / 2 + 90, viewPos.y - 716 / 2 + 140 + 150 + 150 + 45);
			target->draw(*this->windowSprite);

			this->windowSprite->setScale(0.35f, 0.35);

			if (viewPos.x * 2 > 1920)
			{
				mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x + (viewPos.x - 960);
			}
			else
			{
				mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x;
			}

			if (viewPos.y * 2 > 1080)
			{
				mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y + (viewPos.y - 540);
			}
			else if (viewPos.y * 2 == 1080)
			{
				mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y;
			}

			//p1
			this->windowSprite->setTextureRect({ 1188, 2390, 119, 129 });
			this->windowSprite->setPosition(viewPos.x - 119 / 2 + 60, viewPos.y - 716 / 2 + 145);
			target->draw(*this->windowSprite);

			this->text->setCharacterSize(50);
			this->text->setString("10");
			this->text->setPosition(viewPos.x - 40, viewPos.y - 716 / 2 + 135);
			target->draw(*this->text);

			//p2
			this->windowSprite->setPosition(viewPos.x - 119 / 2 + 60, viewPos.y - 716 / 2 + 140 + 140 + 40);
			target->draw(*this->windowSprite);

			this->text->setString("10");
			this->text->setPosition(viewPos.x - 40, viewPos.y - 716 / 2 + 135 + 135 + 40);
			target->draw(*this->text);

			//p3
			this->windowSprite->setTextureRect({ 1635, 2390, 122, 114 });
			this->windowSprite->setPosition(viewPos.x - 122 / 2  + 65, viewPos.y - 716 / 2 + 140 + 150 + 140 + 65);
			target->draw(*this->windowSprite);

			this->text->setString("10");
			this->text->setPosition(viewPos.x - 40, viewPos.y - 716 / 2 + 135 + 150 + 150 + 45);
			target->draw(*this->text);

			this->windowSprite->setScale(0.45f, 0.45);
			//b1
			this->windowSprite->setPosition(viewPos.x - 473 / 2 + 473 - 176, viewPos.y - 716 / 2 + 130);
			buttonPos.x = viewPos.x - 473 / 2 + 473 - 176;
			buttonPos.y = viewPos.y - 716 / 2 + 130;

			if (coins < 10 || heath == 4)
			{
				this->windowSprite->setTextureRect({ 1535 , 1674 , 177 , 179 });
			}
			else
			{
				if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 177 * 0.45
					&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 179 * 0.45)//hover
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						this->windowSprite->setTextureRect({ 1358 , 1674 , 177 , 179 });
						
						if (!clicked)
						{
							coins -= 10;
							heath++;
						}
						this->clicked = true;
					}
					else
					{
						this->clicked = false;
						this->windowSprite->setTextureRect({ 1181 , 1674 , 177 , 179 });
					}
				}
				else
				{
					this->windowSprite->setTextureRect({ 1005, 1674, 177, 179 });
				}
			}
			target->draw(*this->windowSprite);

			//b2

			this->windowSprite->setPosition(viewPos.x - 473 / 2 + 473 - 176, viewPos.y - 716 / 2 + 140 + 140 + 25);
			buttonPos.x = viewPos.x - 473 / 2 + 473 - 176;
			buttonPos.y = viewPos.y - 716 / 2 + 140 + 140 + 25;
			if (coins < 10 || shiends == 4)
			{
				this->windowSprite->setTextureRect({ 1535 , 1674 , 177 , 179 });
			}
			else
			{
				if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 177 * 0.45
					&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 179 * 0.45)//hover
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						this->windowSprite->setTextureRect({ 1358 , 1674 , 177 , 179 });

						if (!this->clicked)
						{
							coins -= 10;;
							shiends++;
						}
						this->clicked = true;
					}
					else
					{
						this->clicked = false;
						this->windowSprite->setTextureRect({ 1181 , 1674 , 177 , 179 });
					}
				}
				else
				{
					this->windowSprite->setTextureRect({ 1005, 1674, 177, 179 });
				}
			}
			target->draw(*this->windowSprite);

			//b3
			this->windowSprite->setPosition(viewPos.x - 473 / 2 + 473 - 176, viewPos.y - 716 / 2 + 140 + 150 + 140 + 45);
			buttonPos.x = viewPos.x - 473 / 2 + 473 - 176;
			buttonPos.y = viewPos.y - 716 / 2 + 140 + 150 + 140 + 45;
			if (diamonds < 10 || attacks == 4)
			{
				this->windowSprite->setTextureRect({ 1535 , 1674 , 177 , 179 });
			}
			else
			{
				if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 177 * 0.45
					&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 179 * 0.45)//hover
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						this->windowSprite->setTextureRect({ 1358 , 1674 , 177 , 179 });

						if (!this->clicked)
						{
							diamonds -= 10;
							attacks++;
						}

						this->clicked = true;
					}
					else
					{
						this->clicked = false;
						this->windowSprite->setTextureRect({ 1181 , 1674 , 177 , 179 });
					}
				}
				else
				{
					this->windowSprite->setTextureRect({ 1005, 1674, 177, 179 });
				}
			}
			target->draw(*this->windowSprite);
			
			this->windowSprite->setScale(1, 1);

			break;

		case GameOver:

			//title
			this->windowSprite->setTextureRect({ 0 , 0 , 525 , 107 });
			this->windowSprite->setPosition(viewPos.x - 525 / 2, viewPos.y - 717 / 2 + 170);
			target->draw(*this->windowSprite);

			this->text->setCharacterSize(60);
			this->text->setString("FAILED");
			this->text->setPosition(viewPos.x - 525 / 2 + 195, viewPos.y - 717 / 2 + 170);
			target->draw(*this->text);

			if (viewPos.x * 2 > 1920)
			{
				mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x + (viewPos.x - 960);
			}
			else
			{
				mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x;
			}

			if (viewPos.y * 2 > 1080)
			{
				mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y + (viewPos.y - 540);
			}
			else if (viewPos.y * 2 == 1080)
			{
				mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y;
			}


			//exit
			this->buttonPos = { viewPos.x - 178 / 2 - 178/2 , viewPos.y - 717 / 2 + 278 };

			if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
				&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					this->menuSelector = Main;
					this->restart = true;
					this->windowSprite->setTextureRect({ 353 , 356 , 176 , 178 });
				}
				else
				{
					this->windowSprite->setTextureRect({ 176 , 356 , 176 , 178 });
				}
			}
			else
			{
				this->windowSprite->setTextureRect({ 0 , 356 , 176 , 178 });
			}
			this->windowSprite->setPosition(this->buttonPos);
			target->draw(*this->windowSprite);


			//restart
			this->buttonPos = { viewPos.x - 178 / 2 + 178 / 2 , viewPos.y - 717 / 2 + 278 };

			if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
				&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					this->menuSelector = Start;
					this->restart = true;
					this->windowSprite->setTextureRect({ 176 , 534 , 176 , 178 });
				}
				else
				{
					this->windowSprite->setTextureRect({ 0 , 534 , 176 , 178 });
				}
			}
			else
			{
				this->windowSprite->setTextureRect({ 1588 , 356 , 176 , 178 });
			}
			this->windowSprite->setPosition(this->buttonPos);
			target->draw(*this->windowSprite);

			break;
		case WinLevel:

			//title
			this->windowSprite->setTextureRect({ 0 , 0 , 525 , 107 });
			this->windowSprite->setPosition(viewPos.x - 525 / 2, viewPos.y - 717 / 2 + 170);
			target->draw(*this->windowSprite);

			this->text->setCharacterSize(60);
			this->text->setString("SUCCED");
			this->text->setPosition(viewPos.x - 525 / 2 + 195, viewPos.y - 717 / 2 + 175);
			target->draw(*this->text);

			if (viewPos.x * 2 > 1920)
			{
				mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x + (viewPos.x - 960);
			}
			else
			{
				mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x;
			}

			if (viewPos.y * 2 > 1080)
			{
				mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y + (viewPos.y - 540);
			}
			else if (viewPos.y * 2 == 1080)
			{
				mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y;
			}


			//exit
			this->buttonPos = { viewPos.x - 178 / 2 - 178 / 2 , viewPos.y - 717 / 2 + 278 };

			if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
				&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					this->menuSelector = Main;
					this->restart = true;
					this->windowSprite->setTextureRect({ 353 , 356 , 176 , 178 });
				}
				else
				{
					this->windowSprite->setTextureRect({ 176 , 356 , 176 , 178 });
				}
			}
			else
			{
				this->windowSprite->setTextureRect({ 0 , 356 , 176 , 178 });
			}
			this->windowSprite->setPosition(this->buttonPos);
			target->draw(*this->windowSprite);


			//restart
			this->buttonPos = { viewPos.x - 178 / 2 + 178 / 2 , viewPos.y - 717 / 2 + 278 };

			if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
				&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					this->menuSelector = Start;
					this->restart = true;
					this->windowSprite->setTextureRect({ 176 , 534 , 176 , 178 });
				}
				else
				{
					this->windowSprite->setTextureRect({ 0 , 534 , 176 , 178 });
				}
			}
			else
			{
				this->windowSprite->setTextureRect({ 1588 , 356 , 176 , 178 });
			}
			this->windowSprite->setPosition(this->buttonPos);
			target->draw(*this->windowSprite);

			break;

		case Levels:

			target->draw(*bgSprite);

			this->windowSprite->setTextureRect({ 0 , 957 , 1045 , 716 });
			this->windowSprite->setPosition({ viewPos.x - 1045 / 2 , 100 });
			target->draw(*this->windowSprite);
			//

			if (viewPos.x * 2 > 1920)
			{
				mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x + (viewPos.x - 960);
			}
			else
			{
				mousePos.x = sf::Mouse::getPosition(*(sf::RenderWindow*)target).x;
			}

			if (viewPos.y * 2 > 1080)
			{
				mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y + (viewPos.y - 540);
			}
			else if (viewPos.y * 2 == 1080)
			{
				mousePos.y = sf::Mouse::getPosition(*(sf::RenderWindow*)target).y;
			}

			//LEVELS

			//title
			this->windowSprite->setTextureRect({ 0 , 0 , 525 , 107 });
			this->windowSprite->setPosition(viewPos.x - 525 / 2, 50);
			target->draw(*this->windowSprite);

			this->text->setCharacterSize(60);
			this->text->setString("Levels");
			this->text->setPosition(viewPos.x - 525 / 2 + 190, 55);
			target->draw(*this->text);

			//home
			this->buttonPos = { viewPos.x - 176, viewPos.y + 716/2 - 50 };

			if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
			   && mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					this->menuSelector = Main;
					this->windowSprite->setTextureRect({ 353 , 356 , 176 , 178 });
				}
				else
				{
					this->windowSprite->setTextureRect({ 176 , 356 , 176 , 178 });
				}
			}
			else
			{
				this->windowSprite->setTextureRect({ 0 , 356 , 176 , 178 });
			}
			this->windowSprite->setPosition(this->buttonPos);
			target->draw(*this->windowSprite);

			//play
			this->buttonPos = { viewPos.x , viewPos.y + 716 / 2 - 50 };

			if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
				&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					this->menuSelector = Start;
					this->windowSprite->setTextureRect({ 1605 , 178 , 176 , 178 });
				}
				else
				{
					this->windowSprite->setTextureRect({ 1429 , 178 , 176 , 178 });
				}
			}
			else
			{
				this->windowSprite->setTextureRect({ 1253 , 178 , 176 , 178 });
			}
			this->windowSprite->setPosition(this->buttonPos);
			target->draw(*this->windowSprite);

			int aux = 1;
			int counter = 0;
			for (int j = 0; j < 2; j++)
			{
				for (int i = 0; i < 3; i++)
				{
					this->buttonPos = { viewPos.x - 252 + i * 176, viewPos.y  - 716/2 + 130 + j * 178 };

					if (mousePos.x >= this->buttonPos.x && mousePos.x <= this->buttonPos.x + 176
						&& mousePos.y >= this->buttonPos.y && mousePos.y <= this->buttonPos.y + 178)//hover
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
						{
							this->menuSelector = Start;
							this->windowSprite->setTextureRect({ 1077 , 178 , 177 , 178 });
						}
						else
						{
							this->windowSprite->setTextureRect({ 901 , 178 , 177 , 178 });
						}
					}
					else
					{
						this->windowSprite->setTextureRect({ 724 , 178 , 177 , 178 });
					}
					this->windowSprite->setPosition(this->buttonPos);
					target->draw(*this->windowSprite);

					std::cout <<counter << "\n";
					counter++;
					this->text->setString((sf::String)((char)(aux + counter + 47)) );
					this->text->setPosition({ viewPos.x - 180 + i * 176, viewPos.y - 716 / 2 + 150 + j * 178 });
					this->text->setCharacterSize(100);
					target->draw(*this->text);
				}

			}
			break;
	}
}

//contructor & destructor
Menu::Menu()
{
	this->initVariables();
	this->initTextures();
	this->initSprites();
	this->initFont();
	this->initText();
}

Menu::~Menu()
{
	delete(this->bgTexture);
	delete(this->bgSprite);
	delete(this->windowTexture);
	delete(this->windowSprite);
	delete(this->font);
	delete(this->text);
}



