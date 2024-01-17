#include "random.h"

std::unique_ptr<Random> Random::_instance = nullptr;

Random::Random() :
	_gen(_rd()) {
}

random_generator& Random::gen() {
	return getInstance()->_gen;
}

Random* Random::getInstance() {
	if (_instance.get() != nullptr) return _instance.get();
	return (_instance = std::unique_ptr<Random>(new Random())).get();
}
