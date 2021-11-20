#include "Common.h"



void NoiseRequest::Thread() {
	if (!Looping) {
		GeneratedNoise = init_vector3d(float, xsize, ysize, zsize);
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
	else {
		GeneratedNoise = init_vector3d(float, xsize, 1, 1);

		float xt, Radius, AngleStep, Angle;

		for (int ix = 0; ix < xsize; ix++) {
			xt = (x / (xsize + 0.f)) * ix;

			Radius = xsize / ((float)PI * 2.0f);
			AngleStep = 360.f / xsize;
			Angle = xt * AngleStep;
			Angle = Angle * (float)PI / 180.f;

			GeneratedNoise[ix][0][0] = Noise.GetNoise((Radius * cos(Angle)), (Radius * sin(Angle)));
		}

		Ready = true;
	}
}