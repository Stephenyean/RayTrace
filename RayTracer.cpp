#include "color.h"
#include "RayTracer.h"
#include "math.h"
#include "Object.h"
#define MAX_DEPTH 5
#define MIN_WEIGHT 1e-4
Color RayTracer::rayTrace(Ray& inRay)
{
	Color color(0,0,0);
	if(inRay.depth>MAX_DEPTH)
		return color;
	if(inRay.weight<MIN_WEIGHT)
		return color;
	Intersection result=O.intersect(inRay);
	if(result.intersected==false)
		return color;
	float t=result.t;
	Vec3 I=inRay.Start+inRay.D*t;
	Vec3 Normal= (result.in)?(O.center-I):(I-O.center);Normal.norm();
	Vec3 In=Vec3(0,0,0)-inRay.D;
	Vec3 Out=Normal*(2*In.dot(Normal))-In;
	if(result.in==false) color+=calDiffusion(inRay,I,Normal,Out);
	Ray outRay(I,Out,inRay.weight*lambda,inRay.color,inRay.depth+1);
	//outRay.Start=I; outRay.D=Out; outRay.weight=inRay.weight*lambda; outRay.depht=inRay.depth+1;
	color+=rayTrace(outRay);
	return color;
}

Color RayTracer:: calDiffusion(Ray& inRay, Vec3 I, Vec3 Normal, Vec3 Out)
{
	Color color(0,0,0);
	//I=I+0.01*(I-O.center);
	Vec3 S=spotLight.place-I;S.norm();
/*	Intersection result=O.intersect(I,S);
	if(result.intersected==true)
		return color;*/
	if(Normal.dot(S)<eps)
		return color;
	return inRay.color*O.color * inRay.weight * ( O.Kd * Normal.dot(S) + 
		O.Kr * pow(Out.dot(S),10));
}
/*
Color RayTracer::rayTrace(Vec3 S, Direction direction, float weight, Color color)
{
	//direction.norm();
	if (weight < limitWeight)
		return Color(0,0,0);
	float d;
	bool in = false;
	if ((d=O.intersect(S, direction,in)) == 0)
		return Color(0,0,0);
	//d /= 2 * direction.dot(direction);
	float x = d / direction.abs();
	Vec3 P(S.x + direction.x*x, S.y + direction.y*x, S.z + direction.z*x);
	Vec3 r = P - O.center;
	r.norm(); //S.norm();
	//direction.norm();
	Vec3 s = Vec3(0, 0, 0) - direction;
	s.norm();
	r = r * 2.0 * (r.dot(s));
	Vec3 E = r - s;
	E.norm();
	Color rc(0, 0, 0);
	r.norm();
	if(!in)
		rc+=calDiffusion(P, r ,E,weight,color);
	rc+=rayTrace(P, E, weight*lambda, color);
	rc += calRefraction(P, Vec3(0, 0, 0) - r, Vec3(0, 0, 0) - s, weight, color,in);
	return rc;
}
Color RayTracer::calDiffusion(Vec3 S, Vec3 R,Vec3 E,float weight,Color color)
{
	Vec3 L = spotLight.place - S;
	L.norm();
	if (R.dot(L) < 0)
		return Color(0, 0, 0);
	return color*O.color*weight*(O.Kd*R.dot(L) +O.Kr*pow(E.dot(L),10));
}
Color RayTracer::calRefraction(Vec3 S, Vec3 D, Vec3 E, float weight, Color color, bool& in)
{
	float cosA = D.dot(E);
	if (cosA > 1) cosA = 1.0;
	float sinA = sqrt(1 - cosA*cosA), sinT = sinA*(in ? 1, 25 : 0.8);
	if (sinT >= 1) return Color(0, 0, 0);
	float cosT = sqrt(1 - sinT*sinT);
	float v = sinA*cosT - cosA*sinT;
	if (v < 1e-4)
		D = D;
	else
		D = D*(sinT / v);
	Vec3 Z = D + E;
	return rayTrace(S, Z, weight*lambda, color);
}
//bool RayTracer::Intersected(Vec3 S, Direction d)
//{
//	Vec3 r(O->center.x - S.x, O->center.y - S.y, O->center.z - S.z);
//	if (r.abs() < O->R)
//		return true;
//	float dotValue = r.dot(d);
//	if (dotValue< 0)
//		return false;
//	float cos = dotValue / (r.abs()*d.abs());
//	float sin = sqrt(1 - cos*cos);
//	if (r.abs()*sin <= O->R)
//		return true;
//	else
//		return false;
//}
*/
