#ifndef IMAGE_PROCESSING_HPP
#define IMAGE_PROCESSING_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include "pixel.hpp"

std::vector<Pixel> imageToPixels(const cv::Mat& image);
cv::Mat pixelsToImage(const std::vector<Pixel>& pixels, int rows, int cols);

#endif