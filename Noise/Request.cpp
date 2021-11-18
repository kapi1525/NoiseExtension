#include "Common.h"



void NoiseRequest::Thread() {
	GeneratedNoise = std::vector<std::vector<std::vector<float>>>(xsize, std::vector<std::vector<float>>(ysize, std::vector<float>(zsize)));

	for (size_t iz = 0; iz < zsize; iz++) {
		for (size_t iy = 0; iy < ysize; iy++) {
			for (size_t ix = 0; ix < xsize; ix++) {
				GeneratedNoise[ix][iy][iz] = Noise.GetNoise((float)ix + x, (float)iy + y, (float)iz + z);
			}
		}
	}

	Ready = true;
}