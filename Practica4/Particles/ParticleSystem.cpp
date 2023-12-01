#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem() {


	// SLINKY
	Vector3 pos(0.0, 15.0, 0.0);
	float mass = 5.0f;

	createSlinky(7, false, pos, mass);
	pos = Vector3(-10.0, 15.0, 0.0);
	createSlinky(7, true, pos, mass);


	pos = Vector3(50.0, 5.0, 0.0);
	mass = 300.0f;

	Particle* pliquid = new Particle(pos, mass, Vector3(0), physx::PxGeometryType::eBOX);
	_particles.push_back(pliquid);

	BoundingBox area(Vector3(50, 0, 0), Vector3(10, 1.0, 10));
	float density = 1000.0f, k1 = 50.0f, k2 = 0.0f;

	LiquidForceGenerator* agua = new LiquidForceGenerator(area, density, k1, k2);
	_force_generators.push_back(agua);
	_particle_force_registry.addRegistry(pliquid, agua);

	//BuoyancyForceGenerator* b = new BuoyancyForceGenerator(area, density);
	//_force_generators.push_back(b);
	//_particle_force_registry.addRegistry(pliquid, b);
	
	//DragForceGenerator* dl = new DragForceGenerator(k1, k2, area);
	//_force_generators.push_back(dl);
	//_particle_force_registry.addRegistry(pliquid, dl);


	pos = Vector3(100.0, 5.0, 0.0);

	pliquid = new Particle(pos, mass, Vector3(0), physx::PxGeometryType::eBOX);
	_particles.push_back(pliquid);

	area = BoundingBox(Vector3(100, 0, 0), Vector3(10, 1.0, 10));
	density = 1500.0f;
	k1 = 500.0f;

	LiquidForceGenerator* viscoso = new LiquidForceGenerator(area, density, k1, k2);
	_force_generators.push_back(viscoso);
	_particle_force_registry.addRegistry(pliquid, viscoso);


	GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, -9.8, 0));
	createGeneralForce(g);
	DragForceGenerator* d = new DragForceGenerator();
	createGeneralForce(d);
}

ParticleSystem::~ParticleSystem() {
	for (Particle*& part : _particles) {
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

void ParticleSystem::soplido() {
	const Vector3 wVel(40, 0, 0);
	constexpr float k1 = 50.0f, k2 = 0.0f;
	constexpr double duration = 2.0;
	WindForceGenerator* w = new WindForceGenerator(wVel, k1, k2, BoundingBox(), duration);
	createGeneralForce(w);
}

void ParticleSystem::lowSlinkyK() {
	for (auto& e : slinky) {
		e->setK(10.0);
	}
}

void ParticleSystem::mediumSlinkyK() {
	for (auto& e : slinky) {
		e->setK(50.0);
	}
}

void ParticleSystem::highSlinkyK() {
	for (auto& e : slinky) {
		e->setK(250.0);
	}
}

void ParticleSystem::createSlinky(int elements, bool gomas, Vector3 pos, float mass) {

	Particle* p = new Particle(pos, mass);
	_particles.push_back(p);

	AnchoredSpringForceGenerator* s = new AnchoredSpringForceGenerator(100.0, 10.0, { pos.x,25,pos.z });
	_force_generators.push_back(s);
	_particle_force_registry.addRegistry(p, s);
	slinky.push_back(s);

	for (int i = 0; i < elements - 1; ++i) {
		pos.y = -15.0 * i;
		mass = 5.0f;
		Particle* p2 = new Particle(pos, mass);
		_particles.push_back(p2);

		constexpr double k = 100.0, resting_length = 15.0;
		SpringForceGenerator* s1;
		SpringForceGenerator* s2;
		if (gomas) {
			s1 = new ElasticRubberForceGenerator(k, resting_length, p);
			s2 = new ElasticRubberForceGenerator(k, resting_length, p2);
		}
		else {
			s1 = new SpringForceGenerator(k, resting_length, p);
			s2 = new SpringForceGenerator(k, resting_length, p2);
		}

		_force_generators.push_back(s1);
		_force_generators.push_back(s2);

		_particle_force_registry.addRegistry(p2, s1);
		_particle_force_registry.addRegistry(p, s2);

		slinky.push_back(s1);
		slinky.push_back(s2);

		p = p2;
	}
}

void ParticleSystem::generateParticles() {
	for (auto const& gen : _particle_generators) {
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
