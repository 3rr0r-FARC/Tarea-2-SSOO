#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <thread>
#include <chrono>

using namespace cv;
using namespace std;
namespace fs = filesystem;
using namespace chrono;

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
    auto start_time = chrono::high_resolution_clock::now();

    // Dividir la imagen en cuatro secciones
    int rows = image.rows;
    int sectionSize = rows / numThreads;
    vector<thread> threads;

    // Crear y ejecutar cuatro hilos
    for (int i = 0; i < numThreads; ++i) {
        int start = i * sectionSize;
        int end = (i == numThreads) ? rows : (i + 1) * sectionSize;
        threads.emplace_back(convertToGrayscaleThreaded, ref(image), start, end);
    }

    // Esperar a que todos los hilos terminen su trabajo
    for (auto& thread : threads) {
        thread.join();
    }

    // Medir el tiempo de ejecución
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    

    // Guardar la imagen en escala de grises
    imwrite(outputImageName, image);
    
    cout << "Imagen convertida a escala de grises exitosamente." << endl;
    cout << "Tiempo de ejecución: " << duration.count() << " ms" << endl;

    return 0;
}
