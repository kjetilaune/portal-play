#include "GameStateController.h"

GameStateController::GameStateController(LocalPlayer *localPlayer,
						RemotePlayer *remotePlayer){
	this->localPlayer = localPlayer;
	this->remotePlayer = remotePlayer;
}

void GameStateController::draw(){

	//Check to see if local player wants to shoot
	if (localBullet == NULL){
		if (localPlayer->is_fire_button_pushed()){
			FaceData fd = localPlayer->getFaceData();
			localBullet = new Bullet(fd.center.x, fd.center.y, fd.center.z);
		}
	}
	else{
		localBullet->draw(-10);
		if (localBullet->z < -180){
			delete localBullet;
			localBullet = NULL;
		}
	}

	//Check to see if opponent has shot a bullet
	if (remoteBullet == NULL){
		//Has shot bullet
		if (remotePlayer->shoot == 1){
			//Make sure that it shoots only once
			remotePlayer->shoot = 0;
			FaceData fd = remotePlayer->getFaceData();
			remoteBullet = new Bullet(-fd.center.x, fd.center.y, -180);
		
		}
	}
	else{
		remoteBullet->draw(10);

		if(remoteBullet->z >= localPlayer->getFaceData().center.z){
			if (is_local_player_hit()){
				//Tell remote player that local got hit and set animation 1 flag
				localPlayer->hit = 1;
				this->hit_animation = 1;

				//So no surprises arise after animation
				delete remoteBullet;
				remoteBullet = 0;
				delete localBullet;
				localBullet = 0;
			}
			delete remoteBullet;
			remoteBullet = NULL;
		}
	}

	//This player hit the other one
	if (remotePlayer->hit == 1){
		
		delete remoteBullet;
		remoteBullet = 0;
		delete localBullet;
		localBullet = 0;
		
		//Reset 'hit' flag
		remotePlayer->hit = 0;
		//Set animation 2 flag
		this->hit_animation = 2;
	}
  
  localPlayer->get_selection_direction();
}

bool GameStateController::is_local_player_hit(){
	float x = remoteBullet->x;
	float y = remoteBullet->y;
	FaceData fd = localPlayer->getFaceData();
	if (x < fd.topright.x && x > fd.topleft.x){
		if (y < fd.topleft.y && y > fd.downleft.y){
			return true;
		}
	}
	return false;
}






