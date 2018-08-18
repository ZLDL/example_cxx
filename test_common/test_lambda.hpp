//
// Created by Wangzhuxing on 2018/8/18.
//

#ifndef EXAMPLE_CXX_TEST_LAMBDA_HPP
#define EXAMPLE_CXX_TEST_LAMBDA_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

/// 1. 使用Lambda表达式替代函数
bool Compare(const int val1, const int val2) {
    return val1 < val2;
}
int test_lambda_1() {
    std::cout << "--------" << __FUNCTION__ << std::endl;
    std::vector<int> vec = {1, 3, 9, 2, 6, 4};
#if 0   // use old
    std::sort(vec.begin(), vec.end(), Compare);
#else   // use lambda
    std::sort(vec.begin(), vec.end(), [](const int val1, const int val2){
        return val1 < val2;
    });
#endif
    for (auto val : vec) {
        std::cout << val << ", ";
    }
    std::cout << std::endl;

    return  0;
}

/// 2. Lambda catch args
int test_lambda_2() {
    std::cout << "--------" << __FUNCTION__ << std::endl;
    int l_iNum = 1;
    double l_dVal = 1.11;
    std::string l_str = "Hello World 1";

    //值传递方式传递父作用域变量
    auto l_func1 = [l_iNum, l_str] {
        std::cout << "func1: " << l_iNum << ", " << l_str << std::endl;
    };
    l_func1();

    //值传递捕获所有父作用域变量
    auto l_func2 = [=] {
        std::cout << "func2: " << l_iNum << ", " << l_dVal << ", " << l_str << std::endl;
    };
    l_func2();

    //引用传递捕获父作用域变量
    auto l_func3 = [&l_iNum, &l_dVal] {
        l_iNum = 333;
        l_dVal = 3.33;
    };
    l_func3();
    std::cout << "func3: " << l_iNum << ", " << l_dVal << std::endl;

    //引用传递捕获所有父作用域变量
    auto l_func4 = [&] {
        l_iNum = 444;
        l_dVal = 4.44;
        l_str = "Hello World 4";
    };
    l_func4();
    std::cout << "func4: " << l_iNum << ", " << l_dVal << ", " << l_str << std::endl;

    //值传递某个父作用域变量，引用传递其它变量
    auto l_func5 = [&, l_iNum] {
        //l_iNum++;		//此处编译器报错
        l_dVal = 5.55;
        l_str = "Hello World 5";
        std::cout << "func5: " << l_iNum;
    };
    l_func5();
    std::cout << ", " << l_dVal << ", " << l_str << std::endl;

    //引用传递某个父作用域变量，值传递其它变量
    auto l_func6 = [=, &l_str] {
        l_str = "HelloWorld 6";
        std::cout << "func6: " << l_iNum << ", " << l_dVal;
    };
    l_func6();
    std::cout << ", " << l_str << std::endl;
    return 0;
}

/// 3. Lambda in class.
class SomeClass
{
public:
    void doLambda()
    {
        std::vector<int> l_vec = { 1, 2, 3 };
        for_each(l_vec.begin(), l_vec.end(), [this](const int val) {
            std::cout << val * m_privateVal << ", ";
        });
        std::cout << std::endl;
    }

private:
    int m_privateVal = 4;
};
int test_lambda_3() {
    std::cout << "--------" << __FUNCTION__ << std::endl;
    SomeClass l_someClass;
    l_someClass.doLambda();
    return 0;
}

int test_lambda() {
    std::cout << "--------" << __FUNCTION__ << "--------" << std::endl;

    test_lambda_1();
    test_lambda_2();
    test_lambda_3();

    return 0;
}

#endif //EXAMPLE_CXX_TEST_LAMBDA_HPP
