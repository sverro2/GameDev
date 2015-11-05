#include "EntityFactory.h"


EntityFactory::EntityFactory(b2World& b2world, BehaviourFactory* _bf, DrawableContainer* _drawContainer) : world(b2world), bf(_bf), drawContainer(_drawContainer)
{
	entityRegistery =	std::unordered_map<EntityType, Entity*>{
			{ EntityType::ENTITY,new Entity() },
			{ EntityType::ACTOR, new Actor() },
			{ EntityType::NPC, new Npc() },
			{ EntityType::PLAYER, new Player() },
			{ EntityType::GROUND, new Ground() },
			{ EntityType::GROUND2, new Ground() }
	};
	b2BodyDef entDef = b2BodyDef();
	entDef.type = b2BodyType::b2_staticBody;
	entDef.fixedRotation = true;
	b2BodyDef ActorDef;
	ActorDef.type = b2BodyType::b2_dynamicBody;
	b2BodyDef NpcDef;
	NpcDef.type = b2BodyType::b2_dynamicBody;
	b2BodyDef PlayerDef;
	PlayerDef.fixedRotation = true;
	PlayerDef.type = b2BodyType::b2_dynamicBody;

	bodyRegistery = std::unordered_map<EntityType, b2BodyDef>{
			{ EntityType::ENTITY,  entDef },
			{ EntityType::ACTOR,  ActorDef },
			{ EntityType::NPC,  NpcDef },
			{ EntityType::PLAYER,  PlayerDef },
			{EntityType::GROUND, entDef},
			{ EntityType::GROUND2, entDef }
	};

}

EntityFactory::~EntityFactory()
{
	for (auto it = entityRegistery.begin(); it != entityRegistery.end(); ++it){
		delete it->second;
	}

	
	
}

Entity* EntityFactory::CreateEntity(float x, float y,float height, float width, EntityType type)
{
	Entity* ent = entityRegistery.at(type)->EmptyClone();

	ent->Init(CreateBody(x, y,height,width, type),width,height, type, bf, drawContainer);

	return ent;

}
b2Body* EntityFactory::CreateBody(float x, float y,float height,float width, EntityType type)
{
	
	b2PolygonShape boxShape;
	//transalte pixels -> units
	float xx = 1;
	float yy = 20;
	height = height / 2;
	width = width / 2;
	float ratio = (xx / yy);
	float newHeight = (height*ratio);
	float newWidth = (width*ratio);
	boxShape.SetAsBox(newHeight, newWidth, b2Vec2(newHeight, newWidth), 0);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	




	b2BodyDef bodydef = bodyRegistery.at(type);	
	bodydef.position.Set(x*ratio, y*ratio);
	b2Body* b2body = world.CreateBody(&bodydef);
	b2body->CreateFixture(&boxFixtureDef);
	b2body->SetTransform(b2Vec2(x*ratio, y*ratio),0);
	return b2body;

}
