#include "Common.h"

#ifdef PI
	#undef PI
#endif
#define PI 3.141592741F


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


// Noise Types
int Extension::open_simplex2() {
	return FastNoiseLite::NoiseType_OpenSimplex2;
}

int Extension::open_simplex2s() {
	return FastNoiseLite::NoiseType_OpenSimplex2S;
}

int Extension::cellular() {
	return FastNoiseLite::NoiseType_Cellular;
}

int Extension::perlin() {
	return FastNoiseLite::NoiseType_Perlin;
}

int Extension::value_cubic() {
	return FastNoiseLite::NoiseType_ValueCubic;
}

int Extension::value() {
	return FastNoiseLite::NoiseType_Value;
}


// Fractal Types
int Extension::none() {
	return FastNoiseLite::FractalType_None;
}

int Extension::fbm() {
	return FastNoiseLite::FractalType_FBm;
}

int Extension::rigid() {
	return FastNoiseLite::FractalType_Ridged;
}

int Extension::pingpong() {
	return FastNoiseLite::FractalType_PingPong;
}


// Cellular Functions
int Extension::euclidean() {
	return FastNoiseLite::CellularDistanceFunction_Euclidean;
}

int Extension::euclidean_sq() {
	return FastNoiseLite::CellularDistanceFunction_EuclideanSq;
}

int Extension::manhattan() {
	return FastNoiseLite::CellularDistanceFunction_Manhattan;
}

int Extension::hybrid() {
	return FastNoiseLite::CellularDistanceFunction_Hybrid;
}


// Cellular Return Types
int Extension::cell_value() {
	return FastNoiseLite::CellularReturnType_CellValue;
}

int Extension::distance() {
	return FastNoiseLite::CellularReturnType_Distance;
}

int Extension::distance2() {
	return FastNoiseLite::CellularReturnType_Distance2;
}

int Extension::distance2_add() {
	return FastNoiseLite::CellularReturnType_Distance2Add;
}

int Extension::distance2_sub() {
	return FastNoiseLite::CellularReturnType_Distance2Sub;
}

int Extension::distance2_mul() {
	return FastNoiseLite::CellularReturnType_Distance2Mul;
}

int Extension::distance2_div() {
	return FastNoiseLite::CellularReturnType_Distance2Div;
}


// Current selections
int Extension::current_noise_type() {
	return noise_type;
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