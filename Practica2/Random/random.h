#pragma once
#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <memory>

using random_generator = std::mt19937;

class Random {
public:
	static random_generator& gen() {
		return getInstance()._gen;
	}

private:
	static std::unique_ptr<Random> _instance;
	random_generator _gen; // mersenne_twister_engine seeded with rd()
	std::random_device _rd;  // a seed source for the random number engine

	Random() : _gen(_rd()) {}

	static Random& getInstance() {
		if (_instance) return *_instance;
		return *(_instance = std::make_unique<Random>());
	}
};

namespace random {
	random_generator& gen() { return Random::gen(); }
}

#endif // !RANDOM_H