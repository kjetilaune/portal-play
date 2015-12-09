#include "player.h"


using namespace std;

Player::Player(std::string name)
  : _name(name) {
  
  _lives = 3;
}

int Player::decrease_lives(){
	if (_lives == 0)
		return -1;
	_lives--;

	return _lives;
}

int Player::increase_lives(){
	_lives++;
	return _lives;
}

int Player::get_lives(){
	return _lives;
}