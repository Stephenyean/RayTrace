#ifndef RAY_TRACE_H
#define RAY_TRACE_H

#include "Ray.h"
#include "Object.h"
#include <vector>

class RayTracer {
public:
	RayTracer(int MD,float MW,int _objectNum, Object** _O,int x,int y,int z,float r,float g,float b,float lW=0.0001,float lam=0.5)
		:MAX_DEPTH(MD),MIN_WEIGHT(MW),objectNum(_objectNum), O(_O) , spotLight(SpotLight(Vec3(x,y,z),Color(r,g,b))) , limitWeight(lW),lambda(lam) {}
	SpotLight spotLight;
	Object** O;
	int objectNum;
	int MAX_DEPTH;
	float MIN_WEIGHT;
	Color m_color;
	float limitWeight;
	float lambda;
	int verbose=0;
	//Color rayTrace(Vec3 S, Direction direction, float weight, Color color);
	Color rayTrace(Ray& inRay);
	Color calDiffusion(Ray& inRay, Vec3 I, Vec3 Normal, Vec3 Out, bool in,Object*);
	Color calRefraction(Ray& inRay, Vec3 I, Vec3 Normal, bool in,Object*);
	//Color calDiffusion(Vec3 S ,Vec3 R,Vec3 E,float weight,Color color);
	//Color calRefraction(Vec3 S, Vec3 D, Vec3 E, float weight, Color color,bool& in);
	//void intersect(Vec3 S, Direction direction);
	//Vec3 getNearestIntersection(Vec3 S, Direction direction);
};
#endif
