#include "Object.h"

Intersection Sphere::intersect(Vec3 S, Vec3 d)
{
	Intersection result;
	result.in = false; result.intersected = false;
	Vec3 co = S - center;
	if (co.abs() - R<eps)
		result.in = true;
	float d_co = d.dot(co);
	float delta = d_co*d_co - d.dot(d)*co.dot(co);
	if (delta<eps)
		return result;
	float t1 = (-2 * d_co - sqrt(delta)) / (2 * d.dot(d));
	if (t1>eps)
	{
		result.intersected = true; result.t = t1;
		return result;
	}
	float t2 = (-2 * d_co + sqrt(delta)) / (2 * d.dot(d));
	if (t2>eps)
	{
		result.intersected = true; result.t = t2;
	}
	return result;
}
Intersection Sphere::intersect(Ray& ray)
{
	return intersect(ray.Start, ray.D);
}
