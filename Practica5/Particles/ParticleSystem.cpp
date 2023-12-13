#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(physx::PxPhysics* gPhysics, physx::PxScene* mScene) : 
	_maxElems(50) {

	GaussianParticleGenerator* pg = new GaussianParticleGenerator("a", 1, /*BoundingBox(Vector3(0), 100.0f),*/ Vector3(0), Vector3(0), Vector3(50), Vector3(1));
	_particle_generators.push_back(pg);
	RigidBody* rb = new RigidBody(gPhysics, mScene, Vector3(0),
		physx::PxActorType::eRIGID_DYNAMIC,
		createRegularShape(physx::PxGeometryType::eBOX, 5.0f),
		0.1,
		Vector4(0.5),
		2.0,
		BoundingBox());
	mScene->removeActor(*rb->getActor());

	//Particle* rb = new Particle(Vector3(0), 1);

	pg->setParticle(rb);
}

ParticleSystem::~ParticleSystem() {
	for (Actor*& part : _particles) {
		delete part; 
		part = nullptr;
	}
	for (ParticleGenerator*& generator : _particle_generators) {
		delete generator;
		generator = nullptr;
	}
	for (ForceGenerator*& force : _force_generators) {
		delete force; 
		force = nullptr;
	}
	
}

void ParticleSystem::integrate(double t) {
	generateParticles();
	updateForces(t);
	updateParticles(t);
}

void ParticleSystem::createGeneralForce(ForceGenerator* fg) {
	_force_generators.push_back(fg);
	for (auto& p : _particles) {
		_particle_force_registry.addRegistry(p, fg);
	}
	for (auto& pg : _particle_generators) {
		if (pg->forcesInitialized()) pg->addForce(fg);
	}
}

void ParticleSystem::explosion() {
	const Vector3 origin(0);
	constexpr double duration = 2.0;
	constexpr float K = 500.0f;
	ExplosionForceGenerator* e = new ExplosionForceGenerator(origin, duration, K);
	createGeneralForce(e);
}

void ParticleSystem::generateParticles() {
	for (auto const& gen : _particle_generators) {
		if (_particles.size() <= _maxElems) 
			_particles.splice(_particles.end(), gen->generateParticles());
	}
}

void ParticleSystem::updateForces(double t) {
	_particle_force_registry.updateForces(t);
	for (auto force_it = _force_generators.begin(); force_it != _force_generators.end(); ) {
		// Non-alive forces get erased on the next iteration so registry works well
		if (!(*force_it)->isAlive()) {
			delete (*force_it);
			(*force_it) = nullptr;
			force_it = _force_generators.erase(force_it);
		}
		else {
			(*force_it)->updateTime(t);
			++force_it;
		}
	}
}

void ParticleSystem::updateParticles(double t) {
	for (auto part_it = _particles.begin(); part_it != _particles.end(); ) {
		if ((*part_it)->integrate(t)) {
			++part_it;
		}
		else {
			_particle_force_registry.deleteParticleRegistry(*part_it);
			(*part_it)->kill();
			delete (*part_it);
			(*part_it) = nullptr;
			part_it = _particles.erase(part_it);
		}
	}
}
