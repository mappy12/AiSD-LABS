#include <iostream>
#include <stdexcept>

template <typename T>
class HalfToneImage
{
    int height, width;
    T **data;

  public:
    HalfToneImage(int h, int w, bool random_fill)
        : height(h), width(w)
    {
        if (height < 0 || width < 0)
            throw std::invalid_argument("Invalid dimensions");

        data = new T *[height];
        for (size_t i = 0; i < height; ++i)
        {
            data[i] = new T[height];
        }

        if (random_fill)
        {
            fillRandom();
        }
        else
        {
            fillZero();
        }
    }

};