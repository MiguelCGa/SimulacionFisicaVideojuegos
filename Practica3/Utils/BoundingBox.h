#pragma once
#include "../core.hpp"

class BoundingBox {
public:
	// Creates a limitless bounding box by default
	BoundingBox();
	BoundingBox(Vector3 origin, Vector3 offset);
	BoundingBox(Vector3 origin, float offset);

	bool contains(Vector3 const& pos) const noexcept;
protected:
	Vector3 _min, _max;
};

