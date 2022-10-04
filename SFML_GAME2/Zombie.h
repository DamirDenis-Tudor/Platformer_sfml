#ifndef ZOMBIE_H_
#define ZOMBIE_H_

enum movementZombie { IDLEZ = 0, WALKZ, ATTACKZ, DEADZ };

#define mapWidth 48
#define damegeBush 25
#define water 31
#define spikes 38

class Zombie{

protected:
	//texture & sprite
	bool type;
	sf::Texture* texture;
	sf::Sprite* sprite;

	//game physics
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f spawnPosition;

	//frezze & attackfinish
	bool freeze;
	bool attackFinish;

	//init
	void setPhisics();
	void setTexture(bool type);
	void setSprite(sf::Vector2f position);

	//animation
	float maxTime;
	int frameIndexIdle;
	int frameIndexWalk;
	int frameIndexAttack;
	int frameIndexDead;

	bool dead;
	bool deadStatus;

	float pauseTime;
	float time;
	void animation(movementZombie move, bool reverse, float deltaTime);

	//bool phisics

	bool groundCollision;
	bool falling;
	bool wasFalling;
	bool waiting;

	public:

	bool zombieBoxCol;
	bool leftCollision;
	bool rightCollision;
	bool blocked;
	bool leftBoxCollision;
	bool rightBoxCollision;
	bool bottomBoxCollision;

	//get
	sf::Vector2f getPosition();
	bool getFreezeStatus();
	int getAttackIndex();
	bool getWaitingStatus();
	bool getGroundStatus();
	sf::Vector2f getVelocity();
	bool getFallingStatus();
	bool getBlockedStatus();
	bool getDeadStatus();
	sf::Vector2f getSpawnPosition();

	//set
	void setVelocityHorizontally(float velocity);
	void setDeadStatus(bool val); 
	void setWaitingStatus(bool val);

	//restart
	void restart();

	bool reverse;
	sf::Vector2f direction;

	bool prevFreezeStatus;//for frezze it takes 6 frame -> i don't want to decrese shields at every freeze frame
	
	//render & update
	bool update(int**& map, sf::Vector2f playerPosition, bool playerAtack, bool groundStatus, bool shieldStatus , float deltaTime); // RETURN BOOL FOR PLAYER DEAD ANIMATION
	void updateTrapCollision(int**& objects);

	void render(sf::RenderTarget* target);

	//contructor and destructor
	Zombie(sf::Vector2f position , bool type);
	~Zombie();

};

#endif