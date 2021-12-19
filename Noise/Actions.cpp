#include "Common.h"


void Extension::set_seed(int seed) {
	this->seed = seed;
	noise.SetSeed(seed);
}


void Extension::set_noise_type(int type) {
	noise.SetNoiseType((FastNoiseLite::NoiseType)type);
	noise_type = type;
}

void Extension::set_noise_frequency(float frequency) {
	noise.SetFrequency(frequency);
}


void Extension::set_fractal_type(int type) {
	noise.SetFractalType((FastNoiseLite::FractalType)type);
	fractal_type = type;
}

void Extension::set_fractal_octaves(int octaves) {
	noise.SetFractalOctaves(octaves);
}

void Extension::set_fractal_lacunarity(float lacunarity) {
	noise.SetFractalLacunarity(lacunarity);
}

void Extension::set_fractal_weighted(float weighted) {
	noise.SetFractalWeightedStrength(weighted);
}

void Extension::set_fractal_pingpong(float pingpong) {
	noise.SetFractalPingPongStrength(pingpong);
}


void Extension::set_cellular_distance_function(int function) {
	noise.SetCellularDistanceFunction((FastNoiseLite::CellularDistanceFunction)function);
	cellular_function = function;
}

void Extension::set_cellular_return_type(int return_type) {
	noise.SetCellularReturnType((FastNoiseLite::CellularReturnType)return_type);
	cellular_return_type = return_type;
}

void Extension::set_cellular_jitter(float jitter) {
	noise.SetCellularJitter(jitter);
}