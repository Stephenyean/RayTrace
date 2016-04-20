#ifndef OBJECT_H
#define OBJECT_H
#include "Ray.h"
#include <cmath>
//#include <pair>
using namespace std;
struct Intersection{
	bool in;
	bool intersected;
	float t;
};

class Sphere {
public:
	Point center;
	Color color;
	int R;

	float Kd;
	float Kr;
	float Ks;
	Sphere(Point c = Point(150, 150, 150), int Ra = 120, Color m_color = Color(0, 0, 1), float mKd = 0.2, float mKr = 0.3, float mKs = 0.4) 
		:center(c),R(Ra), color(m_color), Kd(mKd), Kr(mKr), Ks(mKs) {}
	Intersection intersect(Ray& ray);
	Intersection intersect(Vec3 ,Vec3);
};

/*
pair<bool,float> Sphere::intersect(Vec3 S, Direction d)
{
	Vec3 M = center - S;
	float m = M.abs();
	if (m<R+1e-4)
		in=true;//入射点在球内
	if (d.dot(M) < 1e-4)
		return 0;
	float cos = d.dot(M) / (d.abs()*M.abs());
	if (cos > 1) cos = 1.0;
	float p = m*sqrt(1 - cos*cos);
	if (p > R)
		return 0;
	float d2 = sqrt(R*R - p*p);
	float d1 = sqrt(m*m - p*p) + (in?d2:-d2);
	return d1;
}
*/
#endif
