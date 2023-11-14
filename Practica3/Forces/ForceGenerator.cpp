#include "ForceGenerator.h"

bool ForceGenerator::updateTime(double t) {
	_t += t;
	return isAlive();
}

bool ForceGenerator::isAlive() const {
	return _t < _duration || _duration < 0.0; // Devuelve true si ya era cero o si es positivo
}
