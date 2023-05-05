#include "Common.h"



void Extension::set_seed(int seed) {
	noise_seed = seed;
	fnl_noise.SetSeed(noise_seed);
}



void Extension::set_noise_type(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::NoiseType_Value) {
		DarkEdif::MsgBox::WarningOK(_T("Set Noise type"), _T("Set Noise type action expects one of noise types (see: Noise type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise_type = static_cast<FastNoiseLite::NoiseType>(type);
	fnl_noise.SetNoiseType(noise_type);
}

void Extension::set_noise_frequency(float frequency) {
	fnl_noise.SetFrequency(frequency);
}

void Extension::set_rotation_type_3d(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::RotationType3D_ImproveXZPlanes) {
		DarkEdif::MsgBox::WarningOK(_T("Set rotation type 3D"), _T("Set rotation type 3D action expects one of rotation types 3d (see: Rotation type 3D expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	rotation_type_3d = static_cast<FastNoiseLite::RotationType3D>(type);
	fnl_noise.SetRotationType3D(rotation_type_3d);
}



void Extension::set_fractal_type(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::FractalType_PingPong) {
		DarkEdif::MsgBox::WarningOK(_T("Set fractal type"), _T("Set fractal type action expects one of fractal types (see: Fractal type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	fractal_type = static_cast<FastNoiseLite::FractalType>(type);
	fnl_noise.SetFractalType(fractal_type);
}


void Extension::set_fractal_octaves(int octaves) {
	fnl_noise.SetFractalOctaves(octaves);
}

void Extension::set_fractal_lacunarity(float lacunarity) {
	fnl_noise.SetFractalLacunarity(lacunarity);
}

void Extension::set_fractal_gain(float gain) {
	fnl_noise.SetFractalGain(gain);
}

void Extension::set_fractal_weighted(float weighted) {
	fnl_noise.SetFractalWeightedStrength(weighted);
}

void Extension::set_fractal_pingpong(float pingpong) {
	fnl_noise.SetFractalPingPongStrength(pingpong);
}



void Extension::set_cellular_distance_function(int function) {
	#if EditorBuild
	if(function < 0 || function > FastNoiseLite::CellularDistanceFunction_Hybrid) {
		DarkEdif::MsgBox::WarningOK(_T("Set cellular distance function"), _T("Set cellular distance function action expects one of cellular distance functions (see: Cellular distance functions expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	cellular_function = static_cast<FastNoiseLite::CellularDistanceFunction>(function);
	fnl_noise.SetCellularDistanceFunction(cellular_function);
}

void Extension::set_cellular_return_type(int return_type) {
	#if EditorBuild
	if(return_type < 0 || return_type > FastNoiseLite::CellularReturnType_Distance2Div) {
		DarkEdif::MsgBox::WarningOK(_T("Set cellular return type"), _T("Set cellular return type action expects one of cellular return types (see: Cellular return types expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	cellular_return_type = static_cast<FastNoiseLite::CellularReturnType>(return_type);
	fnl_noise.SetCellularReturnType(cellular_return_type);
}

void Extension::set_cellular_jitter(float jitter) {
	fnl_noise.SetCellularJitter(jitter);
}