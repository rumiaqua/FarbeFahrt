#include "Collision.h"
# include "Sphere.h"
# include "Capsule.h"
# include "Line.h"
# include "Triangle.h"

# include "Utility/Math.h"

bool Collision::Intersects(const Sphere* s1, const Sphere* s2)
{
	return HitCheck_Sphere_Sphere(
		s1->origin, s1->radius,
		s2->origin, s2->radius) != 0;
}

bool Collision::Intersects(const Sphere* s, const Capsule* c)
{
	return HitCheck_Sphere_Capsule(
		s->origin, s->radius,
		c->origin, c->end, c->radius) != 0;
}

bool Collision::Intersects(const Sphere* s, const Line* l)
{
	return Intersects(l, s);
}

bool Collision::Intersects(const Sphere* s, const Triangle* t)
{
	return HitCheck_Sphere_Triangle(
		s->origin, s->radius,
		t->origin, t->p1, t->p2) != 0;
}

bool Collision::Intersects(const Capsule* c, const Sphere* s)
{
	return Intersects(s, c);
}

bool Collision::Intersects(const Capsule* c1, const Capsule* c2)
{
	return HitCheck_Capsule_Capsule(
		c1->origin, c1->end, c1->radius,
		c1->origin, c1->end, c1->radius) != 0;
}

bool Collision::Intersects(const Capsule* c, const Line* l)
{
	return Intersects(l, c);
}

bool Collision::Intersects(const Capsule* c, const Triangle* t)
{
	return HitCheck_Capsule_Triangle(
		c->origin, c->end, c->radius,
		t->origin, t->p1, t->p2) != 0;
}

bool Collision::Intersects(const Line* l, const Sphere* s)
{
	return Intersects(s, l);
}

bool Collision::Intersects(const Line* l, const Capsule* c)
{
	return Intersects(c, l);
}

bool Collision::Intersects(const Line* l1, const Line* l2)
{
	VECTOR ac = VSub(l2->origin, l1->origin);
	VECTOR n1 = VNorm(VSub(l1->end, l1->origin));
	VECTOR n2 = VNorm(VSub(l2->end, l2->origin));

	float t1 = VDot(n1, ac);
	float t2 = VDot(n2, ac);
	float dot = VDot(n1, n2);
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

	VECTOR p1 = VAdd(l1->origin, VScale(n1, d1));
	VECTOR p2 = VAdd(l2->origin, VScale(n2, d2));
	VECTOR sub = VSub(p1, p2);

	// 最近点同士の距離が限りなく0に近ければ交差している
	return VDot(sub, sub) < 0.0001f;
}

bool Collision::Intersects(const Line* l, const Triangle* t)
{
	return HitCheck_Line_Triangle(
		l->origin, l->end,
		t->origin, t->p1, t->p2).HitFlag != 0;
}

bool Collision::Intersects(const Triangle* t, const Sphere* s)
{
	return Intersects(s, t);
}

bool Collision::Intersects(const Triangle* t, const Capsule* c)
{
	return Intersects(c, t);
}

bool Collision::Intersects(const Triangle* t, const Line* l)
{
	return Intersects(l, t);
}

bool Collision::Intersects(const Triangle* t1, const Triangle* t2)
{
	return HitCheck_Triangle_Triangle(
		t1->origin, t1->p1, t1->p2,
		t2->origin, t2->p1, t2->p2) != 0;
}
