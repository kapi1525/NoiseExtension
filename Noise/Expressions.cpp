#include "Common.h"

int Extension::GetSeed() {
	return Seed;
}

int Extension::StringToSeed(const TCHAR* String) {
	std::string Text = TStringToANSI(std::tstring(String));

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


float Extension::GetNoise3D(float x, float y, float z) {
	return Noise.GetNoise(x, y, z);
}

float Extension::GetNoise2D(float x, float y) {
	return Noise.GetNoise(x, y);
}

float Extension::GetNoise1D(float x) {
	return Noise.GetNoise(x, 0.f);
}

float Extension::GetLoopingNoise1D(float x, float xoffset, float xsize) {
	float XPos = x - xoffset;
	float Radius = xsize / ((float)PI * 2.0f);
	float AngleStep = 360.f / xsize;
	float Angle = XPos * AngleStep;
	Angle = Angle * (float)PI / 180.f;

	return Noise.GetNoise((Radius * cos(Angle)), (Radius * sin(Angle)));
}


float Extension::GetRequestNoise3D(const TCHAR* name, float x, float y, float z) {
	NoiseRequest* r = Requests[name];

	int xt = ((r->xsize + 0.f) / r->x) * x;
	int yt = ((r->ysize + 0.f) / r->y) * y;
	int zt = ((r->zsize + 0.f) / r->z) * z;

	//DarkEdif::MsgBox::Info(_T("inf"), _T("%f %f %f, %i %i %i"), x, y, z, xt, yt, zt);

	return r->GeneratedNoise[xt][yt][zt];
}

float Extension::GetRequestNoise2D(const TCHAR* name, float x, float y) {
	NoiseRequest* r = Requests[name];

	int xt = ((r->xsize + 0.f) / r->x) * x;
	int yt = ((r->ysize + 0.f) / r->y) * y;

	//DarkEdif::MsgBox::Info(_T("inf"), _T("%f %f, %i %i"), x, y, xt, yt);

	return r->GeneratedNoise[xt][yt][0];
}

float Extension::GetRequestNoise1D(const TCHAR* name, float x) {
	NoiseRequest* r = Requests[name];

	int xt = ((r->xsize + 0.f) / r->x) * x;

	//DarkEdif::MsgBox::Info(_T("inf"), _T("%f, %i"), x, xt);

	return r->GeneratedNoise[xt][0][0];
}

// TODO: float GetRequestLoopingNoise1D(float x, float xoffset, float xsize) {}



// Noise Types
int Extension::OpenSimplex2() {
	return FastNoiseLite::NoiseType_OpenSimplex2;
}

int Extension::OpenSimplex2S() {
	return FastNoiseLite::NoiseType_OpenSimplex2S;
}

int Extension::Cellular() {
	return FastNoiseLite::NoiseType_Cellular;
}

int Extension::Perlin() {
	return FastNoiseLite::NoiseType_Perlin;
}

int Extension::ValueCubic() {
	return FastNoiseLite::NoiseType_ValueCubic;
}

int Extension::Value() {
	return FastNoiseLite::NoiseType_Value;
}


// Fractal Types
int Extension::None() {
	return FastNoiseLite::FractalType_None;
}

int Extension::FBm() {
	return FastNoiseLite::FractalType_FBm;
}

int Extension::Rigid() {
	return FastNoiseLite::FractalType_Ridged;
}

int Extension::PingPong() {
	return FastNoiseLite::FractalType_PingPong;
}


// Cellular Functions
int Extension::Euclidean() {
	return FastNoiseLite::CellularDistanceFunction_Euclidean;
}

int Extension::EuclideanSq() {
	return FastNoiseLite::CellularDistanceFunction_EuclideanSq;
}

int Extension::Manhattan() {
	return FastNoiseLite::CellularDistanceFunction_Manhattan;
}

int Extension::Hybrid() {
	return FastNoiseLite::CellularDistanceFunction_Hybrid;
}


// Cellular Return Types
int Extension::CellValue() {
	return FastNoiseLite::CellularReturnType_CellValue;
}

int Extension::Distance() {
	return FastNoiseLite::CellularReturnType_Distance;
}

int Extension::Distance2() {
	return FastNoiseLite::CellularReturnType_Distance2;
}

int Extension::Distance2Add() {
	return FastNoiseLite::CellularReturnType_Distance2Add;
}

int Extension::Distance2Sub() {
	return FastNoiseLite::CellularReturnType_Distance2Sub;
}

int Extension::Distance2Mul() {
	return FastNoiseLite::CellularReturnType_Distance2Mul;
}

int Extension::Distance2Div() {
	return FastNoiseLite::CellularReturnType_Distance2Div;
}


// Current selections
int Extension::CurrentNoiseType() {
	return NoiseType;
}

int Extension::CurrentFractalType() {
	return FractalType;
}

int Extension::CurrentCellularFunction() {
	return CellularFunction;
}

int Extension::CUrrentCellularReturnType() {
	return CellularReturnType;
}