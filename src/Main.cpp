#include <iostream> //namespace std
#include <opencv2/opencv.hpp> //namespace cv

int main(int argc, char** argv){
    if(argc != 2){
        std::cout << "ShowImage [image path]" << std::endl;
        return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], 1);

    if(!image.data){
       std::cout << "Not an image" << std::endl;
       return -1; 
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", image);

    cv::waitKey(0);
    return 0;
}