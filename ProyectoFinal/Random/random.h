#pragma once

#include <random>
#include <memory>

using random_generator = std::mt19937;

class Random {
public:
	static random_generator& gen();

private:
	Random();
	static Random* getInstance();


	static std::unique_ptr<Random> _instance;
	random_generator _gen; // mersenne_twister_engine seeded with rd()
	std::random_device _rd;  // a seed source for the random number engine
};

inline random_generator& gen() { return Random::gen(); }