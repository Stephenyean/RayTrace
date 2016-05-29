#include "Object.h"

Intersection Sphere::intersect(Vec3 S, Vec3 d)
{
	Intersection result;
	result.in = false; result.intersected = false;
	Vec3 co = center-S;
	if (co.abs() - R<eps)
	{
		result.in = true;
		result.intersected=true;
		//return result;
	}
	if(result.in==false)
	{
		float delta=co.dot(d);
		if(delta<0) return result;
		else
		{
			float t=delta*delta-(co.dot(co)-R*R);
			if(t<0)
				return result;
			result.intersected=true;
			result.t=delta-sqrt(R*R-co.dot(co)+delta*delta);
		}
	}
	else
	{
		float delta=co.dot(d);
		if(delta>0)
		{
			float v2=co.dot(co)-delta*delta;
			result.t=delta+sqrt(R*R-v2);
		}
		else
		{
			float v2=co.dot(co)-delta*delta;
			result.t=sqrt(R*R-v2)-delta;
		}
	}
	return result;
	/*float d_co = d.dot(co);
	float delta = d_co*d_co - d.dot(d)*(co.dot(co)-R*R);
	if (delta<eps)
		return result;
	float t1 = (-2 * d_co - sqrt(delta)) / (2 * d.dot(d));
	if (t1>eps)
	{
		result.intersected = true; result.t = t1;
		return result;
	}
	float t2 = (-2 * d_co + sqrt(delta)) / (2 * d.dot(d));
	if (t2>eps)
	{
		result.intersected = true; result.t = t2;
	}
	return result;
	*/
}
Intersection Sphere::intersect(Ray& ray)
{
	return intersect(ray.Start, ray.D);
}
Vec3 Sphere::getNormal(Vec3 I,bool in,Vec3 d)
{
	Vec3 Normal;
	if(in)
		Normal=center-I;
	else
		Normal=I-center;
	Normal.norm();
	return Normal;
}

Intersection Panel::intersect(Ray& ray)
{
	return intersect(ray.Start, ray.D);
	
}
/*float abs(float a)
{
	return a>0?a:-a;
}*/
Intersection Panel::intersect(Vec3 S ,Vec3 d)
{
	Intersection result;
	float a=direction.dot(d);
	if(abs(a)<eps)
		return result;
	float t=(-1*distance-direction.dot(S))/a;
	if(t<eps)
		return result;
	result.intersected=true;
	result.t=t;
	return result;
}
Vec3 Panel::getNormal(Vec3 I,bool in,Vec3 d)
{
	Vec3 result=direction;
	result.norm();
	if(d.dot(result)>0) result=Vec3(0,0,0)-result;
	return result;
}
