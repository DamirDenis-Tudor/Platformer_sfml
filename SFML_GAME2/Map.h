#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>

class Map
{
private:
	//tiles
	std::vector<sf::IntRect> *tiles;

	//sprite & texture
	sf::Texture* texture;
	sf::Sprite* sprite;

	sf::Texture* bg;
	sf::Sprite *bgSprite;

	//init tiles
	void initTexture();
	void initSprite();

public:
	//update
	void renderMap(sf::RenderTarget *target , char**& map, char **&objects,  int& width, int& height);

	//contructor destructor
	Map();
	~Map();
};

