#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>

const std::string CHARS = "   .,:;i1tfLCG08@";
int scale_percent = 20;
std::string ascii_art;
cv::VideoCapture vid(0);
cv::Mat frame;

COORD coord;
HANDLE out;
CONSOLE_CURSOR_INFO cursorInfo;

int rgb_ave;
int index;
char char_;
int i, j;
cv::Vec3b v;

void changeCursorPosition(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setCursorVisible(bool visible) {
    out = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
    setCursorVisible(false);
    while (true) {
        try {
            vid >> frame;

            if (frame.empty()) break;
            resize(frame, frame, cv::Size(frame.cols * scale_percent / 100, frame.rows * scale_percent / 100), 0, 0, cv::INTER_AREA);

            changeCursorPosition(0, 0);
            ascii_art = "";

            for (i = 0; i < frame.rows; i++) {
                for (j = 0; j < frame.cols; j++) {
                    v = frame.at<cv::Vec3b>(i, j);
                    rgb_ave = (v[0] + v[1] + v[2]) / 3;
                    index = int(rgb_ave / 255.0 * CHARS.length());
                    char_ = CHARS[index];
                    ascii_art += char_;
                    ascii_art += " ";
                }
                ascii_art += "\n";
            }
            std::cout << ascii_art << std::endl;
        }
        catch (const std::exception& e) {
            break;
        }
    }

    vid.release();
    return 0;
}
