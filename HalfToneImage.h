#include <iostream>
#include <limits>
#include <cmath>


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

    static constexpr double eps = 1e-9;

    HalfToneImage() : height(0), width(0), data(nullptr) {}

    HalfToneImage(int h, int w, bool randomFill) : height(h), width(w) {

        if (height < 0 || width < 0)
            throw invalid_argument("Invalid dimensions");

        data = new T * [height];
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

    HalfToneImage(const HalfToneImage& other) : height(other.height), width(other.width) {

        data = new T * [height];

        for (size_t i = 0; i < height; ++i) {

            data[i] = new T[width];

            for (size_t j = 0; j < width; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    HalfToneImage& operator=(const HalfToneImage& other) {

        if (this == &other) {
            return *this;
        }

        for (size_t i = 0; i < height; ++i) {
            delete[] data[i];
        }

        delete[] data;

        height = other.height;
        width = other.width;

        data = new T * [height];
        for (size_t i = 0; i < height; ++i) {
            data[i] = new T[width];
        }

        for (size_t i = 0; i < height; ++i) {

            for (size_t j = 0; j < width; ++j) {

                data[i][j] = other.data[i][j];

            }
        }

        return *this;
    }

    ~HalfToneImage() {
        for (size_t i = 0; i < height; ++i) {
            delete[] data[i];
        }

        delete[] data;
    }

    int getHeight() const {
        return height;
    }

    int getWidth() const {
        return width;
    }

    T getData(size_t row, size_t col) const {
        return data[row][col];
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

    T& operator()(size_t h, size_t w) {
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
        HalfToneImage result(this->height, other.width, false);

        if (this->width != other.height)
            throw invalid_argument("Multiplication is not possible: number of rows of the first matrix != number of columns of the second matrix");

        for (size_t i = 0; i < this->height; ++i) {

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


    HalfToneImage operator+(const HalfToneImage& other) {
        if (height != other.height || width != other.width)
            throw invalid_argument("Addition is not possible: matrix sizes are not equal");

        HalfToneImage result(height, width, false);

        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {

                if (data[i][j] + other.data[i][j] > numeric_limits<T>::max()) {

                    result.data[i][j] = numeric_limits<T>::max();

                }
                else if (data[i][j] + other.data[i][j] < numeric_limits<T>::min()) {

                    result.data[i][j] = numeric_limits<T>::min();

                }
                else {
                    result.data[i][j] = data[i][j] + other.data[i][j];
                }
            }
        }

        return result;

    }

    HalfToneImage operator-(const HalfToneImage& other) {
        if (height != other.height || width != other.width) {
            throw invalid_argument("Subtraction is not possible: matrix sizes are not equal");
        }

        HalfToneImage result(height, width, false);

        for (size_t i = 0; i < height; ++i) {

            for (size_t j = 0; j < width; ++j) {

                if (data[i][j] - other.data[i][j] < numeric_limits<T>::min()) {
                    result.data[i][j] = numeric_limits<T>::min();
                }

                else if (data[i][j] - other.data[i][j] > numeric_limits<T>::max()) {
                    result.data[i][j] = numeric_limits<T>::max();
                }

                else {
                    result.data[i][j] = data[i][j] - other.data[i][j];
                }


            }
        }

        return result;
    }

    bool operator==(const HalfToneImage& other) const {

        if (height != other.height || width != other.width) {
            return false;
        }

        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {

                if (fabs(data[i][j] - other.data[i][j]) > eps) {
                    return false;
                }

            }
        }

        return true;
    }

    bool operator!=(const HalfToneImage& other) const {
        return !(*this == other);
    }

    HalfToneImage& operator!() {
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                data[i][j] *= -1;
            }
        }

        return *this;
    }

};

template<typename T>
ostream& operator<<(ostream& os, const HalfToneImage<T>& image) {

    for (size_t i = 0; i < image.getHeight(); ++i) {

        for (size_t j = 0; j < image.getWidth(); ++j) {

            if (is_same<T, unsigned char>::value) {

                os << static_cast<int>(image.getData(i, j));
                os << " ";

            }

            else {

                os << image.getData(i, j);
                os << " ";

            }
        }

        os << "\n\n";

    }

    return os;
}