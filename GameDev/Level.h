#pragma once
#include <vector>
#include "header_loader.h"
#include "Box2D\Box2D.h"
#include "Camera.h"
#include "TileLoader.h"

class Level
{
	private:
		// stuff

	protected:
		int tileWitdh, tileHeight;
		int lvlWitdh, lvlHeight, lvlTotalTiles, lvlTotalDiffrentTiles;
		b2World* world;
		Camera* camera;
		int LevelTiles;
		SDL_Texture* tileSheet;
		std::vector<SDL_Rect> tileCrops;

		TileLoader* tileLoader;

	public:
		Level(int _lvlWidth, int _lvlHeight);
		virtual ~Level();

		virtual void SetLvlWidth(int _lvlWidth);
		virtual void SetLvlHeight(int _lvlHeight);

		SDL_Texture* GetTileSheet();

		int GetLvlWidth();
		int GetLvlHeight();
		int GetTotalTiles();
		int GetTotalDiffrentTiles();
		std::vector<SDL_Rect> getTileCrops();

		virtual void Draw() = 0;
		virtual void Update(double dt) = 0;

		virtual b2World* GetWorld();
};
