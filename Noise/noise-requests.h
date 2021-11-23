#pragma once
#include <string>
#include <vector>

#include "DarkEdif.h"
#include "FastNoiseLite.h"

#ifdef PI
	#undef PI
#endif
#define PI 3.141592741F

#define vector3d(type) std::vector<std::vector<std::vector<type>>>
#define vector2d(type) std::vector<std::vector<type>>
#define vector1d(type) std::vector<type>

#define init_vector3d(type, xsize, ysize, zsize) std::vector<std::vector<std::vector<type>>>(xsize, std::vector<std::vector<type>>(ysize, std::vector<type>(zsize)))
#define init_vector2d(type, xsize, ysize) std::vector<std::vector<type>>(xsize, std::vector<type>(ysize))
#define init_vector1d(type, xsize) std::vector<type>(xsize)


struct noise_request {
	FastNoiseLite noise;
	bool ready;

	int x, y, z;
	int xsize, ysize, zsize;

	vector3d(float) generated_noise;
	vector1d(std::thread) generators;
};

void generator_thread(noise_request* request);
void looping_generator_thread(noise_request* request);