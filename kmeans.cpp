#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point {
    double x, y;
    int cluster;
};

double distance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<Point> kmeans(vector<Point> points, int k, int iterations) {
    vector<Point> centroids;

    srand(time(0));
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points[rand() % points.size()]);
    }
    
     // Atribui cada ponto ao centróide mais próximo
    for (int iter = 0; iter < iterations; ++iter) {
        for (Point& point : points) {  
            double minDist = distance(point, centroids[0]);
            int bestCluster = 0;

            for (int i = 1; i < k; ++i) {
                double dist = distance(point, centroids[i]);
                if (dist < minDist) {
                    minDist = dist;
                    bestCluster = i;
                }
            }

            point.cluster = bestCluster;
        }

        // Recalcula os centróides
        vector<int> count(k, 0);
        vector<Point> newCentroids(k, {0, 0, 0});

        for (const Point& point : points) {
            newCentroids[point.cluster].x += point.x;
            newCentroids[point.cluster].y += point.y;
            count[point.cluster]++;
        }

        for (int i = 0; i < k; ++i) {
            if (count[i] > 0) {
                newCentroids[i].x /= count[i];
                newCentroids[i].y /= count[i];
            }
        }

        centroids = newCentroids;
    }

    return points; 
}

int main() {
    vector<Point> points = {
        {1.0, 2.0}, {1.5, 1.8}, {5.0, 8.0},
        {8.0, 8.0}, {1.0, 0.6}, {9.0, 11.0}
    };

    int k = 2;
    int iterations = 10;

    vector<Point> clusteredPoints = kmeans(points, k, iterations);

    for (const Point& point : clusteredPoints) {
        cout << "Point (" << point.x << ", " << point.y << ") - Cluster " << point.cluster << endl;
    }

    return 0;
}
