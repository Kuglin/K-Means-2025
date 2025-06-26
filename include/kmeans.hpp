#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <vector>
#include "pixel.hpp"

std::vector<Pixel> kmeans(std::vector<Pixel> pixels, int k, int max_iter = 100);

#endif // KMEANS_HPP