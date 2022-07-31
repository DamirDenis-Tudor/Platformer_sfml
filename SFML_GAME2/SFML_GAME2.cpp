#include"GameEngine.h"


int main()
{
    Game game;

	while (game.isWindow() )
	{
		//game update
		game.update();

		//hame render
		game.render();
	}

	return 0;
}

