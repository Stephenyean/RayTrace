#ifndef RAY_H
#define RAY_H
#include "color.h"
#include <cmath>
class Vec3{
public:
	float x , y , z;
	Vec3( double  X = 0 , double Y = 0 , double Z = 0 ):x(X) ,y(Y) ,z(Z) {}
	float dot(Vec3& rhs) {
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}
	float abs() { return sqrt(x*x + y*y + z*z); }
	void norm() { double v = abs(); x /= v; y /= v; z /= v; }
	Vec3 operator+(const Vec3& rhs) const { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vec3 operator-(const Vec3& rhs) const { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vec3 operator*(const Vec3& rhs) const { return Vec3(x * rhs.x, y * rhs.y, z * rhs.z); }
	Vec3 operator*(const double& val) const { return Vec3(x*val, y*val, z*val); }
	~Vec3(){}
};
typedef Vec3 Point;
typedef Vec3 Direction;
//class Ray{
//public:
//	Vec3 direction;
//	Vec3 point;
//	double ratio;
//	Ray( Vec3 D=Vec3(0,0,0) ,Vec3 P=Vec3(0,0,0)):direction(D) ,point(P) ,ratio(1) {}
//	~Ray(){}
//};
class SpotLight{
public:
	Vec3 place;
	Color color;
	SpotLight(Vec3 P = Vec3(150, 1500, 300), Color C=Color(1,1,1)):place(P),color(C){}
};
#endif
