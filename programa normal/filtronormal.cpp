#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv ;
using namespace std ;

//leer la imagen
Mat image = imread("Imagen_a_color.jpg", IMREAD_COLOR);

//leer cada pixel (RGB)

for(int r = 0; r<image.rows;r++){
    for(int c=0; c<image.cols; c++){
        Point3_<uchar>*p = image.ptr<Point3__<uchar>>(r, c);
        //x:B y:G z:R
        printf("(%d %d %d)", p->x, p->y, p->z);
    }
}