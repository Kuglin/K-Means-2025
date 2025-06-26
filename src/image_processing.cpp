#include "image_processing.hpp"

std::vector<Pixel> imageToPixels(const cv::Mat& image) {
    std::vector<Pixel> pixels;
    int rows = image.rows;
    int cols = image.cols;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            cv::Vec3b color = image.at<cv::Vec3b>(y, x);
            pixels.push_back({(double)color[2], (double)color[1], (double)color[0], 0});
        }
    }

    return pixels;
}

cv::Mat pixelsToImage(const std::vector<Pixel>& pixels, int rows, int cols) {
    cv::Mat image(rows, cols, CV_8UC3);
    int idx = 0;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            const Pixel& p = pixels[idx++];
            image.at<cv::Vec3b>(y, x) = cv::Vec3b((uchar)p.b, (uchar)p.g, (uchar)p.r);
        }
    }

    return image;
}