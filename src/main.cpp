#include <iostream>
#include <span>
#include <ostream>
// #include <opencv2/opencv.hpp> //namespace cv
#include "utils/camera_list_parser.h"


std::ostream &operator<<(std::ostream &os, Camera const &c) {
	return os << c.latitude << ", " << c.longitude << ' ' << c.state << ' ' << c.county << ' ' << c.description;
}

int main(int argc, char** argv){
	if ( argc == 0 ) {
		std::cerr << "Provide a path to the camera list" << std::endl;
		return 1;
	}
	auto args = std::span(argv, size_t(argc));
	CameraList cameras = CameraParse(args[1]);
	std::cout << cameras.size() << std::endl;
	std::cout << cameras.front() << std::endl;
	std::cout << cameras.back() << std::endl;
	return 0;
}

