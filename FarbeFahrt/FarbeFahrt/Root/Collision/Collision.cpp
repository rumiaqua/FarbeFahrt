#include "Collision.h"
# include "Sphere.h"
# include "Capsule.h"
# include "Line.h"
# include "Triangle.h"

# include "Utility/Math.h"

# include <DxLib.h>

# include "Utility/MemoryCast.h"

bool Collision::intersects(const Sphere& s1, const Sphere& s2)
{
	return HitCheck_Sphere_Sphere(
		s1.origin, s1.radius,
		s2.origin, s2.radius) != 0;
}

bool Collision::intersects(const Sphere& s, const Capsule& c)
{
	return HitCheck_Sphere_Capsule(
		s.origin, s.radius,
		c.origin, c.end, c.radius) != 0;
}

bool Collision::intersects(const Sphere& s, const Line& l)
{
	return intersects(l, s);
}

bool Collision::intersects(const Sphere& s, const Triangle& t)
{
	return HitCheck_Sphere_Triangle(
		s.origin, s.radius,
		t.origin, t.p1, t.p2) != 0;
}

bool Collision::intersects(const Capsule& c, const Sphere& s)
{
	return intersects(s, c);
}

bool Collision::intersects(const Capsule& c1, const Capsule& c2)
{
	return HitCheck_Capsule_Capsule(
		c1.origin, c1.end, c1.radius,
		c1.origin, c1.end, c1.radius) != 0;
}

bool Collision::intersects(const Capsule& c, const Line& l)
{
	return intersects(l, c);
}

bool Collision::intersects(const Capsule& c, const Triangle& t)
{
	return HitCheck_Capsule_Triangle(
		c.origin, c.end, c.radius,
		t.origin, t.p1, t.p2) != 0;
}

bool Collision::intersects(const Line& l, const Sphere& s)
{
	return intersects(s, l);
}

bool Collision::intersects(const Line& l, const Capsule& c)
{
	return intersects(c, l);
}

bool Collision::intersects(const Line& l1, const Line& l2)
{
	Vector3 ac = l2.origin - l1.origin;
	Vector3 n1 = Vector3::Normalize(l1.end - l1.origin);
	Vector3 n2 = Vector3::Normalize(l2.end - l2.origin);

	float t1 = Vector3::Dot(n1, ac);
	float t2 = Vector3::Dot(n2, ac);
	float dot = Vector3::Dot(n1, n2);
	float pow = dot * dot;

	// 最近点を通る直線が通る各線分上の点の比率
	float d1 = (t1 - dot * t2) / (1.0f - pow);
	float d2 = (dot * t1 - t2) / (1.0f - pow);

	// 比率が 0.0 から 1.0 の間に無ければ線分は交差していない
	if (
		!Math::IsContains(d1, 0.0f, 1.0f) ||
		!Math::IsContains(d2, 0.0f, 1.0f))
	{
		return false;
	}

	Vector3 p1 = l1.origin + n1 * d1;
	Vector3 p2 = l2.origin + n2 * d2;
	Vector3 sub = p1 - p2;

	// 最近点同士の距離が限りなく0に近ければ交差している
	return Vector3::Dot(sub, sub) < 0.0001f;
}

bool Collision::intersects(const Line& l, const Triangle& t)
{
	return HitCheck_Line_Triangle(
		l.origin, l.end,
		t.origin, t.p1, t.p2).HitFlag != 0;
}

bool Collision::intersects(const Triangle& t, const Sphere& s)
{
	return intersects(s, t);
}

bool Collision::intersects(const Triangle& t, const Capsule& c)
{
	return intersects(c, t);
}

bool Collision::intersects(const Triangle& t, const Line& l)
{
	return intersects(l, t);
}

bool Collision::intersects(const Triangle& t1, const Triangle& t2)
{
	return HitCheck_Triangle_Triangle(
		t1.origin, t1.p1, t1.p2,
		t2.origin, t2.p1, t2.p2) != 0;
}
