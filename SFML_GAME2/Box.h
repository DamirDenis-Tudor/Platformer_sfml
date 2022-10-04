#ifndef BOX_H_
#define BOX_H_

class Box
{
private:
	//sprite & texture
	sf::Texture* texture;
	sf::Sprite* sprite;

	//phisics
	sf::Vector2f position;
	sf::Vector2f spawnPosition;
	sf::Vector2f velocity;
	bool groundStatus;
	bool fallingStatus;

	//init 
	void initVariables();
	void initTexture();
	void initSprite();

public:
	//
	bool leftStatus;
	bool rightStatus;

	bool leftStatusPlayer;
	bool rightStatusPlayer;
	
	std::vector<bool> leftZombiesStatus;
	std::vector<bool> rightZombiesStatus;
	std::vector<bool> topZombiesStatus;
	std::vector<bool> bottomZombiesStatus;
	
	bool topColision;
	bool bottomCollision;


	//for boxes collision
	bool bottomBoxCollision;

	bool pushedRight;
	bool pushedLeft;
	bool checked;
	bool wasMoved;

	//restart
	void restart();

	//set - get map position
	void setPosition(sf::Vector2f position);
	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	bool getFallingStatus();
	
	void repos();

	//update render
	void update(sf::Vector2f playerPos ,sf::Vector2f &playerVelocity ,std::vector<sf::Vector2f> zombiesPos , int **&map , float deltaTime , bool playerDead , bool playerJumping);
	void render(sf::RenderTarget *target);

	//contructor & destructor
	Box(sf::Vector2f position);
	~Box();
};

#endif
