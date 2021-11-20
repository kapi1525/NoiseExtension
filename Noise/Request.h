#pragma once
#include <string>
#include <vector>

#include "DarkEdif.h"
#include "FastNoiseLite.h"


#define vector3d std::vector<std::vector<std::vector<float>>>


class NoiseRequest {
public:
	FastNoiseLite Noise;
	bool Ready = false;

	int x = 0;
	int y = 0;
	int z = 0;
	int xsize = 1;
	int ysize = 1;
	int zsize = 1;

	vector3d GeneratedNoise;

	void Thread();
};