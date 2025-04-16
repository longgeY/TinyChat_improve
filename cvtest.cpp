#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

int main() {
    // 读取图像
    cv::Mat image1 = cv::imread("C:\\Users\\40927\\Desktop\\material\\material\\Visable.jpg");
    cv::Mat image2 = cv::imread("C:\\Users\\40927\\Desktop\\material\\material\\Infrared.jpg");

    // 检查图像是否成功加载
    if (image1.empty() || image2.empty()) {
        std::cerr << "Could not open or find the images!" << std::endl;
        return -1;
    }

    // 转换图像为灰度图像
    cv::Mat gray1, gray2;
    cv::cvtColor(image1, gray1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(image2, gray2, cv::COLOR_BGR2GRAY);

    // 检测SIFT特征点并计算描述符
    auto sift = cv::xfeatures2d::SIFT::create();
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1, descriptors2;
    sift->detectAndCompute(gray1, cv::noArray(), keypoints1, descriptors1);
    sift->detectAndCompute(gray2, cv::noArray(), keypoints2, descriptors2);

    // 使用FLANN匹配器匹配特征点
    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    // 过滤好的匹配点
    double max_dist = 0;
    double min_dist = 100;
    for (int i = 0; i < descriptors1.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }
    std::vector<cv::DMatch> good_matches;
    for (int i = 0; i < descriptors1.rows; i++) {
        if (matches[i].distance <= std::max(2 * min_dist, 0.02)) {
            good_matches.push_back(matches[i]);
        }
    }

    std::vector<cv::Point2f> points1, points2;
    for (size_t i = 0; i < good_matches.size(); i++) {
        points1.push_back(keypoints1[good_matches[i].queryIdx].pt);
        points2.push_back(keypoints2[good_matches[i].trainIdx].pt);
    }

    cv::Mat H = cv::findHomography(points2, points1, cv::RANSAC);

    cv::Mat aligned_image2;
    cv::warpPerspective(image2, aligned_image2, H, image1.size());

    // 融合两张图像
    cv::Mat fusedImage;
    double alpha = 0.5; 
    double beta = 1.0 - alpha; 
    cv::addWeighted(image1, alpha, aligned_image2, beta, 0.0, fusedImage);

    cv::imshow("Fused Image", fusedImage);
    cv::waitKey(0);

    cv::imwrite("C:\\Users\\40927\\Desktop\\material\\material\\FusedImage.jpg", fusedImage);

    return 0;
}

