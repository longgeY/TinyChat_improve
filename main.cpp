#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat visibleImage = cv::imread("C:\\Users\\40927\\Desktop\\material\\material\\Visable.jpg");
    cv::Mat infraredImage = cv::imread("C:\\Users\\40927\\Desktop\\material\\material\\Infrared.jpg");

    if (visibleImage.empty() || infraredImage.empty()) {
        std::cerr << "Could not open or find the images!" << std::endl;
        return -1;
    }

    cv::resize(visibleImage, visibleImage, infraredImage.size());

    cv::Mat infraredImageGray;
    cv::cvtColor(infraredImage, infraredImageGray, cv::COLOR_BGR2GRAY);

    cv::Mat infraredImageColor;
    cv::cvtColor(infraredImageGray, infraredImageColor, cv::COLOR_GRAY2BGR);

    double alpha = 0.5; 
    double beta = 1.0 - alpha; 
    cv::Mat fusedImage;
    cv::addWeighted(visibleImage, alpha, infraredImageColor, beta, 0.0, fusedImage);

    cv::imshow("Fused Image", fusedImage);
    cv::waitKey(0);

    cv::imwrite("path_to_output_image.jpg", fusedImage);

    return 0;
}


