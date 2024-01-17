#include "Scene.h"

Scene::Scene(physx::PxPhysics* gPhysics, physx::PxScene* mScene) : 
	_gPhysics(gPhysics),
	_mScene(mScene),
	_mForceSystem(new ForceSystem()) {
}

Scene::~Scene() {
	delete _mForceSystem; _mForceSystem = nullptr;
	for (auto& ps : _mParticleSystems) {
		delete ps; ps = nullptr;
	}
	for (auto& act : _mActors) {
		delete act; act = nullptr;
	}
}

void Scene::simulate(float t) {
	updateActors(t);

	_mForceSystem->integrate(t);

	for (ParticleSystem*& ps : _mParticleSystems)
		ps->integrate(t);
}

void Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	for (Actor*& act : _mActors)
		act->keyPress(key);
}
void Scene::keyRelease(unsigned char key, const physx::PxTransform& camera) {
	for (Actor*& act : _mActors)
		act->keyRelease(key);
}

void Scene::updateActors(float t) {
	for (auto part_it = _mActors.begin(); part_it != _mActors.end(); ) {
		if ((*part_it)->integrate(t)) {
			++part_it;
		}
		else {
			_mForceSystem->getRegistry()->deleteParticleRegistry(*part_it);
			(*part_it)->kill();
			delete (*part_it);
			(*part_it) = nullptr;
			part_it = _mActors.erase(part_it);
		}
	}
}

physx::PxPhysics* Scene::getPxPhysics() {
	return _gPhysics;
}

physx::PxScene* Scene::getPxScene() {
	return _mScene;
}

ForceGenerator* Scene::addForce(ForceGenerator* fg) {
	_mForceSystem->addForce(fg);
	return fg;
}

ParticleSystem* Scene::addParticleSystem(ParticleSystem* fg) {
	_mParticleSystems.push_back(fg);
	return fg;
}

ParticleForceRegistry* Scene::getRegistry() {
	return _mForceSystem->getRegistry();
}
