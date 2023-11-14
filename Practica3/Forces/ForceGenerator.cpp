#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(double duration) :
	_duration(duration),
	_t(0.0) {
}

bool ForceGenerator::updateTime(double t) {
	_t += t;
	return isAlive();
}

bool ForceGenerator::isAlive() const noexcept {
	return _t < _duration || _duration < 0.0; // Devuelve true si ya era cero o si es positivo
}
