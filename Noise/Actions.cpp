#include "Common.h"

void Extension::SetSeed(int Seed) {
	this->Seed = Seed;
	Noise.SetSeed(Seed);
}


void NoiseRequest3D(const TCHAR* name, int x, int y, int z, int xsize, int ysize, int zsize) {

}

void NoiseRequest2D(const TCHAR* name, int x, int y, int xsize, int ysize) {

}

void NoiseRequest1D(const TCHAR* name, int x, int xsize) {

}

// TODO: void NoiseRequestLooping1D() {}


void CleanupRequest(const TCHAR* name) {

}

void CleanupRequests() {

}


void Extension::SetNoiseType(int Type) {
	Noise.SetNoiseType((FastNoiseLite::NoiseType)Type);
	NoiseType = Type;
}

void Extension::SetNoiseFrequency(float Frequency) {
	Noise.SetFrequency(Frequency);
}


void Extension::SetFractalType(int Type) {
	Noise.SetFractalType((FastNoiseLite::FractalType)Type);
	FractalType = Type;
}

void Extension::SetFractalOctaves(int Octaves) {
	Noise.SetFractalOctaves(Octaves);
}

void Extension::SetFractalLacunarity(float Lacunarity) {
	Noise.SetFractalLacunarity(Lacunarity);
}

void Extension::SetFractalWeighted(float Weighted) {
	Noise.SetFractalWeightedStrength(Weighted);
}

void Extension::SetFractalPingPong(float PingPong) {
	Noise.SetFractalPingPongStrength(PingPong);
}


void Extension::SetCellularDistanceFunction(int Function) {
	Noise.SetCellularDistanceFunction((FastNoiseLite::CellularDistanceFunction)Function);
	CellularFunction = Function;
}

void Extension::SetCellularReturnType(int Return) {
	Noise.SetCellularReturnType((FastNoiseLite::CellularReturnType)Return);
	CellularReturnType = Return;
}

void Extension::SetCellularJitter(float Jitter) {
	Noise.SetCellularJitter(Jitter);
}