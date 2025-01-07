#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // load and read the image
    std::string imagePath = "/Users/matejzecic/code/cs5330_project1/data/objects.jpg";
    cv::Mat image = cv::imread(imagePath);

    // error check, check if the image is loaded
    if (image.empty()) {
        std::cerr << "Could not read the image: " << imagePath << std::endl;
        return -1;
    }

    // display image
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", image);

    // loop that continues until a key is pressed
    char key = 0;
    while (key != 'q') {
        key = cv::waitKey(10);
        if (key == 's') {
            std::cout << "Saving image" << std::endl;
        }
    }
    return 0;
}
