#ifndef RAY_TRACE_H
#define RAY_TRACE_H

#include "Ray.h"
#include "Object.h"
#include <vector>

class RayTracer {
public:
	RayTracer() { limitWeight = 0.0001; lambda = 0.5; }
	SpotLight spotLight;
	Sphere O;
	Color m_color;
	double limitWeight;
	double lambda;
	Color rayTrace(Vec3 S, Direction direction, double weight, Color color);
	Color calDiffusion(Vec3 S ,Vec3 R,Vec3 E,double weight,Color color);
	Color calRefraction(Vec3 S, Vec3 D, Vec3 E, double weight, Color color,bool& in);
	//void intersect(Vec3 S, Direction direction);
	//Vec3 getNearestIntersection(Vec3 S, Direction direction);
};
#endif
