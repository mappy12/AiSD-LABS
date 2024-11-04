#include <iostream>
#include <stdexcept>
#include <ctime>
#include <limits>

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
            throw std::invalid_argument("Invalid dimensions");
        
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

    ~HalfToneImage() {
        for (size_t i = 0; i < height; ++i) {
                delete[] data[i];
        }

        delete[] data;
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

    T operator()(size_t h, size_t w) {
        if (h >= height || w >= width) {
            throw out_of_range("Index out of range");
        }

        return data[h][w];
    }

    HalfToneImage& operator*(T value) {
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                data[i][j] *= value;
            }
        }

        return *this;
    }

    HalfToneImage operator*(const HalfToneImage& other) {
        HalfToneImage result(this -> height, other.width, false);

        if (this -> width != other.height)
            throw invalid_argument("Multiplication is not possible: number of rows of the first matrix != number of columns of the second matrix");

        for (size_t i = 0; i < this -> height; ++i) {

            for (size_t j = 0; j < other.width; ++j) {

                T sum = 0;

                for (size_t k = 0; k < this->width; ++k) {

                    T mult = data[i][k] * other.data[k][j];

                    if (mult > numeric_limits<T>::max()) {

                        mult = numeric_limits<T>::max();

                    }
                    else if (mult < numeric_limits<T>::min()) {

                        mult = numeric_limits<T>::min();

                    }

                    if (sum > numeric_limits<T>::max() - mult) {

                        sum = numeric_limits<T>::max();

                    }
                    else if (sum < numeric_limits<T>::min() - mult) {
                       
                        sum = numeric_limits<T>::min();

                    }
                    else {
                        sum += mult;
                    }
                    
                }

                result.data[i][j] = sum;
                
            }
        }

        return result;

    }
};

int main() {

    srand(time(0));

    HalfToneImage<float> image(2, 3, true);
    HalfToneImage<float> image2(3, 2, true);

    image.print();

    cout << "\n\n\n";

    image2.print();

    cout << "\n\n\n";

    HalfToneImage<float> result = image * image2;

    result.print();

    return 0;

}