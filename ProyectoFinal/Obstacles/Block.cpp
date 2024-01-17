#include "Block.h"
#include "../Scene.h"
Block::Block(Player* player, Vector3 const& pos, Scene* scene) : 
	Obstacle(player, pos),
	speed(27),
	direction(Vector3(player->getPosition().x - pos.x, 0, player->getPosition().z - pos.z).getNormalized()) {
	BoundingBox area((pos + player->getPosition()) / 2, (player->getPosition() - pos).magnitude() * 1.3);
	bloque = new RigidBody(scene->getPxPhysics(), scene->getPxScene(), pos, physx::PxActorType::eRIGID_DYNAMIC, createRegularShape(physx::PxGeometryType::eBOX, 2), 55, Vector4(1, 0, 0, 1), -1, area);
	
}

Block::~Block() {
	delete bloque; bloque = nullptr;
}

void Block::setPosition(Vector3 const&) {}

Vector3 Block::getPosition() {
	return bloque->getPosition();
}

void Block::update(double t) {
	bloque->setVelocity(direction * speed);
}
