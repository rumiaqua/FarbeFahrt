# pragma once

class Sphere;

class Capsule;

class Line;

class Triangle;

namespace Collision
{
	// -----------------------------------------------------------
	// Sphere
	// -----------------------------------------------------------
	bool intersects(const Sphere& s1, const Sphere& s2);

	bool intersects(const Sphere& s, const Capsule& c);

	bool intersects(const Sphere& s, const Line& l);

	bool intersects(const Sphere& s, const Triangle& t);

	// -----------------------------------------------------------
	// Capsule
	// -----------------------------------------------------------
	bool intersects(const Capsule& c, const Sphere& s);

	bool intersects(const Capsule& c1, const Capsule& c2);

	bool intersects(const Capsule& c, const Line& l);

	bool intersects(const Capsule& c, const Triangle& t);

	// -----------------------------------------------------------
	// Line
	// -----------------------------------------------------------
	bool intersects(const Line& l, const Sphere& s);

	bool intersects(const Line& l, const Capsule& c);

	bool intersects(const Line& l1, const Line& l2);

	bool intersects(const Line& l, const Triangle& t);

	// -----------------------------------------------------------
	// Triangle
	// -----------------------------------------------------------
	bool intersects(const Triangle& t, const Sphere& s);

	bool intersects(const Triangle& t, const Capsule& c);

	bool intersects(const Triangle& t, const Line& l);

	bool intersects(const Triangle& t1, const Triangle& t2);
}
