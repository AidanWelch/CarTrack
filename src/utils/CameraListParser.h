#ifndef CARTRACK_UTILS_CAMERALISTPARSER_H_
#define CARTRACK_UTILS_CAMERALISTPARSER_H_

#include <string>
#include <list>
#include <map>

struct Camera {
    std::string description, direction, latitude, longitude;
    std::string url, encoding, format, update_rate, marked_for_review;
};

typedef std::list <Camera> County;
typedef std::map <std::string, County> State;
typedef std::map <std::string, State> CameraList;
// Structured [(state_name, [(county_name, [cameras]), ...]), ...]

CameraList CameraParse(std::string file_path);

#endif