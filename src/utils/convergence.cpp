#include "convergence.hpp"

bool centroidsConverged(const std::vector<Pixel>& oldCentroids, const std::vector<Pixel>& newCentroids, double epsilon) {
    for (size_t i = 0; i < oldCentroids.size(); ++i) {
        if (distanceSquared(oldCentroids[i], newCentroids[i]) > epsilon * epsilon) {
            return false;
        }
    }
    return true;
}

bool pixelsConverged(double changeRate, double threshold) {
    return changeRate < threshold;
}