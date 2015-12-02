#include "player.h"

Player::Player(){
	lives = 3;
}

Player::Player(string name){
	this->name = name;
}

int Player::decrease_lives(){
	if (lives == 0)
		return -1;
	lives--;
	return lives;
}

int Player::increase_lives(){
	lives++;
	return lives;
}