#include <cstdint>
#include <iostream>
#include <ostream>
#include <span>
// #include <opencv2/opencv.hpp> //namespace cv
#include "utils/camera_kd_tree.h"
#include "utils/read_cameras.h"

std::ostream& operator<<( std::ostream& os, const Camera& c ) {
	return os
		<< c.latitude << ", " << c.longitude << ' ' << c.state << ' ' << c.county << ' '
		<< c.description;  // This indentation must be tolerated because it is impossible to disable
}

int main( int argc, char** argv ) {
	if ( argc == 0 ) {
		std::cerr << "Provide a path to the camera list\n";
		return 1;
	}
	auto args = std::span( argv, static_cast<uint_fast16_t>( argc ) );
	CameraVector cameras = read_cameras( args[1] );
	std::cout << cameras.size() << '\n';
	std::cout << cameras.front() << '\n';
	std::cout << cameras.back() << '\n';
	camera_kd_tree_create( cameras, 0, static_cast<int>( cameras.size() ) );
	std::cout << cameras.size() << '\n';
	std::cout << cameras.front() << '\n';
	std::cout << cameras.back() << '\n';
	return 0;
}
