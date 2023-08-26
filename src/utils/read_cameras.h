#ifndef CARTRACK_UTILS_READCAMERAS_H_
#define CARTRACK_UTILS_READCAMERAS_H_

#include <string>
#include <vector>

struct Camera {
	float latitude, longitude;
	std::string state, county, description, direction;
	std::string url, encoding, format, update_rate, marked_for_review;
};

using CameraVector = std::vector<Camera>;

CameraVector read_cameras( char*& file_path );

#endif