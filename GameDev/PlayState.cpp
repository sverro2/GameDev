#include "PlayState.h"
PlayState::PlayState(int lvl){
	levelToLoad = lvl;
}
void PlayState::Init(GameStateManager* gsm)
{

	levelConfig = LevelConfig();
 	this->gsm = gsm;

	this->gameOver = false;
	currentLevel = nullptr;
	//TODO LOAD PLAYER FROM FILE
	player = new Player();
	
	accumulatedDtWeapon = 0;
	
	hud = new HUD();
	//SetCurrentLevel(LevelFactory::GetFirstLevel(this));
	SetCurrentLevel(LevelFactory::GetSpecificLevel(this, levelToLoad));
	// flush userinput to prevent crash during loadscreen

	//SDL_SetRenderDrawColor(gsm->GetBehaviour()->GetRenderer(), 80, 30, 30, 255);

	
	std::cout << "PlayState \n";
	hud->Initialize(gsm->GetBehaviour()->GetRenderer(), player);
}

void PlayState::InitStartLevel(int lvl){
	SetCurrentLevel(LevelFactory::GetSpecificLevel(this, lvl));
}

void PlayState::GameOver(){
	//SoundBank::GetInstance()->StopMusic(); //not needed
	currentLevel->GetPlayer()->AddPlayTime(currentLevel->GetTimer()->GetCurrentMinutes(), currentLevel->GetTimer()->GetCurrentSeconds());
	gsm->CreateGameState(GameStateType::GameOverState,0);
}

void PlayState::Victory(){
	levelConfig.SaveLevelProgress("Level" + to_string(currentLevel->GetLevelId() + 1));
	currentLevel->GetPlayer()->AddPlayTime(currentLevel->GetTimer()->GetCurrentMinutes(), currentLevel->GetTimer()->GetCurrentSeconds());
	gsm->CreateGameState(GameStateType::VictoryState,0);
}

void PlayState::LoadGame()
{
	
}

void PlayState::SetFileToLoad(std::string fileName)
{
	std::cout << "SetFileToLoad not implemented yet";
}

void PlayState::Pause()
{
	gsm->CreateGameState(GameStateType::PauseState,0);
}

void PlayState::Resume()
{
	SoundBank::GetInstance()->PlaySFX(SoundEffectType::LETSROCK);
	SoundBank::GetInstance()->PlayBGM(SoundBgmType::REDALERT1);

	//if screen changed, reload all layerContainers
	currentLevel->GetParallaxBackGround()->CheckIfScreenSizeChanged();
	hud->ResumeChecks();
}

void PlayState::HandleMouseEvents(SDL_Event mainEvent)
{
//	std::cout << "Mouse events not implemented yet";
}

void PlayState::HandleKeyEvents(std::unordered_map<SDL_Keycode, bool>* _events)
{
	if (currentLevel->GetPlayer() != nullptr){
		b2Vec2 vel = currentLevel->GetPlayer()->GetBody()->GetLinearVelocity();

		bool jump = false;
		bool pause = false;
		float x = vel.x;
		float y = vel.y;
		float impulse;
		for (auto it = _events->begin(); it != _events->end(); ++it){

			if (it->second)
			{
				switch (it->first)
				{
				case SDLK_w:
					if (currentLevel->GetPlayer()->GetNumFootContacts() >  0){
						if (!(currentLevel->GetPlayer()->GetJumpTimeOut() > 0)){

							jump = true;
							impulse = 200; //temp
							//SoundBank::GetInstance()->Play(SoundEffectType::CORRECT);

							currentLevel->GetPlayer()->GetBody()->ApplyLinearImpulse(b2Vec2(0, -impulse), currentLevel->GetPlayer()->GetBody()->GetWorldCenter(), true);
							currentLevel->GetPlayer()->SetJumpTimeOut(15);

							//TODO fix bounce effect -> jumping higher than intended! Not good.
						}
				

					}
					break;
				case SDLK_a:
					currentLevel->GetPlayer()->SetState(EntityState::WALKINGLEFT);
					currentLevel->GetPlayer()->SetFlipped(true);
					x = -25;

					break;
				case SDLK_s:
					//disabled for player
					break;
				case SDLK_d:
					currentLevel->GetPlayer()->SetState(EntityState::WALKINGRIGHT);
					currentLevel->GetPlayer()->SetFlipped(false);
					x = 25;
					break;
				case SDLK_SPACE: //temp changed W -> SPACE =P. Until remapping
					if (currentLevel->GetPlayer()->GetCurrentWeapon()->Shoot(currentLevel->GetEntityFactory(),
						accumulatedDtWeapon, currentManipulatorSpeed)) 
					{
						accumulatedDtWeapon = 0;
					}
					break;
				case SDLK_UP:
					currentLevel->GetPlayer()->GetCurrentWeapon()->SetYVec(-100);
					break;

				case SDLK_DOWN:
					currentLevel->GetPlayer()->GetCurrentWeapon()->SetYVec(+100);
					break;

				case SDLK_LEFT:
					currentLevel->GetPlayer()->GetCurrentWeapon()->SetXVec(-100);
					break;

				case SDLK_RIGHT:
					currentLevel->GetPlayer()->GetCurrentWeapon()->SetXVec(+100);
					break;

				case SDLK_1:
					currentLevel->GetPlayer()->SwitchWeapon(0);
					break;
				case SDLK_2:
					currentLevel->GetPlayer()->SwitchWeapon(1);
					break;
				case SDLK_3:
					currentLevel->GetPlayer()->SwitchWeapon(2);
					break;
				case SDLK_4:
					currentLevel->GetPlayer()->SwitchWeapon(3);
					break;
				case SDLK_5:
					currentLevel->GetPlayer()->SwitchWeapon(4);
					break;
				case SDLK_6:
					currentLevel->GetPlayer()->SwitchWeapon(5);
					break;
				case SDLK_7:
					currentLevel->GetPlayer()->SwitchWeapon(6);
					break;
				case SDLK_8:
					currentLevel->GetPlayer()->SwitchWeapon(7);
					break;
				case SDLK_9:
					currentLevel->GetPlayer()->SwitchWeapon(8);
					break;
				
				case SDLK_ESCAPE:
					pause = true;
					break;
				case SDLK_l:
					SetCurrentLevel(LevelFactory::GetNextLevel(currentLevel, this));
					break;
				case SDLK_k: //TODO cheat mode and not normal key for normal player
					Victory();
					break;
				}
			}
			else
			{
				switch (it->first)
				{
				case SDLK_w:

					break;
				case SDLK_a:
					if (currentLevel->GetPlayer()->GetState() == EntityState::WALKINGLEFT)
						currentLevel->GetPlayer()->SetState(EntityState::IDLE);
					break;
				case SDLK_s:
					
					break;
				case SDLK_d:
					if (currentLevel->GetPlayer()->GetState() == EntityState::WALKINGRIGHT)
						currentLevel->GetPlayer()->SetState(EntityState::IDLE);
					break;
				case SDLK_UP:
					if (currentLevel->GetPlayer()->GetCurrentWeapon()->GetVec().y == -100){
						currentLevel->GetPlayer()->GetCurrentWeapon()->SetYVec(0);
					}

					break;
				case SDLK_DOWN:
					if (currentLevel->GetPlayer()->GetCurrentWeapon()->GetVec().y == 100){
						currentLevel->GetPlayer()->GetCurrentWeapon()->SetYVec(0);
					}
				
					break;

				case SDLK_LEFT:
					if (currentLevel->GetPlayer()->GetCurrentWeapon()->GetVec().x == -100){
						currentLevel->GetPlayer()->GetCurrentWeapon()->SetXVec(0);
					}

					break;

				case SDLK_RIGHT:
					if (currentLevel->GetPlayer()->GetCurrentWeapon()->GetVec().x == 100 && currentLevel->GetPlayer()->GetCurrentWeapon()->GetVec().y != 0){
						currentLevel->GetPlayer()->GetCurrentWeapon()->SetXVec(0);
					}

					break;

				}
			}

		}
		
		if (!jump){
			//temporary solution. Makes controlling player lot easier
			if (currentLevel->GetPlayer()->GetState() == EntityState::IDLE) { 
				x = 0;
			}
			vel.Set(x, y);
			//	currentLevel->GetPlayer()->GetBody()->ApplyForce(vel, currentLevel->GetPlayer()->GetBody()->GetWorldCenter(), true);
			currentLevel->GetPlayer()->GetBody()->SetLinearVelocity(vel);
		}
	
		if (currentLevel->GetPlayer()->GetJumpTimeOut() > 0){
			currentLevel->GetPlayer()->SetJumpTimeOut(currentLevel->GetPlayer()->GetJumpTimeOut() - 1);
		}

		if (pause){
			Pause();
		}
	}
}

void PlayState::HandleTextInputEvents(SDL_Event event) {

}

void PlayState::Update(float dt, float manipulatorSpeed) {
	accumulatedDtWeapon += dt; //accumulate Dt
	currentManipulatorSpeed = manipulatorSpeed;

	currentLevel->Update(dt, manipulatorSpeed);
}

void PlayState::Draw(float dt, float manipulatorSpeed)
{
	//TODO use manipulatorSpeed

	currentLevel->GetParallaxBackGround()->Draw();
	currentLevel->GetDrawableContainer()->Draw(dt, manipulatorSpeed);
	hud->Draw(dt, manipulatorSpeed);
}

Level* PlayState::GetCurrentLevel()
{
	return this->currentLevel;
}

void PlayState::SetCurrentLevel(Level* lvl)
{
	BehaviourFactory* bf = gsm->GetBehaviour();
	if (currentLevel != nullptr){
		delete currentLevel;
		currentLevel = nullptr;
	}

	this->currentLevel = lvl;// LevelFactory::LoadLevel(this, bf, "test");
	//Note CurrentLevel is now new level

	this->currentLevel->Init(bf);
	//LevelFactory::SaveLevel(lvl, "test");
	gsm->SetBehaviour(bf);
	player = this->currentLevel->SetPlayer(player);
	this->gsm->GetBehaviour()->SetLevelToCamera(player, currentLevel->GetLvlHeight(), currentLevel->GetLvlWidth());

	SoundBank::GetInstance()->PlayBGM(SoundBgmType::REDALERT1);


	this->currentLevel->GetParallaxBackGround()->InitializeFixXPos(); //use this to fix XPos after the player is set in the current level
	this->hud->SetTimer(currentLevel->GetTimer());

}


Player* PlayState::GetPlayer()
{
	return this->player;
}


void PlayState::Cleanup()
{
	gsm->GetBehaviour()->ClearCamera();
	delete player;
	delete currentLevel;
	delete hud;

	player = nullptr;
	currentLevel = nullptr;
	hud = nullptr;
}

PlayState::~PlayState()
{
	this->Cleanup();
}

