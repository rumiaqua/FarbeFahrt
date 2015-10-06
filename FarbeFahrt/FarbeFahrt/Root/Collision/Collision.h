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
	bool Intersects(const Sphere* s1, const Sphere* s2);

	bool Intersects(const Sphere* s, const Capsule* c);

	bool Intersects(const Sphere* s, const Line* l);

	bool Intersects(const Sphere* s, const Triangle* t);

	// -----------------------------------------------------------
	// Capsule
	// -----------------------------------------------------------
	bool Intersects(const Capsule* c, const Sphere* s);

	bool Intersects(const Capsule* c1, const Capsule* c2);

	bool Intersects(const Capsule* c, const Line* l);

	bool Intersects(const Capsule* c, const Triangle* t);

	// -----------------------------------------------------------
	// Line
	// -----------------------------------------------------------
	bool Intersects(const Line* l, const Sphere* s);

	bool Intersects(const Line* l, const Capsule* c);

	bool Intersects(const Line* l1, const Line* l2);

	bool Intersects(const Line* l, const Triangle* t);

	// -----------------------------------------------------------
	// Triangle
	// -----------------------------------------------------------
	bool Intersects(const Triangle* t, const Sphere* s);

	bool Intersects(const Triangle* t, const Capsule* c);

	bool Intersects(const Triangle* t, const Line* l);

	bool Intersects(const Triangle* t1, const Triangle* t2);
}
