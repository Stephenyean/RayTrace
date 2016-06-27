main.exe: Ray.h Object.h object.cpp RayTracer.h RayTracer.cpp main.cpp
	g++ -std=c++11 object.cpp RayTracer.cpp color.cpp bmp.cpp main.cpp -o main.exe
clean:
	rm main.exe
