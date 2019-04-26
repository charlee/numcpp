#include <iostream>
#include "numcpp.h"

using numcpp::Vec;

int main() {

    // Vec<float> A(6);
    Vec<float> B({ 1, 2, 3});
    // Vec<float> C = A;

    // std::cout << A.as_string() << std::endl;
    std::cout << B.as_string() << std::endl;
    // std::cout << C.as_string() << std::endl;

    // A[2] = 10;
    // std::cout << A.as_string() << std::endl;
    // std::cout << A[2] << std::endl;

    // std::cout << C.as_string() << std::endl;

    Vec<float> D = B({2});
    std::cout << D.as_string() << std::endl;
}