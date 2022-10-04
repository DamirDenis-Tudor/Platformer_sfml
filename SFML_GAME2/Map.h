#ifndef MAP_H_
#define MAP_H_

class Map
{
private:

	//tiles
	std::vector<sf::IntRect> *tiles;

	//sprite & texture
	sf::Texture* textureDirt;
	sf::Sprite* spriteDirt;

	sf::Texture* textureObjects;
	sf::Sprite* spriteObjects;

	sf::Texture* bg;
	sf::Sprite *bgSprite;

	//init tiles
	void initTexture();
	void initSprite();

public:
	//update
	void renderMapLayer1(sf::RenderTarget *target , int**& map , int**& objects ,  int& width, int& height);
	void renderMapLayer2(sf::RenderTarget* target, int**& objects, int& width, int& height);

	//spwner zombies
	std::vector<sf::Vector2f> getZombiesPosition(int**& objects, int& width, int& height);
	std::vector<sf::Vector2f> getBoxesPosition(int**& objects, int& width, int& height);
	std::vector<sf::Vector2f> getSwitchPositions(int**& objects, int& width, int& height);
	sf::Vector2f getPlayerPosition(int**& objects, int& width, int& height);
	sf::Vector2f getDoorPosition(int**& objects, int& width, int& height);
	sf::Vector2f getShopPosition(int**& objects, int& width, int& height);

	//contructor destructor
	Map();
	~Map();
};

#endif
