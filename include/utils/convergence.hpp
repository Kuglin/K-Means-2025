#ifndef CONVERGENCE_HPP
#define CONVERGENCE_HPP

#include <vector>
#include "pixel.hpp"
#include "distance.hpp"

bool centroidsConverged(const std::vector<Pixel>& oldCentroids, const std::vector<Pixel>& newCentroids, double epsilon);
bool pixelsConverged(double changeRate, double threshold);

#endif // CONVERGENCE_HPP