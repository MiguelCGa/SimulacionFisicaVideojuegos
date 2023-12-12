#include "ForceGenerator.h"

ForceGenerator::ForceGenerator() : 
	ForceGenerator(-1.0, BoundingBox()) {
}

ForceGenerator::ForceGenerator(double duration) :
	ForceGenerator(duration, BoundingBox()) {
}

ForceGenerator::ForceGenerator(BoundingBox const& area) : 
	ForceGenerator(-1.0, area) {
}

ForceGenerator::ForceGenerator(double duration, BoundingBox const& area) : 
	_duration(duration),
	_area(area),
	_t(0.0) {
}

bool ForceGenerator::updateForce(Particle* particle) {
	if (!_area.contains(particle->getPosition())) return isAlive();
	applyForce(particle);
	return isAlive();
}

bool ForceGenerator::updateTime(double t) {
	_t += t;
	return isAlive();
}

bool ForceGenerator::isAlive() const noexcept {
	return _t < _duration || _duration < 0.0; // Devuelve true si ya era cero o si es positivo
}
