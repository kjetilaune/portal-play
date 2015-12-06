#include "player.h"


using namespace std;

Player::Player(){
	lives = 3;
}

Player::Player(std::string name){
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
