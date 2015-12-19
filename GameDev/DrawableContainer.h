#pragma once
#include <vector>
#include "SDL.h"
#include "Container.h"
#include "DrawableBehaviour.h"


using namespace std;
class Entity;
class DrawableContainer :
	public Container
{
public:
	DrawableContainer();
	virtual ~DrawableContainer();
		
	void Add(DrawableBehaviour* behaviour);
	void Draw(float dt);
	void Delete(Entity* behaviour);
private:
	vector<DrawableBehaviour*> behaviours;
};

