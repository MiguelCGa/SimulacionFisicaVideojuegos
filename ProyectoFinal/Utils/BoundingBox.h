#pragma once
#include "../core.hpp"

class BoundingBox {
public:
	// Creates a limitless bounding box by default
	BoundingBox();
	BoundingBox(Vector3 origin, Vector3 offset);
	BoundingBox(Vector3 origin, float offset);

	bool contains(Vector3 const& pos) const noexcept;
	Vector3 getOrigin() const;
	float getWidth() const noexcept;
	float getHeight() const noexcept;
	float getDepth() const noexcept;
	Vector3 getDimentions() const;
	void moveOriginTo(Vector3 const& pos);
protected:
	Vector3 _min, _max, _origin;
};

