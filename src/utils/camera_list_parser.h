#ifndef CARTRACK_UTILS_CAMERALISTPARSER_H_
#define CARTRACK_UTILS_CAMERALISTPARSER_H_

#include <string>
#include <vector>

struct Camera {
	float latitude, longitude;
	std::string state, county, description, direction;
	std::string url, encoding, format, update_rate, marked_for_review;
};

using CameraList = std::vector <Camera>;

CameraList CameraParse(std::string file_path);

#endif