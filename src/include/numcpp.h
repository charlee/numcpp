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

#define NUMCPP_SHAPE_MISMATCH -1

namespace numcpp
{

template <typename T>
constexpr const T &clamp(const T &v, const T &lo, const T &hi)
{
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
    bool useIndex;
    vector<long> index;

  public:
    /**
     * Init a Vec with shape
     */
    Vec(int shape) : shape(shape), size(shape), useIndex(false)
    {
        pData = shared_ptr<vector<T>>(new vector<T>(shape));
    }

    /**
     * Init a Vec with data (std::vector<T>)
     */
    Vec(vector<T> data) : useIndex(false)
    {
        pData = shared_ptr<vector<T>>(new vector<T>(data));
        shape = data.size();
        size = shape;
    }

    /**
     * Copy constructor.
     * This constructor will literally copy the data from v
     * (with v's index).
     */
    Vec(const Vec<T> &v): Vec(v.getShape())
    {
        for (long i = 0; i < getShape(); i++) {
            (*this)[i] = v[i];
        }
    }

    long getSize() const
    {
        return useIndex ? index.size() : size;
    }

    long getShape() const
    {
        return useIndex ? index.size() : shape;
    }

    T &operator[](long n) const
    {
        return useIndex ? (*pData)[index[n]] : (*pData)[n];
    }

    /**
     * Slice.
     */
    Vec<T> operator()(Range range) const
    {
        Vec<T> r(*this);
        vector<long> index = range.seq(getSize());
        if (useIndex)
        {
            // combine two indicies
            vector<long> p(index.size());
            for (long i = 0; i < index.size(); i++)
            {
                p[i] = r.index[index[i]];
            }
            r.index = p;
        }
        else
        {
            r.index = index;
        }
        r.useIndex = true;
        return r;
    }

    Vec<T> operator-() const
    {
        Vec<T> r(*this);
        for (long i = 0; i < r.getShape(); i++)
        {
            r[i] = -r[i];
        }

        return r;
    }

    Vec<T> &operator+=(const Vec<T> &rhs)
    {
        if (getShape() != rhs.getShape())
        {
            throw NUMCPP_SHAPE_MISMATCH;
        }

        for (long i = 0; i < getShape(); i++)
        {
            (*this)[i] += rhs[i];
        }

        return *this;
    }

    Vec<T> &operator+=(const T rhs) {
        for (long i = 0; i < getShape(); i++)
        {
            (*this)[i] += rhs;
        }

        return *this;
    }

    friend Vec<T> operator+(Vec<T> lhs, const Vec<T> &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    friend Vec<T> operator+(Vec<T> lhs, const T rhs)
    {
        lhs += rhs;
        return lhs;
    }

    string as_string() const
    {
        std::stringstream s;
        const size_t size = getSize();
        s << "Vec(" << size << ")[";
        for (long i = 0; i < size; i++)
        {
            if (i != 0)
            {
                s << ", ";
            }
            s << (*this)[i];
        }

        s << "]";

        return s.str();
    }
};

template <typename T>
inline bool operator==(const Vec<T> &lhs, const Vec<T> &rhs)
{

    if (lhs.getShape() != rhs.getShape())
    {
        return false;
    }

    for (long i = 0; i < lhs.getShape(); i++)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }

    return true;
}

template <typename T>
Vec<T> dot(Vec<T> a, Vec<T> b)
{
    // Check if shape matches
    if (a.getShape() != b.getShape())
    {
        throw NUMCPP_SHAPE_MISMATCH;
    }

    long shape = a.getShape();
    Vec<T> r(shape);
    for (long i = 0; i < shape; i++)
    {
        r[i] = a[i] * b[i];
    }

    return r;
}

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