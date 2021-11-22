#include "Common.h"


void generator_thread(noise_request* request) {
	int xsize = request->xsize;
	int ysize = request->ysize;
	int zsize = request->zsize;

	int x = request->x;
	int y = request->y;
	int z = request->z;
	float xt, yt, zt;

	vector3d(float) generated_noise = init_vector3d(float, xsize, ysize, zsize);
	FastNoiseLite noise = request->noise;


	for (int iz = 0; iz < zsize; iz++) {
		for (int iy = 0; iy < ysize; iy++) {
			for (int ix = 0; ix < xsize; ix++) {
				xt = (x / (xsize + 0.f)) * ix;
				yt = (y / (ysize + 0.f)) * iy;
				zt = (z / (zsize + 0.f)) * iz;
				generated_noise[ix][iy][iz] = noise.GetNoise(xt, yt, zt);
			}
		}
	}

	request->generated_noise = generated_noise;
	request->ready = true;
}


void looping_generator_thread(noise_request* request) {
	int xsize = request->xsize;
	int x = request->x;
	float xt, radius, angle_step, angle;

	vector3d(float) generated_noise = init_vector3d(float, xsize, 0, 0);
	FastNoiseLite noise = request->noise;


	for (int ix = 0; ix < xsize; ix++) {
		xt = (x / (xsize + 0.f)) * ix;

		radius = xsize / (PI * 2.0f);
		angle_step = 360.f / xsize;
		angle = xt * angle_step;
		angle = angle * PI / 180.f;

		generated_noise[ix][0][0] = noise.GetNoise((radius * cos(angle)), (radius * sin(angle)));
	}

	request->generated_noise = generated_noise;
	request->ready = true;
}