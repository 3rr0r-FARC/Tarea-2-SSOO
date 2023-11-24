#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

using namespace cv;
using namespace std;
namespace fs = filesystem; 


void convertToGrayscaleSequential(Mat& image) {
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            Point3_<uchar>* p = image.ptr<Point3_<uchar>>(r, c);
            // Luminosity Method: 0.299*R + 0.587*G + 0.114*B
            uchar gray_value = static_cast<uchar>(0.299 * p->z + 0.587 * p->y + 0.114 * p->x);
            p->x = p->y = p->z = gray_value;
        }
    }
}

int main() {
    Mat image = imread("Imagen_a_color.jpg", IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error al cargar la imagen" << endl;

        // Imprimir información adicional
        cout << "Ruta actual: " << fs::current_path() << endl;
        cout << "Ruta completa del archivo: " << fs::absolute("Imagen_a_color.jpg") << endl;

        return -1;
    }

    // Versión secuencial
    convertToGrayscaleSequential(image);

    // Guardar la imagen en escala de grises
    imwrite("Imagen_en_escala_de_grises_secuencial.jpg", image);

    return 0;
}

