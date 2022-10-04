#pragma once

#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

#define mapWidth 48
#define mapHeight 27

#define damegeBush 25
#define water 31
#define spikes 38

#define coin 33
#define diamond 37
#define health 34
#define shield 35
#define attackAbility 36
#define max 4

enum movement { IDLE, WALK , RUN , JUMP, ATTACK , JUMPATTACK ,DEAD };

class Player
{
private:


	//sprite & texture for info bars
	sf::Texture* infoTexture;
	sf::Sprite* infoSprite;

	//text font
	sf::Font* font;
	sf::Text* text;

	//init
	void initCapabilities();
	void initInfo();
	void initText();
	void initFont();
	void setPhisics();
	void setTexture();
	void setSprite();

	//animation
	float maxTime;
	float time;

	int frameIndex;
	int frameIndexJumping;
	int frameIndexDead;
	int frameIndexAttack;
	int frameIndexJumpAttack;
	bool reverse;

	void animation(movement move, bool reverse , float deltaTime);

	//respawn
	void respawn();

	//bool phisics
	bool leftCollision;
	bool rightCollision;
	bool groundCollision;
	bool topCollision;
	bool isJumping;
	float jumpHeight;
	float currentGroungHeight;
	bool maxHeightReached;
	bool falling;



public:
	//player info
	int coins;
	int diamonts;
	int shields;
	int lives;
	int abilities;

	//bool box col
	bool rightBoxCol;
	bool leftBoxCol;
	bool topBoxColision;
	bool bottomBoxCollision;

	//texture & sprite
	sf::Texture* texture;
	sf::Sprite* sprite;

	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f spawnPosition;

	//restart
	void restart();

	
	//zombie detection mecanism
	sf::Vector2f getPos();
	unsigned int getGroundStatus();
	sf::Vector2f getVelocity();
	sf::Vector2i getMapPosition();
	bool getAttackStatus();
	bool getShieldStatus();
	bool getLivesStatus();
	bool getJumpingStatus();
	bool getFallingStatus();

	void decShieds();

	//set ground col -> it's for box
	void setVelocity(sf::Vector2f velocity);

	void leftBoxColision();
	void rightBoxColision();
	//set here -> if not work move box to dirt layer

	bool deadStatus;
	bool shieldBreakStatus;

	//render & update
	void updateMovement(int**&map , float deltaTime);
	void updateInfo(int**&objects);
	void updateObjectsCollision(int**& objects);

	void renderPlayer(sf::RenderTarget* target );
	void renderPlayerInfo(sf::RenderTarget* target, sf::Vector2f viewPos);
	
	//contructor & destructor
	Player(sf::Vector2f position);
	~Player();
};