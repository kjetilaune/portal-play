#include "LocalPlayer.h"
#include "RemotePlayer.h"
#include "bullet.h"
#include "player.h"

class GameStateController{
	Bullet *localBullet = NULL;
	Bullet *remoteBullet = NULL;
	LocalPlayer *localPlayer;
	RemotePlayer *remotePlayer;

public:
	GameStateController(LocalPlayer *localPlayer,
						RemotePlayer *remotePlayer);

	void draw();
	bool is_local_player_hit();

	//0 = no animation, 1 = local, 2 = remote
	int hit_animation = 0;
};