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
	float limitWeight;
	float lambda;
	//Color rayTrace(Vec3 S, Direction direction, float weight, Color color);
	Color rayTrace(Ray& inRay);
	Color calDiffusion(Ray& inRay, Vec3 I, Vec3 Normal, Vec3 Out);
	//Color calDiffusion(Vec3 S ,Vec3 R,Vec3 E,float weight,Color color);
	//Color calRefraction(Vec3 S, Vec3 D, Vec3 E, float weight, Color color,bool& in);
	//void intersect(Vec3 S, Direction direction);
	//Vec3 getNearestIntersection(Vec3 S, Direction direction);
};
#endif
