main.exe: Ray.h Object.h RayTracer.h RayTracer.cpp main.cpp
	g++ object.cpp RayTracer.cpp color.cpp bmp.cpp main.cpp -o main.exe
clean:
	rm main.exe
