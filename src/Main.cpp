#include <iostream> //namespace std
// #include <opencv2/opencv.hpp> //namespace cv
#include "utils/camera_list_parser.h"

int main(int argc, char** argv){
	CameraList cameras = CameraParse(argv[1]);
	std::cout << "cams" << std::endl;
	State ky = cameras["Kentucky"];
	std::cout << "ky" << std::endl;
	County jefferson = ky["Jefferson"];
	std::cout << "jeff" << std::endl;
	Camera cam = jefferson.front();
	std::cout << cam.description << std::endl;
	return 0;
}