#include "color.h"
#include "RayTracer.h"
#include "math.h"
#include "Object.h"
#include <iostream>
using namespace std;
void print(Vec3 v)
{
	cout<<v.x<<" "<<v.y<<" "<<v.z<<endl;
}
void print(Color v)
{
	cout<<v.r<<" "<<v.g<<" "<<v.b<<endl;
}
Color RayTracer::rayTrace(Ray& inRay)
{
	
	Color color(0,0,0);
	if(inRay.depth>MAX_DEPTH)
		return color;
	if(inRay.weight<MIN_WEIGHT)
		return color;
	Intersection result;//result.intersected=false;result.t=1e20;//=O.intersect(inRay);
	Object* currentO=nullptr;
	for(int i=0;i<objectNum;i++)
	{
		Intersection inter=O[i]->intersect(inRay);
		if(inter.intersected && inter.t<result.t)
		{
			result=inter;
			currentO=O[i];
		}
	}
	if(verbose>0)
	{
		cout<<result.in<<" "<<result.intersected<<endl;
	}
	if(result.intersected==false)
		return color;
	float t=result.t;
	Vec3 I=inRay.Start+inRay.D*t;
	Vec3 Normal= currentO->getNormal(I,result.in,inRay.D);//(result.in)?(currentO->center-I):(I-currentO->center);Normal.norm();
	//I=I+Normal*0.01;
	Vec3 In=Vec3(0,0,0)-inRay.D;
	Vec3 Out=Normal*(2*In.dot(Normal))-In;
	color+=calDiffusion(inRay,I+Normal*0.01,Normal,Out,result.in,currentO);
	Ray outRay(I+Normal*0.01,Out,inRay.weight*lambda,inRay.color,inRay.depth+1);
	//outRay.Start=I; outRay.D=Out; outRay.weight=inRay.weight*lambda; outRay.depht=inRay.depth+1;
	color+=calRefraction(inRay,I,Normal,result.in,currentO);
	color+=rayTrace(outRay);
	return color;
}

Color RayTracer:: calDiffusion(Ray& inRay, Vec3 I, Vec3 Normal, Vec3 Out, bool in, Object* currentO)
{
	Color color(0,0,0);
	//I=I+0.01*(I-O.center);
	if(in) return color;//Normal=Vec3(0,0,0)-Normal;
	Vec3 S=spotLight.place-I;S.norm();
	if(verbose>0)
	{
		cout<<"Difussion\n";
		print(S);
		print(I);
		print(Normal);
	}
/*	Intersection result=O.intersect(I,S);
	if(result.intersected==true)
		return color;*/
	// check the shadow
	if(Normal.dot(S)<eps)
		return color;
	Ray outRay(I,S);
	float distanceToLight=(spotLight.place-I).abs();
	for(int i=0;i<objectNum;i++)
	{
		Intersection inter=O[i]->intersect(outRay);
		if(inter.intersected && inter.t<distanceToLight)
			return color;
	}
	color+=inRay.color*currentO->color * inRay.weight * currentO->Kd * Normal.dot(S);
	if(Out.dot(S)>0)
		color+=inRay.color*currentO->color * inRay.weight * currentO->Kr * pow(Out.dot(S),50);
	return color;
}

Color RayTracer::calRefraction(Ray& inRay, Vec3 I, Vec3 Normal, bool in, Object* currentO)
{
//	if(inRay.depth>2)
//		cout<<inRay.depth<<endl;
	Color color(0,0,0);
	return color;
	Vec3 In=inRay.D;
	I=I-Normal*0.01;
	float k=0,k2;
	Normal=Vec3(0,0,0)-Normal;
	float cosT=Normal.dot(In);
	if(cosT>1.0) cosT=1.0;
	float sinT=sqrt(1-cosT*cosT);
	if(in==false)
	{
		float sinA=0.8*sinT;
		float cosA=sqrt(1-sinA*sinA);
		if((k2=sinT*cosA-cosT*sinA)<eps)
			k=1.0;
		else
			k=sinA/k2;
	}
	else
	{
		if(sinT>0.8)
			return Color(0,0,0);
		float sinA=1.25*sinT;
		if(sinA>1.0) sinA=1.0;
		float cosA=sqrt(1-sinA*sinA);
		if((k2=sinA*cosT-cosA*sinT)<eps)
			k=1.0;
		else
			k=sinT/k2;
	}
	Vec3 Out=Normal+In*k;Out.norm();
	Ray outRay(I,Out,inRay.weight*currentO->Ks,inRay.color,inRay.depth+1);
	while(in==true)
	{
		Vec3 S=spotLight.place-I;S.norm();
		if(S.dot(Out)<1-1e-4) break;
		Ray outRay2(I,S);
		for(int i=0;i<objectNum;i++)
		{
			Intersection inter=O[i]->intersect(outRay2);
			if(inter.intersected)
				break;
		}
		if(Normal.dot(S)>eps)
			color+=inRay.color*currentO->color * inRay.weight * ( currentO->Kd * Out.dot(S));// + currentO->Kr * pow(Out.dot(S),10));
		break;
	}
		if(verbose>0)
		{
			cout<<"verbose="<<verbose<<endl;
			cout<<color.r<<" "<<color.g<<" "<<color.b<<endl;
			cout<<"depth="<<inRay.depth<<endl;
			cout<<"Normal= ";
			print(Normal);
			cout<<"In= ";
			print(In);
			cout<<"Out= ";
			print(Out);
			//print(currentO->center-I);
			//cout<<(currentO->center-I).abs()<<endl;
			
		}
	return color+rayTrace(outRay);
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
