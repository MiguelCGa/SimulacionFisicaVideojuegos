#include "Cannon.h"
#include "../Scene.h"

Cannon::Cannon(Player* player, Vector3 const& pos, Scene* scene) :
	Obstacle(player, pos), 
	ps(new ParticleSystem(scene->getPxPhysics(), scene->getPxScene())) {
	auto* rbg = new UniformParticleGenerator("Cannon", 0.0012, Vector3(0), Vector3(0), Vector3(0), Vector3(0));
	BoundingBox area((pos + player->getPosition()) / 2, (player->getPosition() - pos).magnitude() * 0.6);
	auto* cannon_model = new RigidBody(scene->getPxPhysics(), scene->getPxScene(), pos, physx::PxActorType::eRIGID_DYNAMIC, createRegularShape(physx::PxGeometryType::eSPHERE, 2), 100, Vector4(1, 0, 0, 1), -1, area);
	rbg->setParticle(cannon_model);
	ps->addParticleGenerator(rbg);

	scene->getPxScene()->removeActor(*cannon_model->getActor());
	Vector3 dir = Vector3(player->getPosition().x - pos.x, 0, player->getPosition().z - pos.z).getNormalized();
	dir.y = 0.2;
	dir.normalize();
	cannon_model->setVelocity(dir * 50);

	base = new RigidBody(scene->getPxPhysics(), scene->getPxScene(), pos + Vector3(0, -5, 0), physx::PxActorType::eRIGID_STATIC, createRegularShape(physx::PxGeometryType::eBOX, 3), 10, Vector4(1, 0, 0, 1), -1, BoundingBox());
}

Cannon::~Cannon() {
	delete ps; ps = nullptr;
	delete base; base = nullptr;
}

void Cannon::setPosition(Vector3 const&) {

}

Vector3 Cannon::getPosition() {
	return base->getPosition();
}

void Cannon::update(double t) {
	ps->integrate(t);
}
