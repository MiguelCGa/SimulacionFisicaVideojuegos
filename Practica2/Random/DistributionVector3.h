#pragma once

#include "random.h"
#include "../core.hpp"

template <typename T>
class DistributionVector3 {
private:
	T _x, _y, _z;
public:
	template <typename T_param_type>
	DistributionVector3(T_param_type x, T_param_type y, T_param_type z) :
		_x(x), _y(y), _z(z) {
	}

	Vector3 operator()(random_generator gen) {
		return Vector3(_x(gen), _y(gen), _z(gen));
	}
};