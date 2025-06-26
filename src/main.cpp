// main.cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include "kmeans.hpp"
#include "image_processing.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <caminho_para_imagem> <número_de_clusters> [número_maximo_de_iterações]" << endl;
        return -1;
    }

    string inputPath = "../" + string(argv[1]);
    int k = atoi(argv[2]);

    if (k <= 0) {
        cerr << "O número de clusters deve ser maior que zero." << endl;
        return -1;
    }

    Mat image = imread(inputPath);

    if (image.empty()) {
        cerr << "Erro ao carregar imagem!" << endl;
        return -1;
    }

    vector<Pixel> pixels = imageToPixels(image);

    vector<Pixel> clustered = (argc >= 4) ? kmeans(pixels, k, atoi(argv[3])) : kmeans(pixels, k);

    Mat segmented = pixelsToImage(clustered, image.rows, image.cols);
    imwrite("segmentada.jpg", segmented);

    cout << "Imagem segmentada salva como 'segmentada.jpg'" << endl;

    return 0;
}
