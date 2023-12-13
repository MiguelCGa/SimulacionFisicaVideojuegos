#pragma once
#include "random.h"

inline float percentage_randomize(double value, double percentage) {
	const double variation = abs(value / (percentage / 2) * 100);
	return std::uniform_real_distribution<>(value - variation, value + variation)(gen());
}