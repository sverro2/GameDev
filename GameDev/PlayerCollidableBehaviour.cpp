#include "PlayerCollidableBehaviour.h"


PlayerCollidableBehaviour::PlayerCollidableBehaviour()
{
}


PlayerCollidableBehaviour::~PlayerCollidableBehaviour()
{
}
void PlayerCollidableBehaviour::Hit(CollidableBehaviour* cb){
	
	if (cb){
		switch (cb->GetActor()->GetType()){
		case EntityType::BULLET:
			break;
			
		default:

			ent->SetHealth(ent->GetHealth() - cb->GetActor()->GetDamage());
			//TODO different sound
			ent->SetNumFootContacts(ent->GetNumFootContacts() + 1);

		

			break;
		}
	}
	else{
		ent->SetNumFootContacts(ent->GetNumFootContacts() + 1);

	}
}

void PlayerCollidableBehaviour::Unhit(CollidableBehaviour* cb){
	if (cb){
		switch (cb->GetActor()->GetType()){
		case EntityType::BULLET:
			break;

		default:
			ent->SetNumFootContacts(ent->GetNumFootContacts() - 1);
			break;
		}
	}
	else{
		ent->SetNumFootContacts(ent->GetNumFootContacts() - 1);
	}
}
CollidableBehaviour* PlayerCollidableBehaviour::EmptyClone(){
	return new PlayerCollidableBehaviour();
}