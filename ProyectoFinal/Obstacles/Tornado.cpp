#include "Tornado.h"
#include "../Scene.h"

Tornado::Tornado(Player* player, Vector3 const& pos, Scene* scene) :
	Obstacle(player, pos),
	particles(new ParticleSystem(scene->getPxPhysics(), scene->getPxScene())),
	forceGen(new MovableWhirlwindForceGenerator(50.0f, 2.0f, 300.0f, 0.5f, BoundingBox(pos, 2.5))),
	effectArea(pos, 2.5),
	speed(25),
	myScene(scene),
	moveDir(Vector3(player->getPosition().x - pos.x, 0, player->getPosition().z - pos.z).getNormalized()){
	gen = new UniformParticleGenerator("TornadoParticles", 1, effectArea, Vector3(0), Vector3(0), Vector3(0.5), Vector3(0));
	particles->addParticleGenerator(gen);
	torn_core = new Particle(Vector3(pos.x, pos.y - 2.5f, pos.z), 30, values::std_life_time, Vector4(1, 0, 0, 1));
	gen->setParticle(torn_core);
	gen->initializeForces(scene->getRegistry());
	particles->initializeForces(scene->getRegistry());
	scene->addForce(forceGen);
	particles->addForce(forceGen);
	scene->getRegistry()->addRegistry(player, forceGen);
}

Tornado::~Tornado() {
	delete particles;
}

void Tornado::setPosition(Vector3 const& pos) {
	for (auto& p : particles->getParticles()) {
		p->setPosition(p->getPosition() + (pos - getPosition()));
	}
	effectArea.moveOriginTo(pos);
	forceGen->setPosition(pos);
	torn_core->setPosition(pos);
	gen->moveLimitsTo(pos);
}

Vector3 Tornado::getPosition() {
	return effectArea.getOrigin();
}

void Tornado::update(double t) {
	particles->integrate(t);

	Vector3 dest = _player->getPosition();
	dest.y = spawnPos.y;
	//setPosition(getPosition() + moveDir * speed * t);
	move(moveDir * speed * t);
}

void Tornado::move(Vector3 const& offset) {
	for (auto& p : particles->getParticles()) {
		p->setPosition(p->getPosition() + offset);
	}
	forceGen->setPosition(effectArea.getOrigin() + offset);
	torn_core->setPosition(effectArea.getOrigin() + offset);
	gen->moveLimitsTo(effectArea.getOrigin() + offset);
	effectArea.moveOriginTo(effectArea.getOrigin() + offset);
}
