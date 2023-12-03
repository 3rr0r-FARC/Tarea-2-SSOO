#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h>
#include <filesystem>


using namespace cv;
using namespace std;
namespace fs = filesystem;

void convertToGrayscaleThreaded(Mat& image, int startRow, int endRow) {
    for (int r = startRow; r < endRow; ++r) {
        for (int c = 0; c < image.cols; ++c) {
            Point3_<uchar>* p = image.ptr<Point3_<uchar>>(r, c);
            uchar gray_value = static_cast<uchar>(0.299 * p->z + 0.587 * p->y + 0.114 * p->x);
            p->x = p->y = p->z = gray_value;
        }
    }
}

int main(int argc, char** argv) {
    // Verificar si se proporcionan argumentos suficientes
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <imagen_de_entrada> <imagen_en_escala_de_grises> <N° hilos>" << endl;
        return -1;
    }

    // Obtener nombres de archivos de los argumentos
    string inputImageName = argv[1];
    string outputImageName = argv[2];
    int numThreads = stoi(argv[3]);

    Mat image = imread("Imagen_a_color.jpg", IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error al cargar la imagen" << endl;
        cout << "Ruta actual: " << fs::current_path() << endl;
        cout << "Ruta completa del archivo: " << fs::absolute(inputImageName) << endl;
        return -1;
    }

    // Medir el tiempo de ejecución
    double start_time = omp_get_wtime();

    // Dividir la imagen en secciones según el número de hilos
    int rows = image.rows;
    int sectionSize = rows / numThreads;

    // Utilizar OpenMP para paralelizar el bucle
    #pragma omp parallel num_threads(numThreads)
    {
        int threadID = omp_get_thread_num();
        int start = threadID * sectionSize;
        int end = (threadID == numThreads - 1) ? rows : (threadID + 1) * sectionSize;

        convertToGrayscaleThreaded(image, start, end);
    }

    // Medir el tiempo de ejecución
    double end_time = omp_get_wtime();
    double duration = (end_time - start_time) * 1000.0; // Convertir a milisegundos

    // Guardar la imagen en escala de grises
    imwrite(outputImageName, image);

    cout << "Imagen convertida a escala de grises exitosamente." << endl;
    cout << "Tiempo de ejecución: " << duration << " ms" << endl;

    return 0;
}
