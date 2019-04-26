#ifndef __NUMCPP_H__
#define __NUMCPP_H__

#include <vector>
#include <string>
#include <sstream>
#include <memory>

using std::shared_ptr;
using std::size_t;
using std::string;
using std::unique_ptr;
using std::vector;

namespace numcpp
{

class Shape2D
{
  public:
    size_t d0;
    size_t d1;
    Shape2D(size_t d0, size_t d1) : d0(d0), d1(d1){};
};

class Shape3D
{
  public:
    size_t d0;
    size_t d1;
    size_t d2;
    Shape3D(size_t d0, size_t d1, size_t d2) : d0(d0), d1(d1), d2(d2){};
};

class Range
{
  public:
    size_t start;
    size_t end;
    size_t step;

    // TODO: step cannot be 0
    Range(size_t start = 0, size_t end = -1, size_t step = 1) : start(start), end(end), step(step){};

    vector<size_t> series(size_t size)
    {
        size_t start = this->start;
        size_t end = this->end;

        if (start < 0) start += size;
        if (end < 0) end += size;

        size_t count = (end - start + 1) / step;

        if (step > 0)
        {
        }
    }
};

template <typename T>
class Vec
{
  private:
    size_t shape;
    size_t size;
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

    size_t getSize()
    {
        return size;
    }

    size_t getShape()
    {
        return shape;
    }

    T &operator[](size_t n)
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
        for (size_t i = 0; i < pData->size(); i++)
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