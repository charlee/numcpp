#include <vector>
#include "catch.hpp"
#include "numcpp.h"

using std::vector;
using namespace numcpp;

TEST_CASE("Should compute dot product correctly", "[Vec_dot]") {

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> b({2.0, 4.0, 6.0});
    Vec<float> r({2.0, 12.0, 30.0});

    REQUIRE(dot(a, b) == r);
}

TEST_CASE("Should compute negative correctly", "[Vec_negative]") {

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> r({-1.0, -3.0, -5.0});

    REQUIRE(-a == r);
}

TEST_CASE("Should compute addition correctly", "[Vec_addition]") {

    Vec<float> a({1.0, 3.0, 5.0});
    Vec<float> b({2.0, 4.0, 6.0});
    Vec<float> r({3.0, 7.0, 11.0});

    REQUIRE(a + b== r);
}