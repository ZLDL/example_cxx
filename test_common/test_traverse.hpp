//
// Created by Wangzhuxing on 2018/8/18.
//

#ifndef EXAMPLE_CXX_TEST_TRAVERSE_HPP
#define EXAMPLE_CXX_TEST_TRAVERSE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int test_traverse()
{
    std::vector<std::string> strVec = { "hello", "world", "!" };
    // 使用下标遍历
    for (int i = 0; i < strVec.size(); i++) {
        std::cout << strVec[i] << std::endl;
    }

    // 使用迭代器遍历
    for (auto itor = strVec.begin(); itor != strVec.end(); itor++) {
        std::cout << *itor << std::endl;
    }

    // 使用 for (T var : Vec) 遍历
    for (auto str : strVec) {
        std::cout << str << std::endl;
    }

    // 使用 for (T& var : Vec) 对容器批量修改
    for (auto& str : strVec) {
        str += "_new,";
    }

    // 使用 for each (T var in Vec) 遍历容器
//    for each(auto str in strVec) {
//        std::cout << str << std::endl;
//    }

    // 使用 for_each(Vec.begin(), Vec.end()
    std::string strAll;
    for_each(strVec.begin(), strVec.end(), [&strAll](std::string var){
        strAll += var;
    });
    std::cout << strAll << std::endl;

    return 0;
}

#endif //EXAMPLE_CXX_TEST_TRAVERSE_HPP
