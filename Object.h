#ifndef OBJECT_H
#define OBJECT_H
#include "Ray.h"
#include <cmath>
class Sphere {
public:
	Point center;
	Color color;
	int R;

	double Kd;
	double Kr;
	double Ks;
	Sphere(Point c = Point(150, 150, 150), int Ra = 120, Color m_color = Color(0, 0, 1), double mKd = 0.2, double mKr = 0.3, double mKs = 0.4) :center(c),
		R(Ra), color(m_color), Kd(mKd), Kr(mKr), Ks(mKs) {}
	inline double intersect(Vec3 S, Direction direction, bool& in);
};

double Sphere::intersect(Vec3 S, Direction d, bool& in)
{
	Vec3 M = center - S;
	double m = M.abs();
	if (m<R+1e-4)
		in=true;//入射点在球内
	if (d.dot(M) < 1e-4)
		return 0;
	double cos = d.dot(M) / (d.abs()*M.abs());
	if (cos > 1) cos = 1.0;
	double p = m*sqrt(1 - cos*cos);
	if (p > R)
		return 0;
	double d2 = sqrt(R*R - p*p);
	double d1 = sqrt(m*m - p*p) + (in?d2:-d2);
	return d1;
}

#endif
