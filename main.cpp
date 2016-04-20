#include "RayTracer.h"
#include "bmp.h"
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
extern const float EPS = 0.001;
int main()
{
	Bmp image(300, 300);
	RayTracer RT;
	Vec3 eye(150, -150, 300);
	for (int i = 0; i < 300; i++)
		for (int j = 0; j < 300; j++)
		{
			Color color = RT.rayTrace(eye, Vec3(j, 0, i) - eye, 1, RT.spotLight.color);
			//if(i>100&& i<200 && j>100 && j<200) cout << color.r << " " << color.g << " " << color.b << endl;
			image.SetColor(i, j, color);
		}
	image.Output("3.bmp");
	return 0;
}