#include "Map.h"

//init

void Map::initTexture()
{
	this->bg = new sf::Texture;
	this->bg->loadFromFile("sprites/BG.png");

	this->texture = new sf::Texture;
	this->texture->loadFromFile("sprites/tiles.png");
}

void Map::initSprite()
{
	this->bgSprite = new sf::Sprite;
	this->bgSprite->setTexture(*this->bg);

	this->sprite = new sf::Sprite;
	this->sprite->setTexture(*this->texture);
}

//update
void Map::renderMap(sf::RenderTarget* target, char**& map,  char **&objects ,  int& width, int& height)
{
	target->draw(*this->bgSprite);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			switch (map[i][j])
			{

			case '1': //platform 1
				this->sprite->setTextureRect(sf::IntRect{ 128 , 438, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case '2': //platform 2
				this->sprite->setTextureRect(sf::IntRect{ 256 , 438, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case '3': //platform 3
				this->sprite->setTextureRect(sf::IntRect{ 384 , 438, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;

				//dirt bump level1
			case 'x': // dirt1
				this->sprite->setTextureRect(sf::IntRect{ 128 , 694 , 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'c':
				this->sprite->setTextureRect(sf::IntRect{ 256 , 694, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;

			case 'b':
				this->sprite->setTextureRect(sf::IntRect{ 128 , 310, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'n':
				this->sprite->setTextureRect(sf::IntRect{ 256 , 310, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;

				//dirt bump level 2
			case 'd':
				this->sprite->setTextureRect(sf::IntRect{ 256 , 566, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'f':
				this->sprite->setTextureRect(sf::IntRect{ 384 , 566, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'g':
				this->sprite->setTextureRect(sf::IntRect{ 0 , 694, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;

				//dirt bump level 3
			case 'e':
				this->sprite->setTextureRect(sf::IntRect{ 0 , 310, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'r':
				this->sprite->setTextureRect(sf::IntRect{ 0 , 566, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 't':
				this->sprite->setTextureRect(sf::IntRect{ 128 , 566, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;

				//bottom dirt
			case 'z':
				this->sprite->setTextureRect(sf::IntRect{ 384 , 310, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'v':
				this->sprite->setTextureRect(sf::IntRect{ 384 , 694, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'm':
				this->sprite->setTextureRect(sf::IntRect{ 0 , 438, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			}
			
			switch (objects[i][j])
			{
			case 'G':
				this->sprite->setTextureRect(sf::IntRect{ 86 , 76, 182 , 90 });
				this->sprite->setScale({ 0.65934065f , 0.65934065f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'T':
				this->sprite->setTextureRect(sf::IntRect{ 0 , 822, 286 , 239 });
				this->sprite->setScale({ 0.753138075313807f , 0.753138075313807f });
				this->sprite->setPosition({ j * 60.f ,  i * 60.f });
				this->sprite->move({ 0.f,-120.f });
				target->draw(*this->sprite);
				break;
			case 'b':
				this->sprite->setTextureRect(sf::IntRect{ 256 , 182, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'B':
				this->sprite->setTextureRect(sf::IntRect{ 0 , 182, 128 , 128 });
				this->sprite->setScale({ 0.46875f , 0.46875f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 't':
				this->sprite->setTextureRect(sf::IntRect{ 388 , 0, 53 , 76 });
				this->sprite->setScale({ 0.78947368421052f , 0.78947368421052f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'x':
				this->sprite->setTextureRect(sf::IntRect{ 359 , 76, 106 , 106 });
				this->sprite->setScale({ 0.5660377358490f , 0.5660377358490f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			case 'p':
				this->sprite->setTextureRect(sf::IntRect{ 268 , 76, 91 , 93 });
				this->sprite->setScale({ 0.6451612903f , 0.6451612903f });
				this->sprite->setPosition({ j * 60.f , i * 60.f });
				target->draw(*this->sprite);
				break;
			}
		}
	}
}

//contructo & destructor
Map::Map()
{
	this->initTexture();
	this->initSprite();
}

Map::~Map()
{
	delete(this->texture);
	delete(this->sprite);
	delete(this->bg);
	delete(this->bgSprite);
}
