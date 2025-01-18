// name: Matej Zecic
// date: 01/07/2025
// description: This file contains the implementation filters that can be applied to images

#include <opencv2/opencv.hpp>
#include <iostream>
#include "../include/filters.h"
#include <cmath>

// Function that applies a grayscale filter to an image
// Parameters:
//      src: input image
//      dst: destination image
// Returns:
//      int
int applyGrayscale(cv::Mat& src, cv::Mat& dst) {
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    return 0;
}

// Function that applies a custom grayscale filter to an image
// Parameters:
//      src: input image
//      dst: destination image
// Returns:
//      int
int applyCustomGrayscale(cv::Mat& src, cv::Mat& dst) {
    // initialize gray_image to have the same size and type as the input src
    cv::Mat gray_image = cv::Mat(src.rows, src.cols, src.type());

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            cv::Vec3b intensity = src.at<cv::Vec3b>(i, j);

            // extract the blue, green, and red channel values
            int blue = intensity.val[0];
            int green = intensity.val[1];
            int red = intensity.val[2];
            // custom grayscale filter
            int gray = (green * 1/2 + blue * 1/3 + red * 1/8 / 3);

            gray_image.at<cv::Vec3b>(i, j) = cv::Vec3b(gray, gray, gray);
        }
    }

    dst = gray_image;

    return 0;
}

// Function that applies a sepia filter to an image
// Parameters:
//      src: input image
//      dst: destination image
// Returns:
//      int
int applySepia(cv::Mat& src, cv::Mat& dst) {
    // initialize sepia_image to have the same size and type as the input src
    cv::Mat sepia_image = cv::Mat(src.rows, src.cols, src.type());

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            cv::Vec3b intensity = src.at<cv::Vec3b>(i, j);

            // extract the blue, green, and red channel values
            int blue = intensity.val[0];
            int green = intensity.val[1];
            int red = intensity.val[2];

            // apply sepia filter
            int sepia_blue = (int)(0.272 * red + 0.534 * green + 0.131 * blue);
            int sepia_green = (int)(0.349 * red + 0.686 * green + 0.168 * blue);
            int sepia_red = (int)(0.393 * red + 0.769 * green + 0.189 * blue);

            // add vignetting effect (optional, extra credit?)



            // make sure the values are within the range [0, 255]
            sepia_blue = std::min(sepia_blue, 255);
            sepia_green = std::min(sepia_green, 255);
            sepia_red = std::min(sepia_red, 255);

            sepia_image.at<cv::Vec3b>(i, j) = cv::Vec3b(sepia_blue, sepia_green, sepia_red);
        }
    }

    dst = sepia_image;

    return 0;
}


// Function that applies a blur filter to an image
// Parameters:
//      src: input image
//      dst: destination image
// Returns:
//      int
int blur5x5_1(cv::Mat& src, cv::Mat& dst) {
    // clone the source image to the destination image
    dst.create(src.size(), src.type());

    // define the 5x5 Gaussian kernel for blurring
    int kernel[5][5] = {
        {1, 2, 4, 2, 1},
        {2, 4, 8, 4, 2},
        {4, 8, 16, 8, 4},
        {2, 4, 8, 4, 2},
        {1, 2, 4, 2, 1}
    };

    // iterate over each pixel, excluding the first and last two rows/columns
    for (int i = 2; i < src.rows - 2; i++) {
        for (int j = 2; j < src.cols - 2; j++) {

            int sumBlue = 0, sumGreen = 0, sumRed = 0;

            for (int ki = -2; ki <= 2; ki++) {
                for (int kj = -2; kj <= 2; kj++) {
                    cv::Vec3b intensity = src.at<cv::Vec3b>(i + ki, j + kj);

                    // multiply by the corresponding kernel value
                    int weight = kernel[ki + 2][kj + 2];
                    sumBlue += intensity[0] * weight;
                    sumGreen += intensity[1] * weight;
                    sumRed += intensity[2] * weight;
                }
            }

            // Normalize the accumulated values by dividing by 256
            sumBlue /= 256;
            sumGreen /= 256;
            sumRed /= 256;

            // Set the result in the destination image
            dst.at<cv::Vec3b>(i, j) = cv::Vec3b(sumBlue, sumGreen, sumRed);
        }
    }

    return 0;
}

// Function that applies a blur filter to an image
// Parameters:
//      src: input image
//      dst: destination image
// Returns:
//      int
int blur5x5_2(cv::Mat &src, cv::Mat &dst) {
    dst.create(src.size(), src.type());

    // Define the 1x5 kernel
    int kernel[5] = {1, 2, 4, 2, 1};
    const int kernelSum = 10;

    // create an intermediate image to store the horizontal pass results
    cv::Mat temp = cv::Mat::zeros(src.size(), src.type());

    // horizontal pass
    for (int i = 0; i < src.rows; i++) {
        cv::Vec3b *srcRow = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *tempRow = temp.ptr<cv::Vec3b>(i);

        for (int j = 2; j < src.cols - 2; j++) {
            int sumBlue = 0, sumGreen = 0, sumRed = 0;

            // applying the filter
            for (int k = -2; k <= 2; k++) {
                sumBlue += srcRow[j + k][0] * kernel[k + 2];
                sumGreen += srcRow[j + k][1] * kernel[k + 2];
                sumRed += srcRow[j + k][2] * kernel[k + 2];
            }

            // normalization
            tempRow[j][0] = sumBlue / kernelSum;
            tempRow[j][1] = sumGreen / kernelSum;
            tempRow[j][2] = sumRed / kernelSum;
        }
    }

    // vertical pass
    for (int i = 2; i < src.rows - 2; i++) {
        cv::Vec3b *dstRow = dst.ptr<cv::Vec3b>(i);

        for (int j = 0; j < src.cols; j++) {
            int sumBlue = 0, sumGreen = 0, sumRed = 0;

            // applying the filter
            for (int k = -2; k <= 2; k++) {
                cv::Vec3b *tempRow = temp.ptr<cv::Vec3b>(i + k);

                sumBlue += tempRow[j][0] * kernel[k + 2];
                sumGreen += tempRow[j][1] * kernel[k + 2];
                sumRed += tempRow[j][2] * kernel[k + 2];
            }

            // normalization
            dstRow[j][0] = sumBlue / kernelSum;
            dstRow[j][1] = sumGreen / kernelSum;
            dstRow[j][2] = sumRed / kernelSum;
        }
    }

    return 0; // Indicate success
}

// Function that applies sobel x filter to an image
// Parameters:
//      src: input image
//      dst: destination image
// Returns:
//      int
int sobelX3x3(cv::Mat& src, cv::Mat& dst) {
    // creating an image of the same size as the source image, but with 16-bit signed channels
    dst.create(src.size(), CV_16SC3);
    cv::Mat paddedSrc;
    cv::copyMakeBorder(src, paddedSrc, 1, 1, 1, 1, cv::BORDER_REPLICATE);

    cv::Mat temp;
    temp.create(src.size(), CV_16SC3);

    int horizontalKernel[3] = {-1, 0, +1};

    // horizontal pass
    for (int i = 0; i < paddedSrc.rows - 1; i++) {
        for (int j = 1; j < paddedSrc.cols - 1; j++) {
            short sumBlue = 0, sumGreen = 0, sumRed = 0;

            for (int k = -1; k <= 1; k++) {
                cv::Vec3b intensity = src.at<cv::Vec3b>(i, j + k);
                sumBlue += intensity[0] * horizontalKernel[k + 1];
                sumGreen += intensity[1] * horizontalKernel[k + 1];
                sumRed += intensity[2] * horizontalKernel[k + 1];
            }

            temp.at<cv::Vec3s>(i, j) = cv::Vec3s(sumBlue, sumGreen, sumRed);
        }
    }

    int verticalKernel[3] = {1, 2, 1};

    // vertical pass
    for (int i = 1; i < paddedSrc.rows; i++) {
        for (int j = 0; j < paddedSrc.cols; j++) {
            short sumBlue = 0, sumGreen = 0, sumRed = 0;

            for (int k = -1; k <= 1; k++) {
                cv::Vec3s intensity = temp.at<cv::Vec3s>(i + k, j);
                sumBlue += intensity[0] * verticalKernel[k + 1];
                sumGreen += intensity[1] * verticalKernel[k + 1];
                sumRed += intensity[2] * verticalKernel[k + 1];
            }

            dst.at<cv::Vec3s>(i, j) = cv::Vec3s(sumBlue, sumGreen, sumRed);
        }
    }

    return 0;
}


// Function that applies sobel y filter to an image
// Parameters:
//      src: input image
//      dst: destination image
// Returns:
//      int
int sobelY3x3(cv::Mat& src, cv::Mat& dst) {
    // creating an image of the same size as the source image, but with 16-bit signed channels
    dst.create(src.size(), CV_16SC3);
    cv::Mat paddedSrc;
    cv::copyMakeBorder(src, paddedSrc, 1, 1, 1, 1, cv::BORDER_REPLICATE);

    cv::Mat temp;
    temp.create(src.size(), CV_16SC3);

    int horizontalKernel[3] = {1, 2, 1};

    // horizontal
    for (int i = 0; i < src.rows; i++) {
        for (int j = 1; j < src.cols - 1; j++) {
            short sumBlue = 0, sumGreen = 0, sumRed = 0;

            for (int k = -1; k <= 1; k++) {
                cv::Vec3b intensity = src.at<cv::Vec3b>(i, j + k);
                sumBlue += intensity[0] * horizontalKernel[k + 1];
                sumGreen += intensity[1] * horizontalKernel[k + 1];
                sumRed += intensity[2] * horizontalKernel[k + 1];
            }

            temp.at<cv::Vec3s>(i, j) = cv::Vec3s(sumBlue, sumGreen, sumRed);
        }
    }

    int verticalKernel[3] = {-1, 0, +1};

    // vertical pass
    for (int i = 1; i < src.rows - 1; i++) {
        for (int j = 0; j < src.cols; j++) {
            short sumBlue = 0, sumGreen = 0, sumRed = 0;

            for (int k = -1; k <= 1; k++) {
                cv::Vec3s intensity = temp.at<cv::Vec3s>(i + k, j);
                sumBlue += intensity[0] * verticalKernel[k + 1];
                sumGreen += intensity[1] * verticalKernel[k + 1];
                sumRed += intensity[2] * verticalKernel[k + 1];
            }

            dst.at<cv::Vec3s>(i, j) = cv::Vec3s(sumBlue, sumGreen, sumRed);
        }
    }

    return 0;
}

// Function that applies magnitude filter to an image
// Parameters:
//      sx: unsigned short 3 channel input image
//      sy: unsigned short 3 channel input image
//      dst: destination image
// Returns:
//      int
int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst) {
    // check if input is valid
    if (sx.empty() || sy.empty() || sx.size() != sy.size() || sx.type() != sy.type()) {
        return -1;
    }

    dst = cv::Mat::zeros(sx.size(), CV_8UC3); // Unsigned char 3-channel image

    // main loop, iterate through rows, cols, and channels
    for (int row = 0; row < sx.rows; ++row) {
        for (int col = 0; col < sx.cols; ++col) {
            for (int ch = 0; ch < 3; ++ch) {
                short val_sx = sx.at<cv::Vec3s>(row, col)[ch];
                short val_sy = sy.at<cv::Vec3s>(row, col)[ch];

                // compute gradient magnitude
                float magnitude = std::sqrt(val_sx * val_sx + val_sy * val_sy);

                // cormalize and convert to uchar
                dst.at<cv::Vec3b>(row, col)[ch] = static_cast<uchar>(
                    std::min(255.0f, magnitude));
            }
        }
    }
    return 0;
}

// Function that blurs and quantizes the image
// Parameters:
//      src: input image
//      dst: result image
//      levels: number of levels to apply
// Returns:
//      int
int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels = 10) {
    // check if input is valid
    if (src.empty() || levels < 1) {
        return -1;
    }

    // apply blur filter
    cv::Mat blurred;
    blur5x5_2(src, blurred);

    // apply quantization
    float b = 255.0f / levels;
    dst = cv::Mat::zeros(src.size(), src.type());
    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            for (int ch = 0; ch < 3; ch++) {
                uchar x = blurred.at<cv::Vec3b>(i, j)[ch];

                // apply forumla, quantize the value
                int xt = static_cast<int>(x / b); // Bucket index
                uchar xf = static_cast<uchar>(xt * b); // Quantized value

                dst.at<cv::Vec3b>(i, j)[ch] = xf;
            }
        }
    }

    return 0;
}
