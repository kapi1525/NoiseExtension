#include "Common.h"


void Extension::set_seed(int seed) {
	this->seed = seed;
	noise.SetSeed(seed);
}


void Extension::set_noise_type(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::NoiseType_Value) {
		DarkEdif::MsgBox::WarningOK(_T("Set Noise type"), _T("Set Noise type action expects one of noise types (see: Noise type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise.SetNoiseType((FastNoiseLite::NoiseType)type);
	noise_type = type;
}

void Extension::set_noise_frequency(float frequency) {
	noise.SetFrequency(frequency);
}


void Extension::set_fractal_type(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::FractalType_PingPong) {
		DarkEdif::MsgBox::WarningOK(_T("Set fractal type"), _T("Set fractal type action expects one of fractal types (see: Fractal type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise.SetFractalType((FastNoiseLite::FractalType)type);
	fractal_type = type;
}

void Extension::set_fractal_octaves(int octaves) {
	noise.SetFractalOctaves(octaves);
}

void Extension::set_fractal_lacunarity(float lacunarity) {
	noise.SetFractalLacunarity(lacunarity);
}

void Extension::set_fractal_gain(float gain) {
	noise.SetFractalGain(gain);
}

void Extension::set_fractal_weighted(float weighted) {
	noise.SetFractalWeightedStrength(weighted);
}

void Extension::set_fractal_pingpong(float pingpong) {
	noise.SetFractalPingPongStrength(pingpong);
}


void Extension::set_cellular_distance_function(int function) {
	#if EditorBuild
	if(function < 0 || function > FastNoiseLite::FractalType_PingPong) {
		DarkEdif::MsgBox::WarningOK(_T("Set cellular distance function"), _T("Set cellular distance function action expects one of cellular distance functions (see: Cellular distance functions expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise.SetCellularDistanceFunction((FastNoiseLite::CellularDistanceFunction)function);
	cellular_function = function;
}

void Extension::set_cellular_return_type(int return_type) {
	#if EditorBuild
	if(return_type < 0 || return_type > FastNoiseLite::FractalType_PingPong) {
		DarkEdif::MsgBox::WarningOK(_T("Set cellular return type"), _T("Set cellular return type action expects one of cellular return types (see: Cellular return types expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise.SetCellularReturnType((FastNoiseLite::CellularReturnType)return_type);
	cellular_return_type = return_type;
}

void Extension::set_cellular_jitter(float jitter) {
	noise.SetCellularJitter(jitter);
}