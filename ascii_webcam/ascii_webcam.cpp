#include <iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>

using namespace cv;

const std::string CHARS = "  .,:;i1tfLCG08@";
int scale_percent = 10;
std::string ascii_art;
VideoCapture vid(0);
Mat frame;
COORD coord;

void changeCursorPosition(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setCursorVisible(bool visible) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
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
            resize(frame, frame, Size(frame.cols * scale_percent / 100, frame.rows * scale_percent / 100), 0, 0, INTER_AREA);

            changeCursorPosition(0, 0);
            ascii_art = "";

            for (int i = 0; i < frame.rows; i++) {
                for (int j = 0; j < frame.cols; j++) {
                    int rgb_ave = (frame.at<Vec3b>(i, j)[0] + frame.at<Vec3b>(i, j)[1] + frame.at<Vec3b>(i, j)[2]) / 3;
                    int index = int(rgb_ave / 255.0 * CHARS.length()) - 1;
                    char char_ = CHARS[index];
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
