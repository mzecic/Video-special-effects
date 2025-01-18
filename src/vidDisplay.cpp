// name: Matej Zecic
// date: 01/07/2025
// description: This file reads a video and displays it

#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include "../include/filters.h"
#include "../include/faceDetect.h"

int main(int argc, char *argv[]) {
    cv::VideoCapture *capdev;

    // open the video file
    capdev = new cv::VideoCapture("../data/video.mp4");
    if (!capdev->isOpened()) {
        printf("Unable to open video device\n");
        return -1;
    }

    // get width height
    cv::Size refS((int) capdev->get(cv::CAP_PROP_FRAME_WIDTH),
                  (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1);
    cv::Mat frame;

    std::string mode = "default";

    // main loop to read frames from the video
    for (;;) {
        *capdev >> frame;
        if (frame.empty()) {
            printf("frame is empty\n");
            break;
        }

        cv::Mat changed_frame;

        // switch modes based on the user's input
        if (mode == "grayscale") {
            applyGrayscale(frame, changed_frame);
            cv::imshow("Video", changed_frame);
        } else if (mode == "custom_grayscale") {
            applyCustomGrayscale(frame, changed_frame);
            cv::imshow("Video", changed_frame);
        } else if (mode == "sepia") {
            applySepia(frame, changed_frame);
            cv::imshow("Video", changed_frame);
        } else if (mode == "blur") {
            blur5x5_2(frame, changed_frame);
            cv::imshow("Video", changed_frame);
        } else if (mode == "sobel_x") {
            cv::Mat sobel_x, absSobel_x;
            sobelX3x3(frame, sobel_x);
            cv::convertScaleAbs(sobel_x, absSobel_x);
            changed_frame = absSobel_x;
            cv::imshow("Video", changed_frame);
        } else if (mode == "sobel_y") {
            cv::Mat sobel_y, absSobel_y;
            sobelY3x3(frame, sobel_y);
            cv::convertScaleAbs(sobel_y, absSobel_y);
            changed_frame = absSobel_y;
            cv::imshow("Video", changed_frame);
        } else if (mode == "magnitude") {
            cv::Mat sobel_x, sobel_y, absSobel_x, absSobel_y;
            sobelX3x3(frame, sobel_x);
            sobelY3x3(frame, sobel_y);
            magnitude(sobel_x, sobel_y, changed_frame);
            cv::imshow("Video", changed_frame);
        } else if (mode == "blurQuantize") {
            blurQuantize(frame, changed_frame, 10);
            cv::imshow("Video", changed_frame);
        } else if (mode == "showFaces") {
            std::vector<cv::Rect> faces;
            cv::Rect last(0, 0, 0, 0);
            applyGrayscale(frame, changed_frame);
            detectFaces(changed_frame, faces);
            drawBoxes(frame, faces);
            cv::imshow("Video", frame);
        }
            else {
            cv::imshow("Video", frame);
        }

        // check for user input
        char key = cv::waitKey(10);
        if (key == 'q') {
            break;
        } else if (key == 's') {
            std::cout << "Saving image" << std::endl;
            cv::imwrite("../data/video_frame.jpg", frame);

            if (mode != "default") {
                cv::imwrite("../data/video_frame_with_filter.jpg", changed_frame);
            }
        } else if (key == 'g') {
            mode = "grayscale";
            std::cout << "Converting to grayscale" << std::endl;
        } else if (key == 'h') {
            mode = "custom_grayscale";
            std::cout << "Converting to custom grayscale" << std::endl;
        } else if (key == 'j') {
            mode = "sepia";
            std::cout << "Converting to sepia" << std::endl;
        } else if (key == 'b') {
            mode = "blur";
            std::cout << "Applying blur filter" << std::endl;
        } else if (key == 'x') {
            mode = "sobel_x";
            std::cout << "Applying sobel x filter" << std::endl;
        } else if (key == 'y') {
            mode = "sobel_y";
            std::cout << "Applying sobel y filter" << std::endl;
        } else if (key == 'm') {
            mode = "magnitude";
            std::cout << "Applying magnitude filter" << std::endl;
        } else if (key == 'l') {
            mode = "blurQuantize";
            std::cout << "Applying blurQuantize filter" << std::endl;
        } else if (key == 'f') {
            mode = "showFaces";
            std::cout << "Showing faces" << std::endl;
        }
    }

    delete capdev; // close the video file
    return 0;
}
