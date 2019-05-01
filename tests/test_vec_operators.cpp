#include <vector>
#include "catch.hpp"
#include "numcpp.h"

using std::vector;
using namespace numcpp;

TEST_CASE("Should compute dot product correctly", "[Vec_dot]")
{

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> b({2.0, 4.0, 6.0});
    Vec<float> r({2.0, 12.0, 30.0});

    REQUIRE(dot(a, b) == r);
}

TEST_CASE("Should compute negative correctly", "[Vec_negative]")
{

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> r({-1.0, -3.0, -5.0});

    REQUIRE(-a == r);
}

TEST_CASE("Should compute addition correctly", "[Vec_addition]")
{

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> b({2.0, 4.0, 6.0});
    Vec<float> r1({3.0, 7.0, 11.0});

    REQUIRE(a + b == r1);

    Vec<float> r2({11.0, 13.0, 15.0});
    REQUIRE((a + 10.0f) == r2);

    Vec<float> r3({12.0, 14.0});
    REQUIRE(b({0, 2}) + 10.0 == r3);
}

TEST_CASE("Should compute subtraction correctly", "[Vec_addition]")
{

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> b({2.0, 4.0, 6.0});
    Vec<float> r1({-1.0, -1.0, -1.0});

    REQUIRE(a - b == r1);

    Vec<float> r2({0.5, 2.5, 4.5});
    REQUIRE(a - 0.5 == r2);
}