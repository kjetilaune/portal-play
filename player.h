#include <iostream>

using namespace std;

class Player{
	string name;
	int lives;
	//vector<Weapon> weapons;

public:
	Player();
	Player(string);
	string get_name(){return name;}
	int decrease_lives();
	int increase_lives();
		
};