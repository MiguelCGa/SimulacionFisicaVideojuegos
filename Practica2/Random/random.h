#pragma once
#ifndef RANDOM_H
#define RANDOM_H

#include <random>

using random_generator = std::mt19937;
namespace random {
	std::random_device rd;  // a seed source for the random number engine
	random_generator gen(rd()); // mersenne_twister_engine seeded with rd()
}

#endif // !RANDOM_H


