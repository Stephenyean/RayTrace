#include "RayTracer.h"
#include "bmp.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//#pragma warning(disable:4996)
//extern const float EPS = 0.001;
int main(int argc,char** argv)
{
	ifstream fin(argv[1]);
	int M,N;
	string name;
	fin>>name>>M>>name>>N;
	int md;
	float mw;
	fin>>name>>md>>name>>mw;
	Bmp image(M, N);
	float Kd,Kr,Ks,lr,lg,lb,lW,lambda;
	int lx,ly,lz,Ra;
	
	
	fin>>name>>lx>>name>>ly>>name>>lz>>name>>lr>>name>>lg>>name>>lb>>name>>lW>>name>>lambda;
	int Ex,Ey,Ez;
	fin>>name>>Ex>>name>>Ey>>name>>Ez;
	//cout<<Ex<<Ey<<Ez<<endl;
	Vec3 eye(Ex, Ey, Ez);
	int objectNum;
	fin>>name>>objectNum;
	string objectType;
//	Object* O=new Object[objectNum];
	Object** O=new Object*[10];
	for(int i=0;i<objectNum;i++)
	{
		fin>>objectType;
		if(objectType==string("Circle"))
		{
			float Ox,Oy,Oz,Ra,Or,Og,Ob;
			fin>>name>>Ox>>name>>Oy>>name>>Oz>>name>>Ra>>name>>Or>>name>>Og>>name>>Ob>>name>>Kd>>name>>Kr>>name>>Ks;
			Sphere* circle=new Sphere(Vec3(Ox,Oy,Oz),Ra,Color(Or,Og,Ob),Kd,Kr,Ks);
			O[i]=circle;
		}
		if(objectType==string("Panel"))
		{
			float A,B,C,D,Or,Og,Ob;
			fin>>name>>A>>name>>B>>name>>C>>name>>D>>name>>Or>>name>>Og>>name>>Ob>>name>>Kd>>name>>Kr>>name>>Ks;
			Panel* panel=new Panel(Vec3(A,B,C),D,Color(Or,Og,Ob),Kd,Kr,Ks);
			O[i]=panel;
		}
	}
	RayTracer RT(md,mw,objectNum,O, lx, ly, lz, lr, lg, lb, lW, lambda);
	for (int i = -M/2; i < M/2; i++)
		for (int j = -M/2; j < N/2; j++)
		{
			//Color color(1,1,0);
			//RayTracer RT(md,mw,Ox, Oy, Oz, Ra, Or, Og, Ob, Kd, Kr, Ks, lx, ly, lz, lr, lg, lb, lW, lambda);
			Vec3 S=eye;
			Vec3 D=Vec3(j,-200,i)-eye;D.norm();
			Ray inRay(S,D,1.0,RT.spotLight.color,0);
			if(i==20 && j==0) RT.verbose=1;
			else RT.verbose=0;
			Color color = RT.rayTrace(inRay );
			//if(i>100&& i<200 && j>100 && j<200) cout << color.r << " " << color.g << " " << color.b << endl;
			if(i==20 && j==0) 
				cout<<color.r<<" "<<color.g<<" "<<color.b<<" ";
			if(i==-20 && j==0) 
				cout<<color.r<<" "<<color.g<<" "<<color.b<<" ";
			image.SetColor(i+M/2, j+N/2, color);
		}
	image.Output(argv[2]);
	return 0;
}
