#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <string>
#include <cmath>

std::string chars = "  .,:;i1tfLCG08@";
int scale_percent = 50;

int main(int argc, char* argv[]) {
    cv::Mat image = cv::imread(argv[argc - 1], cv::IMREAD_COLOR);
    resize(image, image, cv::Size(image.cols * scale_percent / 100, image.rows * scale_percent / 100), 0, 0, cv::INTER_AREA);

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { 0, 0 };
    SetConsoleCursorPosition(hStdout, pos);

    std::string ascii_art = "";
    cv::Vec3b v;

    int rgb_ave;
    int index;
    char char_;
    int i, j;

    for (i = 0; i < image.rows; i++) {
        for (j = 0; j < image.cols; j++) {
            v = image.at<cv::Vec3b>(i, j);
            rgb_ave = (v[0] + v[1] + v[2]) / 3;
            index = floor(rgb_ave / 255.0 * (chars.length() - 1));
            char_ = chars[index];
            ascii_art += char_;
            ascii_art += " ";
        }
        ascii_art += "\n";
    }

    std::cout << ascii_art;

    system("pause");
    return 0;
}
