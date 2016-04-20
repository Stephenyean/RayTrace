#ifndef RAY_H
#define RAY_H
#include "color.h"
#include <cmath>
#define eps 1e-4
class Vec3{
public:
	float x , y , z;
	Vec3( float  X = 0 , float Y = 0 , float Z = 0 ):x(X) ,y(Y) ,z(Z) {}
	float dot(Vec3& rhs) {
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}
	float abs() { return sqrt(x*x + y*y + z*z); }
	void norm() { float v = abs(); x /= v; y /= v; z /= v; }
	Vec3 operator+(const Vec3& rhs) const { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vec3 operator-(const Vec3& rhs) const { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vec3 operator*(const Vec3& rhs) const { return Vec3(x * rhs.x, y * rhs.y, z * rhs.z); }
	Vec3 operator*(const float& val) const { return Vec3(x*val, y*val, z*val); }
	~Vec3(){}
};


typedef Vec3 Point;

typedef Vec3 Direction;

class Ray{
public:
	Ray(Point S,Vec3 _D,float _w=0.0,Color _c=Color(0,0,0),int _d=0):Start(S),D(_D),weight(_w),color(_c),depth(_d){}
	Point Start;
	Vec3 D;
	float weight;
	Color color;
	int depth;
};

class SpotLight{
public:
	Vec3 place;
	Color color;
	SpotLight(Vec3 P = Vec3(150, 1500, 300), Color C=Color(1,1,1)):place(P),color(C){}
};
#endif
