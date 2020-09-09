#include <iostream> //namespace std
#include <opencv2/opencv.hpp> //namespace cv
#include "utils/CameraListParser.h"

int main(int argc, char** argv){
    cv::Mat image(1080,1920, CV_8UC3, cv::Scalar(255,255,0));


    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", image);

    cv::waitKey(0);
    CameraParse(argv[1]);
    return 0;
}