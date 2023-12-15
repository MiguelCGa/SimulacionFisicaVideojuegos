#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(physx::PxPhysics* gPhysics, physx::PxScene* mScene) : 
	_maxElems(500) {

	GaussianParticleGenerator* pg = new GaussianParticleGenerator(
		"ActorGenerator",	// name
		1,					// generations per iteration
		BoundingBox(),		// limits
		Vector3(0),			// mean position
		Vector3(0),			// mean velocity
		Vector3(50),		// dev position
		Vector3(1));		// dev velocity
	_particle_generators.push_back(pg);
	pg->initializeForces(&_particle_force_registry);
	
	
	RigidBody* model = new RigidBody(gPhysics, mScene,
		Vector3(0),												// position
		physx::PxActorType::eRIGID_DYNAMIC,						// type
		createRegularShape(physx::PxGeometryType::eBOX, 2.0f),	// shape (type, dimensions)
		1.0,													// density
		Vector4(0.5),											// color
		2.0,													// lifetime
		BoundingBox());											// limits
	
	mScene->removeActor(*model->getActor()); // para que el modelo no tenga fisicas
	pg->setParticle(model);



	RigidBody* suelo = new RigidBody(gPhysics, mScene, 
		Vector3(0, -100, 0),								// position
		physx::PxActorType::eRIGID_STATIC,					// type
		CreateShape(physx::PxBoxGeometry(500, 10, 500)),	// shape (type, dimentions)
		0.0,												// density
		Vector4(0.5),										// color
		-1.0,												// lifetime
		BoundingBox());										// limits
	_particles.push_back(suelo);							
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
	constexpr float K = 500000.0f;
	ExplosionForceGenerator* e = new ExplosionForceGenerator(origin, duration, K);
	createGeneralForce(e);
}

void ParticleSystem::wind() {
	if (_wind == nullptr) {
		_wind = new WindForceGenerator(
			Vector3(30.0f, 20.0f, 0.0f),		// wind velocity
			100.0f,								// k1
			0.0f,								// k2
			BoundingBox(Vector3(0), 100.0f));	// area
		createGeneralForce(_wind);
	}
	else {
		_wind->unalive();
		_wind = nullptr;
	}
}

void ParticleSystem::whirlwind() {
	if (_whirlwind == nullptr) {
		_whirlwind = new WhirlwindForceGenerator(
			1.0f,			// K
			100.0f,			// k1
			0.0f,			// k2
			BoundingBox());	// area
		createGeneralForce(_whirlwind);
	}
	else {
		_whirlwind->unalive();
		_whirlwind = nullptr;
	}
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
