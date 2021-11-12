#include "Common.h"

void Extension::SetSeed(int Seed) {
	this->Seed = Seed;
	Noise.SetSeed(Seed);
}


void Extension::SetNoiseType(int Type) {
	Noise.SetNoiseType((FastNoiseLite::NoiseType)Type);
}

void Extension::SetNoiseFrequency(float Frequency) {
	Noise.SetFrequency(Frequency);
}


void Extension::SetFractalType(int Type) {
	Noise.SetFractalType((FastNoiseLite::FractalType)Type);
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
}

void Extension::SetCellularReturnType(int Return) {
	Noise.SetCellularReturnType((FastNoiseLite::CellularReturnType)Return);
}

void Extension::SetCellularJitter(float Jitter) {
	Noise.SetCellularJitter(Jitter);
}