# pragma once

class Sphere;
class Capsule;
class Line;
class Triangle;
class ModelCollider;

namespace Collision
{
	// -----------------------------------------------------------
	// Sphere
	// -----------------------------------------------------------
	bool intersects(const Sphere& sphere1, const Sphere& sphere2);

	bool intersects(const Sphere& sphere1, const Capsule& capsule2);

	bool intersects(const Sphere& sphere1, const Line& line2);

	bool intersects(const Sphere& sphere1, const Triangle& triangle2);

	// -----------------------------------------------------------
	// Capsule
	// -----------------------------------------------------------
	bool intersects(const Capsule& capsule1, const Sphere& sphere2);

	bool intersects(const Capsule& capsule1, const Capsule& capsule2);

	bool intersects(const Capsule& capsule1, const Line& line2);

	bool intersects(const Capsule& capsule1, const Triangle& triangle2);

	// -----------------------------------------------------------
	// Line
	// -----------------------------------------------------------
	bool intersects(const Line& line1, const Sphere& sphere2);

	bool intersects(const Line& line1, const Capsule& capsule2);

	bool intersects(const Line& line1, const Line& line2);

	bool intersects(const Line& line1, const Triangle& triangle2);

	// -----------------------------------------------------------
	// Triangle
	// -----------------------------------------------------------
	bool intersects(const Triangle& triangle1, const Sphere& sphere2);

	bool intersects(const Triangle& triangle1, const Capsule& capsule2);

	bool intersects(const Triangle& triangle1, const Line& line2);

	bool intersects(const Triangle& triangle1, const Triangle& triangle2);

	// -----------------------------------------------------------
	// ModelCollider
	// -----------------------------------------------------------
	bool intersects(const ModelCollider& model1, const Sphere& sphere2);

	bool intersects(const ModelCollider& model1, const Capsule& capsule2);

	bool intersects(const ModelCollider& model1, const Line& line2);

	bool intersects(const ModelCollider& model1, const Triangle& triangle2);
}
