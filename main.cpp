#include <iostream>

#include "test_common/test_traverse.hpp"
#include "test_common/test_lambda.hpp"

#include "test_algorithm/test_sort.hpp"

int main(int argc, char** argv) {

    test_traverse();
    test_lambda();

    test_sort();

//    std::cout << "Hello, World!" << std::endl;
    return 0;
}