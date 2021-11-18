#pragma once
#include <string>
#include <vector>

#include "DarkEdif.h"
#include "FastNoiseLite.h"


class NoiseRequest {
public:
	FastNoiseLite Noise;
	bool Ready = false;

	int x = 0;
	int	y = 0;
	int z = 0;
	size_t xsize = 1;
	size_t ysize = 1;
	size_t zsize = 1;

	std::vector<std::vector<std::vector<float>>> GeneratedNoise;

	void Thread();
};