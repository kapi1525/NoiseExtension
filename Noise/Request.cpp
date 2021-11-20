#include "Common.h"



void NoiseRequest::Thread() {
	GeneratedNoise = std::vector<std::vector<std::vector<float>>>(xsize, std::vector<std::vector<float>>(ysize, std::vector<float>(zsize)));
	//DarkEdif::MsgBox::Info(_T("test"), _T("%i %i %i %i %i %i"), x, xsize, y, ysize, z, zsize);

	float xt, yt, zt;

	for (int iz = 0; iz < zsize; iz++) {
		for (int iy = 0; iy < ysize; iy++) {
			for (int ix = 0; ix < xsize; ix++) {
				xt = (x / (xsize + 0.f)) * ix;
				yt = (y / (ysize + 0.f)) * iy;
				zt = (z / (zsize + 0.f)) * iz;
				GeneratedNoise[ix][iy][iz] = Noise.GetNoise(xt, yt, zt);
				//DarkEdif::MsgBox::Info(_T("test"), _T("%f %f %f"),xt, yt, zt);
			}
		}
	}

	Ready = true;
}