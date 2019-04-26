#include <vector>
#include "catch.hpp"
#include "numcpp.h"


using std::vector;
using namespace numcpp;

TEST_CASE("Should generate correct series when step = 1", "[Range]") {

    Range s1;
    vector<long>r1 = {0, 1, 2, 3, 4};
    REQUIRE(s1.seq(5) == r1);

    Range s2(5);
    vector<long>r2 = {5, 6, 7, 8};
    REQUIRE(s2.seq(9) == r2);

    Range s3(-1);
    vector<long>r3 = {8};
    REQUIRE(s3.seq(9) == r3);
}