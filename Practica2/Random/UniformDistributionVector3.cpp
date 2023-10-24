#include "UniformDistributionVector3.h"

UniformDistributionVector3::UniformDistributionVector3(Vector3 const& mean, Vector3 const& width) :
	DistributionVector3(
		std::uniform_int_distribution<>::param_type(mean.x - width.x, mean.x + width.x),
		std::uniform_int_distribution<>::param_type(mean.y - width.y, mean.y + width.y),
		std::uniform_int_distribution<>::param_type(mean.z - width.z, mean.z + width.z)) {
}