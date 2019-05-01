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

    Vec<float> r4({2.0, 4.0, 6.0});
    REQUIRE(1 + a == r4);
}

TEST_CASE("Should compute subtraction correctly", "[Vec_subtraction]")
{

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> b({2.0, 4.0, 6.0});
    Vec<float> r1({-1.0, -1.0, -1.0});

    REQUIRE(a - b == r1);

    Vec<float> r2({0.5, 2.5, 4.5});
    REQUIRE(a - 0.5 == r2);

    Vec<float> r3({-8.0, -6.0});
    REQUIRE(b({0, 2}) - 10.0 == r3);

    Vec<float> r4({-1.0, -3.0, -5.0});
    REQUIRE(0.0 - a == r4);
}

TEST_CASE("Should compute multiplication correctly", "[Vec_multiplication]")
{

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> b({0.5, 0.1, 0.2});
    Vec<float> r1({0.5, 0.3, 1.0});

    REQUIRE(a * b == r1);

    Vec<float> r2({0.5, 1.5, 2.5});
    REQUIRE(a * 0.5 == r2);

    REQUIRE(0.5 * a == r2);
}

TEST_CASE("Should compute division correctly", "[Vec_division]")
{

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> b({0.5, 0.1, 0.2});
    Vec<float> r1({2.0, 30.0, 25.0});

    REQUIRE(a / b == r1);

    Vec<float> r2({0.5, 1.5, 2.5});
    REQUIRE(a / 2 == r2);

    Vec<float> r3({15.0, 5.0, 3.0});
    REQUIRE(15.0 / a == r3);
}