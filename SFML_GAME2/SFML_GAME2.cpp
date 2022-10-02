#include"GameEngine.h"


int main()
{
    Game game;

	while (game.isWindow() )
	{
		game.update();
		
		game.render();
	}

	return 0;
}

