#include "Common.h"




void Extension::set_seed(int seed_) {
	seed = seed_;
	noise_main.SetSeed(seed);
}



void Extension::set_noise_type(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::NoiseType_Value) {
		DarkEdif::MsgBox::WarningOK(_T("Set Noise type"), _T("Set Noise type action expects one of noise types (see: Noise type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise_main.SetNoiseType((FastNoiseLite::NoiseType)type);
	noise_type = type;
}

void Extension::set_noise_frequency(float frequency) {
	noise_main.SetFrequency(frequency);
}


void Extension::set_fractal_type(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::FractalType_PingPong) {
		DarkEdif::MsgBox::WarningOK(_T("Set fractal type"), _T("Set fractal type action expects one of fractal types (see: Fractal type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise_main.SetFractalType((FastNoiseLite::FractalType)type);
	fractal_type = type;
}


void Extension::set_rotation_type_3d(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::RotationType3D_ImproveXZPlanes) {
		DarkEdif::MsgBox::WarningOK(_T("Set rotation type 3D"), _T("Set rotation type 3D action expects one of rotation types 3d (see: Rotation type 3D expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise_main.SetRotationType3D((FastNoiseLite::RotationType3D)type);
	rotation_type_3d = type;
}



void Extension::set_fractal_octaves(int octaves) {
	noise_main.SetFractalOctaves(octaves);
}

void Extension::set_fractal_lacunarity(float lacunarity) {
	noise_main.SetFractalLacunarity(lacunarity);
}

void Extension::set_fractal_gain(float gain) {
	noise_main.SetFractalGain(gain);
}

void Extension::set_fractal_weighted(float weighted) {
	noise_main.SetFractalWeightedStrength(weighted);
}

void Extension::set_fractal_pingpong(float pingpong) {
	noise_main.SetFractalPingPongStrength(pingpong);
}



void Extension::set_cellular_distance_function(int function) {
	#if EditorBuild
	if(function < 0 || function > FastNoiseLite::CellularDistanceFunction_Hybrid) {
		DarkEdif::MsgBox::WarningOK(_T("Set cellular distance function"), _T("Set cellular distance function action expects one of cellular distance functions (see: Cellular distance functions expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise_main.SetCellularDistanceFunction((FastNoiseLite::CellularDistanceFunction)function);
	cellular_function = function;
}

void Extension::set_cellular_return_type(int return_type) {
	#if EditorBuild
	if(return_type < 0 || return_type > FastNoiseLite::CellularReturnType_Distance2Div) {
		DarkEdif::MsgBox::WarningOK(_T("Set cellular return type"), _T("Set cellular return type action expects one of cellular return types (see: Cellular return types expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise_main.SetCellularReturnType((FastNoiseLite::CellularReturnType)return_type);
	cellular_return_type = return_type;
}

void Extension::set_cellular_jitter(float jitter) {
	noise_main.SetCellularJitter(jitter);
}