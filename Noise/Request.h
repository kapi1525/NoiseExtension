#pragma once
#include <string>
#include <vector>

#include "DarkEdif.h"
#include "FastNoiseLite.h"


#define vector3d(type) std::vector<std::vector<std::vector<type>>>
#define vector2d(type) std::vector<std::vector<type>>
#define vector1d(type) std::vector<type>

#define init_vector3d(type, xsize, ysize, zsize) std::vector<std::vector<std::vector<type>>>(xsize, std::vector<std::vector<type>>(ysize, std::vector<type>(zsize)))
#define init_vector2d(type, xsize, ysize) std::vector<std::vector<type>>(xsize, std::vector<type>(ysize))
#define init_vector1d(type, xsize) std::vector<type>(xsize)


class NoiseRequest {
public:
	FastNoiseLite Noise;
	bool Ready = false;
	bool Looping = false;

	int x = 0;
	int y = 0;
	int z = 0;
	int xsize = 1;
	int ysize = 1;
	int zsize = 1;

	vector3d(float) GeneratedNoise;

	void Thread();
};