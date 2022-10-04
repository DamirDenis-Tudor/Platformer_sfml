#include "Map.h"

//init

void Map::initTexture()
{
	this->bg = new sf::Texture;
	this->bg->loadFromFile("sprites/BG.png");

	this->textureDirt = new sf::Texture;
	this->textureDirt->loadFromFile("sprites/spriteSheets/dirt.png");

	this->textureObjects = new sf::Texture;
	this->textureObjects->loadFromFile("sprites/spriteSheets/objects3.png");
}

void Map::initSprite()
{
	this->bgSprite = new sf::Sprite;
	this->bgSprite->setTexture(*this->bg);
	this->bgSprite->setScale(1.5f, 1.5f);

	this->spriteDirt = new sf::Sprite;
	this->spriteDirt->setTexture(*this->textureDirt);

	this->spriteObjects = new sf::Sprite;
	this->spriteObjects->setTexture(*this->textureObjects);
}

//update

void Map::renderMapLayer1(sf::RenderTarget* target, int**& map , int **&objects, int& width, int& height)
{
	//
	// Tiled  -> generates two matrixs
	//
	target->draw(*this->bgSprite);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			bool draw = true;
			switch (map[i][j])//dirt types
			{
			case 1:
				this->spriteDirt->setTextureRect(sf::IntRect{ 0 * 60, 0 , 60 , 60 });
				break;

			case 2:
				this->spriteDirt->setTextureRect(sf::IntRect{ 1 * 60 , 0 , 60 , 60 });
				break;

			case 3:
				this->spriteDirt->setTextureRect(sf::IntRect{ 2 * 60 , 0 , 60 , 60 });
				break;

			case 4:
				this->spriteDirt->setTextureRect(sf::IntRect{ 3 * 60 , 0 , 60 , 60 });
				break;

			case 5:
				this->spriteDirt->setTextureRect(sf::IntRect{ 4 * 60 , 0 , 60 , 60 });
				break;

			case 6:
				this->spriteDirt->setTextureRect(sf::IntRect{ 5 * 60 , 0 , 60 , 60 });
				break;

			case 7:
				this->spriteDirt->setTextureRect(sf::IntRect{ 6 * 60 , 0 , 60 , 60 });
				break;

			case 8:
				this->spriteDirt->setTextureRect(sf::IntRect{ 7 * 60 , 0 , 60 , 60 });
				break;

			case 9:
				this->spriteDirt->setTextureRect(sf::IntRect{ 8 * 60 , 0 , 60 , 60 });
				break;

			case 10:
				this->spriteDirt->setTextureRect(sf::IntRect{ 9 * 60 , 0 , 60 , 60 });
				break;

			case 11:
				this->spriteDirt->setTextureRect(sf::IntRect{ 10 * 60 , 0 , 60 , 60 });
				break;

			case 12:
				this->spriteDirt->setTextureRect(sf::IntRect{ 11 * 60 , 0 , 60 , 60 });
				break;

			case 13:
				this->spriteDirt->setTextureRect(sf::IntRect{ 12 * 60 , 0 , 60 , 60 });
				break;

			case 14:
				this->spriteDirt->setTextureRect(sf::IntRect{ 13 * 60 , 0 , 60 , 60 });
				break;

			case 15:
				this->spriteDirt->setTextureRect(sf::IntRect{ 14 * 60 , 0 , 60 , 60 });
				break;

			case 16:
				this->spriteDirt->setTextureRect(sf::IntRect{ 15 * 60 , 0 , 60 , 60 });
				break;

			default:
				draw = false;
				break;
			}
			if (draw)
			{
				this->spriteDirt->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->spriteDirt);
			}

			draw = true;

			int verticalAligment = 0;
			switch (objects[i][j])
			{
			case 30://bush 2
				this->spriteObjects->setTextureRect(sf::IntRect{ 73 , 0 , 47 , 30 });
				verticalAligment = 30;
				break;
			case 17://arrow sign
				this->spriteObjects->setTextureRect(sf::IntRect{ 0 , 36 , 40 , 41 });
				verticalAligment = 19;
				break;
			case 18://bush 1
				this->spriteObjects->setTextureRect(sf::IntRect{ 40 , 36 , 85 , 42 });
				verticalAligment = 18;
				break;
			case 20://info
				this->spriteObjects->setTextureRect(sf::IntRect{ 125 , 36 , 43 , 44 });
				verticalAligment = 16;
				break;
			case 21://bone
				this->spriteObjects->setTextureRect(sf::IntRect{ 0 , 0 , 48 , 23 });
				verticalAligment = 37;
				break;
			case 22:///grave spawner
				this->spriteObjects->setTextureRect(sf::IntRect{ 48 , 0 , 25 , 26 });
				verticalAligment = 34;
				break;
			case 23://grave
				this->spriteObjects->setTextureRect(sf::IntRect{ 182 , 0 , 25 , 36 });
				verticalAligment = 24;
				break;
			case 24://three
				this->spriteObjects->setTextureRect(sf::IntRect{ 60 , 146 , 134 , 112 });
				verticalAligment = -52;
				break;
			case 26://bone
				this->spriteObjects->setTextureRect(sf::IntRect{ 60 , 86 , 60 , 60 });
				break;
			case 28://bone
				this->spriteObjects->setTextureRect(sf::IntRect{ 120 , 86 , 60 , 60 });
				break;
			case 27://bone
				this->spriteObjects->setTextureRect(sf::IntRect{ 0 , 146 , 60 , 60 });
				break;
			case 29://bone
				this->spriteObjects->setTextureRect(sf::IntRect{ 0 , 86 , 60 , 60 });
				break;
			case 33://coin
				this->spriteObjects->setTextureRect(sf::IntRect{ 120 , 258 , 31 , 34 });
				verticalAligment = 16;
				break;
			case 34://heath
				this->spriteObjects->setTextureRect(sf::IntRect{ 181 , 258 , 30 , 30 });
				verticalAligment = 20;
				break;
			case 35://shield
				this->spriteObjects->setTextureRect(sf::IntRect{ 0 , 318 , 26 , 30 });
				verticalAligment = 20;
				break;
			case 36://Attack ability
				this->spriteObjects->setTextureRect(sf::IntRect{ 151 , 258 , 30 , 33 });
				verticalAligment = 17;
				break;
			case 37://diamond
				this->spriteObjects->setTextureRect(sf::IntRect{ 26 , 318 , 33 , 30 });
				verticalAligment = 20;
				break;
			case 38://spikes
				this->spriteObjects->setTextureRect(sf::IntRect{ 0 , 348 + 120 , 60 , 60 });
				break;
			case 43://switch open
				this->spriteObjects->setTextureRect(sf::IntRect{ 60 , 348 + 120 , 34 , 120 });
				verticalAligment = -60;
				break;
			case 40://switch close
				this->spriteObjects->setTextureRect(sf::IntRect{ 94 , 348 + 120 , 34 , 120 });
				verticalAligment = -60;
				break;
			case 41://door unLocked
				this->spriteObjects->setTextureRect(sf::IntRect{ 0 , 348 , 72 , 120 });
				verticalAligment = -60;
				break;
			case 42://door open
				this->spriteObjects->setTextureRect(sf::IntRect{ 72 , 348 , 72 , 120 });
				verticalAligment = -60;
				break;
			case 39://door locked
				this->spriteObjects->setTextureRect(sf::IntRect{ 144 , 348 , 72 , 120 });
				verticalAligment = -60;
				break;
			case 44://door locked
				this->spriteObjects->setTextureRect(sf::IntRect{ 0 , 588 , 120 , 75 });
				verticalAligment = -15;
				break;
			default:
				draw = false;
				break;
			}
			if (draw)
			{
				this->spriteObjects->setPosition({ j * 60.f  , i * 60.f + verticalAligment });
				target->draw(*this->spriteObjects);
			}
		}
	}
}

void Map::renderMapLayer2(sf::RenderTarget* target, int**& objects, int& width, int& height)
{

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			bool draw = true;

			int verticalAligment = 0;
			switch (objects[i][j])
			{
			case 19://crate
				//this->spriteObjects->setTextureRect(sf::IntRect{ 168 , 36 , 50 , 50 });
				//verticalAligment = 10;
				draw = false;
				break;

			case 25://damege bush
				this->spriteObjects->setTextureRect(sf::IntRect{ 120 , 0 , 62 , 35 });
				verticalAligment = 25;
				break;
			case 32://water1
				this->spriteObjects->setTextureRect(sf::IntRect{ 0 , 258 , 60 , 60 });
				break;
			case 31://water2
				this->spriteObjects->setTextureRect(sf::IntRect{ 60 , 258 , 60 , 48 });
				verticalAligment = 14;
				break;
			default:
				draw = false;
				break;
			}
			if (draw)
			{
				this->spriteObjects->setPosition({ j * 60.f  , i * 60.f + verticalAligment });
				target->draw(*this->spriteObjects);
			}

		}
	}
}

//get moveble objects positions
std::vector<sf::Vector2f> Map::getZombiesPosition(int**& objects , int& width, int& height)
{
	std::vector<sf::Vector2f> zPositions;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (objects[i][j] == 22) //graveSpwner code
			{
				zPositions.push_back({(float) j , (float) i } );
			}
		}
	}
	return zPositions;
}

std::vector<sf::Vector2f> Map::getBoxesPosition(int**& objects, int& width, int& height)
{
	std::vector<sf::Vector2f> bPositions;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (objects[i][j] == 19) //box
			{
				bPositions.push_back({ (float)j , (float)i });
			}
		}
	}
	return bPositions;
}

std::vector<sf::Vector2f> Map::getSwitchPositions(int**& objects, int& width, int& height)
{
	std::vector<sf::Vector2f> swtPositions;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (objects[i][j] == 40) //switchClose
			{
				swtPositions.push_back({ (float)j , (float)i });
			}
		}
	}
	return swtPositions;
}

sf::Vector2f Map::getPlayerPosition(int**& objects, int& width, int& height)
{
	bool find = false;
	sf::Vector2f pPositions;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (objects[i][j] == 23) //graveSpwner code
			{
				find = true;
				pPositions = { (float)j , (float) i };
				break;
			}
		}
		if (find)
		{
			break;
		}
	}
	return pPositions;
}

sf::Vector2f Map::getDoorPosition(int**& objects, int& width, int& height)
{
	bool find = false;
	sf::Vector2f dPositions;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (objects[i][j] == 39) //graveSpwner code
			{
				find = true;
				dPositions = { (float)j , (float)i };
				break;
			}
		}
		if (find)
		{
			break;
		}
	}
	return dPositions;
}

sf::Vector2f Map::getShopPosition(int**& objects, int& width, int& height)
{
	bool find = false;
	sf::Vector2f sPositions;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (objects[i][j] == 44) //graveSpwner code
			{
				find = true;
				sPositions = { (float)j , (float)i };
				break;
			}
		}
		if (find)
		{
			break;
		}
	}
	return sPositions;
}

//contructor & destructor
Map::Map()
{
	this->initTexture();
	this->initSprite();
}

Map::~Map()
{
	delete(this->textureDirt);
	delete(this->spriteDirt);
	delete(this->bg);
	delete(this->bgSprite);
}
