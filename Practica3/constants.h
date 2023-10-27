#pragma once
#include "core.hpp"
#include <random>
namespace values {
	constexpr float damping = 0.998f;
	const Vector3 gravity = Vector3(0.0f, -9.8f, 0.0f);
	constexpr double std_life_time = 5.0;
}