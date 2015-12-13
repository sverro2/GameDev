#pragma once
#include "BehaviourFactory.h"
#include "Camera.h"
#include "CollidableBehaviour.h"
#include "PlayerCollidableBehaviour.h"
#include "EnemyCollidableBehaviour.h"
#include "BulletCollidableBehaviour.h"
#include "HealthCollidableBehaviour.h"
#include "AmmoCollidableBehaviour.h"
#include "JumpSensorCollidableBehaviour.h"
#include "HealthSprite.h"
#include "BulletSprite.h"
#include "AmmoSprite.h"
#include "GunSprite.h"


BehaviourFactory::BehaviourFactory(SDL_Renderer* sdl_renderer, int screenwidth, int screenheight)
{
	renderer = sdl_renderer;
	screenWidth = screenwidth;
	screenHeight = screenheight;
	camera = new Camera(screenHeight, screenwidth);
	sprites = std::vector<Sprite*>();

	GroundSprite* groundSprite = new GroundSprite(renderer);
	groundSprite->LoadMedia("grass.png");

	GroundObstacleSprite* groundobstacleSprite = new GroundObstacleSprite(renderer);
	groundobstacleSprite->LoadMedia("grass.png");

	BarObstacleSprite* barobstacleSprite = new BarObstacleSprite(renderer);
	barobstacleSprite->LoadMedia("grass.png");

	PlantSprite* plantSprite = new PlantSprite(renderer);
	plantSprite->LoadMedia("plant.png");
	plantSprite->SetAnimationSet(EntityState::IDLE);

	PlantBossSprite* plantBossSprite = new PlantBossSprite(renderer);
	plantBossSprite->LoadMedia("plantboss.png");
	plantBossSprite->SetAnimationSet(EntityState::IDLE);

	AcornSprite* acornSprite = new AcornSprite(renderer);
	acornSprite->LoadMedia("plantboss.png");
	acornSprite->SetAnimationSet(EntityState::IDLE);

	PlayerSprite* playerSprite = new PlayerSprite(renderer);
	playerSprite->LoadMedia("sprites.png");

	HealthSprite* healthSprite = new HealthSprite(renderer);
	healthSprite->LoadMedia("HealthSprite.png");



	BulletSprite* bulletSprite = new BulletSprite(renderer);
	bulletSprite->LoadMedia("Bullet.png");

	AmmoSprite* ammoSprite = new AmmoSprite(renderer);
	ammoSprite->LoadMedia("AmmoBox.png");

	GunSprite* gun = new GunSprite(renderer);
	gun->LoadMedia("Gun.png");

	GroundLvl2Sprite* groundlvl2Sprite = new GroundLvl2Sprite(renderer);
	groundlvl2Sprite->LoadMedia("snow2.png");

	PinguinSprite* pinguinSprite = new PinguinSprite(renderer);
	pinguinSprite->LoadMedia("pinguin.png");
	pinguinSprite->SetAnimationSet(EntityState::IDLE);

	//leaks 
	TreeSprite* treeSprite = new TreeSprite(renderer);
	treeSprite->LoadMedia("tree.png");

	ShotgunSprite* shotgun = new ShotgunSprite(renderer);
	shotgun->LoadMedia("shotgun.png");

	SnowmanSprite* snowman = new SnowmanSprite(renderer);
	snowman->LoadMedia("yeti.png");
	snowman->SetAnimationSet(EntityState::IDLE);

	sprites.push_back(snowman);
	sprites.push_back(groundSprite);
	sprites.push_back(groundobstacleSprite);
	sprites.push_back(barobstacleSprite);
	sprites.push_back(plantSprite);
	sprites.push_back(plantBossSprite);
	sprites.push_back(acornSprite);
	sprites.push_back(playerSprite);
	sprites.push_back(healthSprite);
	sprites.push_back(bulletSprite);
	sprites.push_back(ammoSprite);
	sprites.push_back(gun);
	sprites.push_back(groundlvl2Sprite);
	sprites.push_back(pinguinSprite); 
	sprites.push_back(treeSprite);
	sprites.push_back(shotgun);
	registery = std::unordered_map<EntityType, DrawableBehaviour*>{
		{ EntityType::PLAYER, new PlayerDrawableBehaviour(renderer, playerSprite, screenWidth, screenHeight) },
		{ EntityType::PLANT, new AnimatedDrawableBehaviour(renderer, plantSprite, screenWidth, screenHeight) },
		{ EntityType::PLANTBOSS, new AnimatedDrawableBehaviour(renderer, plantBossSprite, screenWidth, screenHeight) },
		{ EntityType::GROUND, new StaticDrawableBehaviour(renderer, groundSprite, screenWidth, screenHeight) },
		{ EntityType::GROUND2, new StaticDrawableBehaviour(renderer, groundobstacleSprite, screenWidth, screenHeight) },
		{ EntityType::BAR, new StaticDrawableBehaviour(renderer, barobstacleSprite, screenWidth, screenHeight) },
		{ EntityType::HEALTH, new StaticDrawableBehaviour(renderer, healthSprite, screenWidth, screenHeight) },
		{ EntityType::AMMO, new StaticDrawableBehaviour(renderer,ammoSprite,screenWidth,screenHeight)},
		{ EntityType::WEAPON, new StaticDrawableBehaviour(renderer, gun, screenWidth, screenHeight) },
		{ EntityType::SHOTGUN, new StaticDrawableBehaviour(renderer, shotgun, screenWidth, screenHeight) },
		{ EntityType::BULLET, new StaticDrawableBehaviour(renderer, bulletSprite, screenWidth, screenHeight) },
		{ EntityType::ACORN, new AnimatedDrawableBehaviour(renderer, acornSprite, screenWidth, screenHeight) },
	//	{ EntityType::CHEATLOAD, new CheatLoadDrawableBehaviour(renderer, playerSprite, screenWidth, screenHeight) },	
	//level2
		{ EntityType::GROUNDLVL2, new StaticDrawableBehaviour(renderer, groundlvl2Sprite, screenWidth, screenHeight) },
		{ EntityType::PINGUIN, new AnimatedDrawableBehaviour(renderer, pinguinSprite, screenWidth, screenHeight) },
		{ EntityType::SNOWMAN, new AnimatedDrawableBehaviour(renderer, snowman, screenWidth, screenHeight) },
		{ EntityType::PLAYERSPRITE, new AnimatedDrawableBehaviour(renderer, playerSprite, screenWidth, screenHeight) }

	};

	

	collideRegistery = std::unordered_map < EntityType, CollidableBehaviour* > {
		{ EntityType::PLAYER, new PlayerCollidableBehaviour()},
		{ EntityType::PLANT, new EnemyCollidableBehaviour() },
		{ EntityType::PLANTBOSS, new EnemyCollidableBehaviour() },
		{ EntityType::BULLET, new BulletCollidableBehaviour() },
		{ EntityType::ACORN, new BulletCollidableBehaviour() },
		{ EntityType::PINGUIN, new EnemyCollidableBehaviour() },
		{ EntityType::HEALTH, new HealthCollidableBehaviour() },
		{ EntityType::AMMO, new AmmoCollidableBehaviour() },
		{ EntityType::JUMP, new JumpSensorCollidableBehaviour()},
		{ EntityType::SNOWMAN, new EnemyCollidableBehaviour() },
	};

	IdleCommand* idle = new IdleCommand();
	DefaultPatrolCommand* patrol = new DefaultPatrolCommand();

	defaultComamnds = std::unordered_map<EntityState, BaseCommand*> {
		{ EntityState::IDLE, idle }
	};

	plantComamnds = std::unordered_map<EntityState, BaseCommand*> {
		{ EntityState::IDLE, patrol },
		{ EntityState::PATROL, idle }
	};

	moveRegistery = std::unordered_map < EntityType, MoveableBehaviour* > {
		{ EntityType::ACORN, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::AMMO, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::BAR, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::BULLET, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::GROUND, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::GROUND2, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::GROUNDLVL2, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::HEALTH, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::PINGUIN, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::PLANT, new PlantMoveableBehaviour(plantComamnds) },
		{ EntityType::PLAYER, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::PLAYERSPRITE, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::PLANTBOSS, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::SHOTGUN, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::SNOWMAN, new MoveableBehaviour(defaultComamnds) },
		{ EntityType::WEAPON, new MoveableBehaviour(defaultComamnds) }
	};

}



SDL_Renderer* BehaviourFactory::GetRenderer(){
	return renderer;
}


BehaviourFactory::~BehaviourFactory()
{
	for each(auto var in sprites){
		delete var;
	}

	for each (auto var in registery)
	{
	
		delete (var.second);

	}
	registery.clear();

	for each (auto var in collideRegistery)
	{
		delete var.second;

	}
	collideRegistery.clear();
	delete camera;
}

DrawableBehaviour* BehaviourFactory::CreateDrawableBehaviour(EntityType type)
{
	DrawableBehaviour* behaviour = registery.at(type)->EmptyClone();
	behaviour->SetCamera(camera);
	return behaviour;
}

CollidableBehaviour* BehaviourFactory::CreateCollidableBehaviour(EntityType type)
{
	CollidableBehaviour* behaviour = collideRegistery.at(type)->EmptyClone();
	return behaviour;
}

MoveableBehaviour* BehaviourFactory::CreateMoveableBehaviour(EntityType type)
{ 
	MoveableBehaviour* behaviour = moveRegistery.at(type)->EmptyClone();
	return behaviour;
}

void BehaviourFactory::ClearCamera(){
	camera->Init(nullptr, 0, 0);
}
void BehaviourFactory::SetLevelToCamera(Player* player,double levelWidth,double levelheight){
	camera->Init(player, levelWidth, levelheight);
}