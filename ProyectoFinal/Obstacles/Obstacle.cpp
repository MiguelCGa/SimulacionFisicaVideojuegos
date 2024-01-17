#include "Obstacle.h"

Obstacle::Obstacle(Player* player, Vector3 const& pos) :
	_player(player),
	spawnPos(pos) {
}

void Obstacle::update(double t) {
}
