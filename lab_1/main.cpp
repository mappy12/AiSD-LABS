#include <iostream>
#include <stdexcept>
#include <ctime>

using namespace std;


template <typename T>
class HalfToneImage {
    int height, width;
    T** data;

    void fillRandom() {
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {

                if (is_same<T, bool>::value)

                    data[i][j] = rand() % 2;

                else if (is_same<T, short>::value)

                    data[i][j] = rand() % 256;

                else if (is_same<T, unsigned char>::value)

                    data[i][j] = static_cast<unsigned char> (rand() % 256);

                else if (is_same<T, float>::value) {

                    float intPart = static_cast<float> (rand() % 256);
                    float fracPart = static_cast<float> (rand()) / RAND_MAX;
                    
                    data[i][j] = intPart + fracPart;
                }
            }
        }

    }

    void fillZero() {
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                data[i][j] = 0;
            }
        }
    }

public:
    HalfToneImage(int h, int w, bool randomFill) : height(h), width(w) {
        if (height < 0 || width < 0)
            throw std::invalid_argument("Invalid dimentions");
        
        data = new T* [height];
        for (size_t i = 0; i < height; ++i) {
            data[i] = new T[width];
        }

        if (randomFill) {
            fillRandom();
        }
        else {
            fillZero();
        }
    }

    void print() {
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {

                if (is_same<T, unsigned char>::value) {
                    cout << static_cast<int> (data[i][j]);
                    cout << "  ";
                }
                else {

                    cout << data[i][j];
                    cout << "  ";
                }
            }

            cout << "\n\n";
        }
    }
};

int main() {

    srand(time(0));

    HalfToneImage<unsigned char> image(3, 4, true);
    image.print();

    return 0;

}