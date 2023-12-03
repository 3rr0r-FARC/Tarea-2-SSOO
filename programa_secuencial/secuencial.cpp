#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <chrono>

using namespace cv;
using namespace std;
namespace fs = filesystem;
using namespace chrono;

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

int main(int argc, char** argv) {
    // Verificar si se proporcionan argumentos suficientes
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <imagen_de_entrada> <imagen_en_escala_de_grises>" << endl;
        return -1;
    }

    // Obtener nombres de archivos de los argumentos
    string inputImageName = argv[1];
    string outputImageName = argv[2];

    // Leer la imagen de entrada
    Mat image = imread(inputImageName, IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error al cargar la imagen" << endl;
        cout << "Ruta actual: " << fs::current_path() << endl;
        cout << "Ruta completa del archivo: " << fs::absolute(inputImageName) << endl;
        return -1;
    }

    // Medir el tiempo de ejecución
    auto start_time = high_resolution_clock::now();

    // Versión secuencial
    convertToGrayscaleSequential(image);

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    // Guardar la imagen en escala de grises
    imwrite(outputImageName, image);

    cout << "Imagen convertida a escala de grises exitosamente." << endl;
    cout << "Tiempo de ejecución: " << duration.count() << " ms" << endl;


    return 0;
}


