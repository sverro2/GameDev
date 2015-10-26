#pragma once

#include <SDL.h>
#include <vector>
#include "SDLInitializer.h"
#include "Level.h"
#include "LevelFactory.h"

class IGameState;

class GameStateManager
{
	private:
		float updateLength;
		int fps;
		std::vector<IGameState*> states;
		IGameState* currentState;
		bool m_running;

		static GameStateManager m_Gsm;

	public:
		bool showFps;
		GameStateManager();

		SDLInitializer* sdlInitializer;

		void Init(const char* title, int width, int height, bool fullscreen);
		void Cleanup();

		void SetFps(int fps);
		int GetFps();

		void ChangeGameState(IGameState* gameState);
		void PushGameState(IGameState* gameState);
		void PopState();

		void Update(double delta);
		void HandleEvents();
		void FlushEvents();
		void Draw();

		Level* GetLevel();
		void GetLevel(Level* lvl);

		void SetUpdateLength(float updateLength);
		float GetUpdateLength();

		void QuitGame();
		bool Running();
		void Quit();

		static GameStateManager* Instance() { return &m_Gsm; };

		virtual ~GameStateManager();
};
