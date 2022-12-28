#include "Common.h"

#ifdef PI
	#undef PI
#endif
#define PI 3.141592741f


int Extension::get_seed() {
	return seed;
}

int Extension::string_to_seed(const TCHAR* String) {
	std::string Text = DarkEdif::TStringToANSI(std::tstring(String));

	unsigned int Seed = 0;

	for (size_t i = 0; i < Text.length(); i++) {
		if (Text.at(i) >= '0' && Text.at(i) <= '9') {
			Seed = Seed * 10;
			Seed = Seed + (Text.at(i) - 48);
		}
		else {
			Seed = Seed * 100;
			srand((int)Text.at(i) + i);
			Seed = Seed + rand() % 99;
		}
	}

	return Seed;
}


float Extension::get_noise3D(float x, float y, float z) {
	return noise.GetNoise(x, y, z);
}

float Extension::get_noise2D(float x, float y) {
	return noise.GetNoise(x, y);
}

float Extension::get_noise1D(float x) {
	return noise.GetNoise(x, 0.f);
}

float Extension::get_looping_noise1D(float x, float xoffset, float xsize) {
	float XPos = x - xoffset;
	float Radius = xsize / (PI * 2.0f);
	float AngleStep = 360.f / xsize;
	float Angle = XPos * AngleStep;
	Angle = Angle * PI / 180.f;

	return noise.GetNoise((Radius * cos(Angle)), (Radius * sin(Angle)));
}


// Constant returns
int Extension::always_0() {
    return 0;
}

int Extension::always_1() {
    return 1;
}

int Extension::always_2() {
    return 2;
}

int Extension::always_3() {
    return 3;
}

int Extension::always_4() {
    return 4;
}

int Extension::always_5() {
    return 5;
}

int Extension::always_6() {
    return 6;
}


// Current selections
int Extension::current_noise_type() {
	return noise_type;
}

int Extension::current_rotation_type_3d() {
    return rotation_type_3d;
}

int Extension::current_fractal_type() {
	return fractal_type;
}

int Extension::current_cellular_function() {
	return cellular_function;
}

int Extension::current_cellular_return_type() {
	return cellular_return_type;
}