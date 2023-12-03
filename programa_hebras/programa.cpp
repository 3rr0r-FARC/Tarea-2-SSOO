#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>

using namespace cv;
using namespace std;

void convertToGrayscaleThreaded(Mat& image, int startRow, int endRow) {
    for (int r = startRow; r < endRow; ++r) {
        for (int c = 0; c < image.cols; ++c) {
            Point3_<uchar>* p = image.ptr<Point3_<uchar>>(r, c);
            uchar gray_value = static_cast<uchar>(0.299 * p->z + 0.587 * p->y + 0.114 * p->x);
            p->x = p->y = p->z = gray_value;
        }
    }
}

int main() {
    Mat image = imread("Imagen_a_color.jpg", IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error al cargar la imagen" << endl;
        return -1;
    }

    // Dividir la imagen en cuatro secciones
    int rows = image.rows;
    int sectionSize = rows / 4;
    vector<thread> threads;

    // Crear y ejecutar cuatro hilos
    for (int i = 0; i < 4; ++i) {
        int start = i * sectionSize;
        int end = (i == 3) ? rows : (i + 1) * sectionSize;
        threads.emplace_back(convertToGrayscaleThreaded, ref(image), start, end);
    }

    // Esperar a que todos los hilos terminen su trabajo
    for (auto& thread : threads) {
        thread.join();
    }

    // Guardar la imagen en escala de grises
    imwrite("Imagen_en_escala_de_grises_threaded.jpg", image);

    return 0;
}
