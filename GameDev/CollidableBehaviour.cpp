#include "CollidableBehaviour.h"
#include "Actor.h"

CollidableBehaviour::CollidableBehaviour()
{
	
}


CollidableBehaviour::~CollidableBehaviour()
{

}
CollidableBehaviour* CollidableBehaviour::EmptyClone()
{
	return new CollidableBehaviour();
}
void CollidableBehaviour::Hit(CollidableBehaviour* cb){

	


}
void CollidableBehaviour::Unhit(CollidableBehaviour* cb){

}
Actor* CollidableBehaviour::GetActor(){
	return ent;
}
void CollidableBehaviour::Init(Actor* _ent){
	ent = _ent;
}
int CollidableBehaviour::GetHitDmg(){
	return ent->GetDamage();
}