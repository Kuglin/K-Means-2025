#include "kmeans.hpp"
#include "utils/distance.hpp"
#include "utils/convergence.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

std::vector<Pixel> kmeans(std::vector<Pixel> pixels, int k, int max_iter) {
    std::vector<Pixel> centroids;
    srand(time(0));

    centroids.push_back(pixels[rand() % pixels.size()]);

    for (int c = 1; c < k; ++c) {
        vector<double> distances(pixels.size());
        double total = 0.0;

        for (size_t i = 0; i < pixels.size(); ++i) {
            double minDist = distanceSquared(pixels[i], centroids[0]);
            for (size_t j = 1; j < centroids.size(); ++j) {
                double d = distanceSquared(pixels[i], centroids[j]);
                if (d < minDist) {
                    minDist = d;
                }
            }
            distances[i] = minDist * minDist;
            total += distances[i];
        }

        double r = ((double)rand() / RAND_MAX) * total;
        double cumulative = 0.0;
        for (size_t i = 0; i < pixels.size(); ++i) {
            cumulative += distances[i];
            if (cumulative >= r) {
                centroids.push_back(pixels[i]);
                break;
            }
        }
    }

    const double EPSILON_CENTROID = 1e-2;
    const double EPSILON_PIXELS = 0.01;

    for (int iter = 0; iter < max_iter; ++iter) {
        int changed = 0;

        for (size_t i = 0; i < pixels.size(); ++i) {
            double minDist = distanceSquared(pixels[i], centroids[0]);
            int bestCluster = 0;
            for (int j = 1; j < k; ++j) {
                double d = distanceSquared(pixels[i], centroids[j]);
                if (d < minDist) {
                    minDist = d;
                    bestCluster = j;
                }
            }
            if (pixels[i].cluster != bestCluster) {
                changed++;
            }
            pixels[i].cluster = bestCluster;
        }

        double changeRate = (double)changed / pixels.size();

        std::vector<int> count(k, 0);
        std::vector<Pixel> newCentroids(k, {0, 0, 0, 0});

        for (const Pixel& p : pixels) {
            newCentroids[p.cluster].r += p.r;
            newCentroids[p.cluster].g += p.g;
            newCentroids[p.cluster].b += p.b;
            count[p.cluster]++;
        }

        for (int i = 0; i < k; ++i) {
            if (count[i] > 0) {
                newCentroids[i].r /= count[i];
                newCentroids[i].g /= count[i];
                newCentroids[i].b /= count[i];
            }
        }

        bool centroidsOk = centroidsConverged(centroids, newCentroids, EPSILON_CENTROID);
        bool pixelsOk = pixelsConverged(changeRate, EPSILON_PIXELS);

        centroids = newCentroids;

        if (centroidsOk && pixelsOk) {
            cout << "Convergência alcançada em " << iter << " iterações." << endl;
            break;
        }
    }

    for (Pixel& p : pixels) {
        Pixel c = centroids[p.cluster];
        p.r = c.r;
        p.g = c.g;
        p.b = c.b;
    }

    return pixels;
}
