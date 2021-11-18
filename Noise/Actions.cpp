#include "Common.h"

void Extension::SetSeed(int Seed) {
	this->Seed = Seed;
	Noise.SetSeed(Seed);
}


void Extension::NoiseRequest3D(const TCHAR* name, int x, int y, int z, int xsize, int ysize, int zsize) {
	if (xsize <= 0) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: X size must be greater than 0, but received: %u."), xsize);
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
	NoiseRequest* request = new NoiseRequest;
	request->Noise = Noise;
	request->x = x;
	request->y = y;
	request->z = z;
	request->xsize = xsize;
	request->ysize = ysize;
	request->zsize = zsize;
	
	std::thread generator(&NoiseRequest::Thread, request);
	generator.detach();

	Requests.insert_or_assign(name, request);
}

void Extension::NoiseRequest2D(const TCHAR* name, int x, int y, int xsize, int ysize) {
	if (xsize <= 0) {
		DarkEdif::MsgBox::Error(_T("Error"), _T("Failed to create noise request: X size must be greater than 0, but received: %u."), xsize);
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
	NoiseRequest* request = new NoiseRequest;
	request->Noise = Noise;
	request->x = x;
	request->y = y;
	request->xsize = xsize;
	request->ysize = ysize;

	std::thread generator(&NoiseRequest::Thread, request);
	generator.detach();

	Requests.insert_or_assign(name, request);
}

void Extension::NoiseRequest1D(const TCHAR* name, int x, int xsize) {
	if (xsize <= 0) {
		DarkEdif::MsgBox::Error(_T("Noise error"), _T("Failed to create noise request: X size must be greater than 0, but received: %u."), xsize);
		return;
	}
	if (name == _T("")) {
		DarkEdif::MsgBox::Error(_T("Noise error"), _T("Failed to create noise request: Name cant be blank."));
		return;
	}
	if (name == NULL) {
		DarkEdif::MsgBox::Error(_T("Noise error"), _T("Failed to create noise request: Somehow you passed NULL as a name."));
		return;
	}
	NoiseRequest* request = new NoiseRequest;
	request->Noise = Noise;
	request->xsize = xsize;

	std::thread generator(&NoiseRequest::Thread, request);
	generator.detach();

	Requests.insert_or_assign(name, request);
}

// TODO: void NoiseRequestLooping1D() {}


void Extension::CleanupRequest(const TCHAR* name) {
	for (auto const& [key, val] : Requests) {
		if (key == name && val->Ready == true) {
			delete val;
			Requests.erase(key);
		}
	}
}

void Extension::CleanupRequests() {
	for (auto const& [key, val] : Requests) {
		if (val->Ready == true) {
			delete val;
			Requests.erase(key);
		}
	}
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