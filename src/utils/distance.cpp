#include "distance.hpp"

double distanceSquared(const Pixel& a, const Pixel& b) {
    return (a.r - b.r) * (a.r - b.r) +
           (a.g - b.g) * (a.g - b.g) +
           (a.b - b.b) * (a.b - b.b);
}