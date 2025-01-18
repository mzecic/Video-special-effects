#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/opencv.hpp>

// Function that applies a grayscale filter to an image
int applyGrayscale(cv::Mat& src, cv::Mat& dst);


// Function that applies a custom grayscale filter to an image
int applyCustomGrayscale(cv::Mat& src, cv::Mat& dst);

// Function that applies a sepia filter to an image
int applySepia(cv::Mat& src, cv::Mat& dst);

// Function that applies blur filter
int blur5x5_1(cv::Mat& src, cv::Mat& dst);

// Function that applies blur filter
int blur5x5_2(cv::Mat& src, cv::Mat& dst);

// Function that applies a 3x3 sobel x filter to an image
int sobelX3x3(cv::Mat& src, cv::Mat& dst);

// Function that applies a 3x3 sobel y filter to an image
int sobelY3x3(cv::Mat& src, cv::Mat& dst);

// Function that applies magnitude filter to an image (sobel x and sobel y)
int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst);

// Function that blurs and quantizes the image
int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels);

#endif // FILTERS_H
