#ifndef __NUMCPP_H__
#define __NUMCPP_H__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <climits>

using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

namespace numcpp
{

template<typename T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
    return v < lo ? lo : v > hi ? hi : v;
}

class Shape2D
{
  public:
    long d0;
    long d1;
    Shape2D(long d0, long d1) : d0(d0), d1(d1){};
};

class Shape3D
{
  public:
    long d0;
    long d1;
    long d2;
    Shape3D(long d0, long d1, long d2) : d0(d0), d1(d1), d2(d2){};
};

class Range
{
  public:
    long start;
    long end;
    long step;

    // TODO: step cannot be 0
    Range(long start = 0, long end = LONG_MAX, long step = 1) : start(start), end(end), step(step){};

    vector<long> seq(long size)
    {
        long start = this->start;
        long end = this->end;
        long step = this->step;

        // Handle negative index
        if (start < 0L)
            start += size;
        if (end < 0L)
            end += size;

        // Handle out of range
        start = clamp(start, 0L, size);
        end = clamp(end, 0L, size);

        long count = (end - start) / step;
        vector<long> r(count, 0);

        r[0] = start;
        for (long i = 1; i < count; i++)
        {
            r[i] = r[i - 1] + step;
        }

        return r;
    }
};

template <typename T>
class Vec
{
  private:
    long shape;
    long size;
    shared_ptr<vector<T>> pData;
    unique_ptr<vector<T>> pIndex;

  public:
    /**
     * Init a Vec with shape
     */
    Vec(int shape) : shape(shape)
    {
        pData = shared_ptr<vector<T>>(new vector<T>(shape));
        size = shape;
    }

    /**
     * Init a Vec with data (std::vector<T>)
     */
    Vec(vector<T> data)
    {
        pData = shared_ptr<vector<T>>(new vector<T>(data));
        shape = data.size();
        size = shape;
    }

    /**
     * Copy constructor.
     */
    Vec(const Vec<T> &v)
    {
        pData = v.pData;
        shape = v.shape;
        size = v.size;
    }

    long getSize()
    {
        return size;
    }

    long getShape()
    {
        return shape;
    }

    T &operator[](long n)
    {
        return (*pData)[n];
    }

    /**
     * Slice.
     */
    Vec<T> operator()(Range range)
    {
        Vec<T> r(*this);
        // TODO
        return r;
    }

    string as_string()
    {
        std::stringstream s;
        s << "Vec(" << size << ")[";
        for (long i = 0; i < pData->size(); i++)
        {
            if (i != 0)
            {
                s << ", ";
            }
            s << (*pData)[i];
        }

        s << "]";

        return s.str();
    }
};

template <typename T>
class Mat2D
{
  private:
    Shape2D shape;
    shared_ptr<vector<T>> pData;
};

// template <class T>
// class mat2d
// {
//   private:
//     shape2d shape;
//     std::vector<T> *data;

//   public:
//     int size;
//     array(shape2d shape) : shape(shape)
//     {
//         // Compute data size
//         size = 1;
//         for (auto i = shape.cbegin(); i != shape.cend(); i++)
//         {
//             size *= *i;
//         }

//         // Allocate memory for data
//         this->data = new std::vector<T>(size);
//     }

//     ~array()
//     {
//         delete this->data;
//     }

//     void fill(T value)
//     {
//         for (auto i = data->begin(); i != data->end(); i++)
//         {
//             *i = value;
//         }
//     }

//     /**
//      * Return sub array at index n.
//      */
//     array<T> operator()(range r)
//     {
//     }

//     /**
//      * Output the array as a string.
//      */
//     std::string as_string()
//     {
//         std::stringstream s;
//         s << "array(";

//         for (auto i = shape.cbegin(); i != shape.cend(); i++)
//         {
//             if (i != shape.cbegin())
//             {
//                 s << ", ";
//             }
//             s << *i;
//         }
//         s << ")";
//         s << dimen_as_string();
//         return s.str();
//     }
// };

} // namespace numcpp

#endif