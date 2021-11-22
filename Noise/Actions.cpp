#include "Common.h"


void Extension::set_seed(int seed) {
	this->seed = seed;
	noise.SetSeed(seed);
}


void Extension::noise_request3D(const TCHAR* name, int x, int y, int z, int xsize, int ysize, int zsize) {
	if (x > xsize && x < 0) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: Max X must be smaller or equal than X Size (%i), but received: %i."), xsize, x);
		return;
	}
	if (xsize <= 0) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: X size must be greater than 0, but received: %i."), xsize);
		return;
	}
	if (name == _T("")) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: Name cant be blank."));
		return;
	}
	if (name == NULL) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: Somehow you passed NULL as a name."));
		return;
	}
	noise_request* request = new noise_request;
	request->noise = noise;
	request->x = x;
	request->y = y;
	request->z = z;
	request->xsize = xsize;
	request->ysize = ysize;
	request->zsize = zsize;
	request->generators.push_back(std::thread(&generator_thread, request));

	requests.insert_or_assign(name, request);
}

void Extension::noise_request2D(const TCHAR* name, int x, int y, int xsize, int ysize) {
	noise_request3D(name, x, y, 0, xsize, ysize, 1);
}

void Extension::noise_request1D(const TCHAR* name, int x, int xsize) {
	noise_request3D(name, x, 0, 0, xsize, 1, 1);
}

void Extension::noise_request_looping1D(const TCHAR* name, int x, int xsize) {
	if (x > xsize && x < 0) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: Max X must be smaller or equal than X Size (%i), but received: %i."), xsize, x);
		return;
	}
	if (xsize <= 0) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: X size must be greater than 0, but received: %i."), xsize);
		return;
	}
	if (name == _T("")) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: Name cant be blank."));
		return;
	}
	if (name == NULL) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: Somehow you passed NULL as a name."));
		return;
	}
	noise_request* request = new noise_request;
	request->noise = noise;
	request->x = x;
	request->xsize = xsize;
	request->generators.push_back(std::thread(&looping_generator_thread, request));

	requests.insert_or_assign(name, request);
}


void Extension::cleanup_request(const TCHAR* name) {
	for (auto const& [key, val] : requests) {
		if (key == name && val->ready == true) {
			delete val;
			requests.erase(key);
		}
	}
}

void Extension::cleanup_requests() {
	for (auto const& [key, val] : requests) {
		if (val->ready == true) {
			delete val;
			requests.erase(key);
		}
	}
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