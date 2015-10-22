#include "Game.h"
#include "header_loader.h"

Game::Game()
{
	//gameManager = GameStateManager();
	//running = true;
	//if (SDL_Init(SDL_INIT_VIDEO) < 0)
	//{
	//	//TODO
	//}
	//// Create the window where we will draw.
	//window = SDL_CreateWindow("SDL_RenderClear",
	//	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	//	512, 512, 0);
	//// We must call SDL_CreateRenderer in order for draw calls to affect this window.
	//renderer = SDL_CreateRenderer(window, -1, 0);

	//// Select the color for drawing. It is set to red here.
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	//// Clear the entire screen to our selected color.
	//SDL_RenderClear(renderer);

	//gameLoop();

	gsm = GameStateManager::Instance();
	gsm->init("GameDev", ScreenWidth, ScreenHeight, fullScreen);
	//Non-threaded
	this->gameLoop(gsm);

	gsm->cleanup();
}


Game::~Game()
{
	//delete window;
	//delete renderer;
}

void Game::inputManager(GameStateManager* gsm)
{
	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_QUIT)
			gsm->quit();
	}
}

void Game::setUpBox2D()
{

}

void Game::gameLoop(GameStateManager* gsm)
{	
	int lastTime = SDL_GetTicks() - 1;
	while (gsm->running())
	{
		//Checks if windows is not closed
		inputManager(gsm);
		//Time to be used by behaviours
	
		//TODO UPDATE Behaviours with Time
		int time = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();
	
		// max 60 fps	
		if (1000.0 / 60 > time){
			SDL_Delay((1000.0 / 60) - time);
		}

	}
	SDL_Quit();
}