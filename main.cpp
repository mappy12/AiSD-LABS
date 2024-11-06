#include "HalfToneImage.h"
#include <ctime>

using namespace std;


template<typename T>
void drawRectangle(HalfToneImage<T>& hfImage, size_t x1, size_t y1, size_t x2, size_t y2, T fillValue) {

    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);

    for (size_t i = x1; i <= x2; ++i) {
        for (size_t j = y1; j <= y2; ++j) {
            hfImage(i, j) = fillValue;
        }
    }

    cout << hfImage;

}


int main() {

    srand(time(0));

    cout << "Multiplication: " << "\n\n\n";

    HalfToneImage<float> image(2, 3, true);
    HalfToneImage<float> image2(3, 2, true);

    image.print();
    cout << "\n\n\n";
    image2.print();
    cout << "\n\n\n";
    HalfToneImage<float> result = image * image2;
    result.print();
    cout << "\n\n\n";

    cout << "Addition:" << "\n\n\n";

    HalfToneImage<unsigned char> image3(2, 3, true);
    image3.print();
    cout << "\n\n\n";

    HalfToneImage<unsigned char> image4(2, 3, true);
    image4.print();
    cout << "\n\n\n";

    HalfToneImage<unsigned char> result2 = image3 + image4;
    result2.print();

    cout << "\n\nCout overloading\n\n\n";
    cout << result2;

    cout << "\n\n\nCopy constructor check\n\n\n";

    HalfToneImage<unsigned char> image5(image4);
    cout << image5;

    cout << "\n\n\nChecking comparison overload for equalit\n\n\n";

    cout << (image5 == image4);

    cout << (image5 != image4);

    cout << "\n\n\nOperator '!' check\n\n\n";
    cout << image << "\n\n\n" << !image;

    cout << "\n\nOperator '-' checking\n\n\n";

    cout << image5 << "\n\n\n";
    cout << image3 << "\n\n\n";

    cout << (image5 - image3);

    cout << "\n\n\n";

    HalfToneImage<unsigned char> htImage(10, 5, true);

    drawRectangle<unsigned char>(htImage, 0, 0, 7, 4, 200);
    

    return 0;

}