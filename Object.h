#ifndef OBJECT_H
#define OBJECT_H
#include "Ray.h"
#include <cmath>
//#include <pair>
using namespace std;
struct Intersection{
	bool in=false;
	bool intersected=false;
	float t=1e20;
};
class Object{
public:
//	Point center;
	Color color;
//	int R;

	float Kd;
	float Kr;
	float Ks;
	Object(Color m_color = Color(0, 0, 1), float mKd = 0.2, float mKr = 0.3, float mKs = 0.4) 
		:color(m_color), Kd(mKd), Kr(mKr), Ks(mKs) {}
	virtual Intersection intersect(Ray& ray)=0;
	virtual Vec3 getNormal(Vec3 I,bool,Vec3)=0;
//	Intersection intersect(Vec3 ,Vec3);
};
class Sphere :public Object {
public:
	Sphere(Point c = Point(150, 150, 150), int Ra = 120, Color m_color = Color(0, 0, 1), float mKd = 0.2, float mKr = 0.3, float mKs = 0.4) 
		:Object(m_color,mKd,mKr,mKs),center(c),R(Ra) {}
	Point center;
	int R;
	Intersection intersect(Ray& ray);
	Intersection intersect(Vec3 ,Vec3);
	Vec3 getNormal(Vec3 I,bool,Vec3);
};
class Panel :public Object{
public:
	float distance;
	Vec3 direction;
	Color color;
	Panel(Vec3 _d=Vec3(0,0,0),float _D=0,Color m_color=Color(0,0,1),float mKd = 0.2, float mKr = 0.3, float mKs = 0.4) 
		:Object(m_color,mKd,mKr,mKs),distance(_D),direction(_d) {}
	Intersection intersect(Ray& ray);
	Intersection intersect(Vec3 ,Vec3);
	Vec3 getNormal(Vec3 I,bool,Vec3);
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
