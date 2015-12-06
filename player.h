#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>


class Player{
  std::string name;
	int lives;

public:
	Player();
	Player(std::string name);
  std::string get_name(){return name;}
	int decrease_lives();
	int increase_lives();
		
};

#endif //PLAYER_H_
