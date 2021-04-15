#include <Testing.h>
#include <iostream>
#include <cxxabi.h>

std::vector<Test*> Test::_tests;

void Test::Register(Test* test) {
    _tests.emplace_back(test);
}

const char* Test::getName() {
    int status;
    return abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
}

void Test::run() {
    std::cout << "Running suite " << getName() << std::endl;
    for(auto test : _tests) {
        std::cout << "  " << test->getName() << ": ";
        std::flush(std::cout);
        test->run();
        std::cout << "OK" << std::endl;
    }
    std::cout << std::endl;
}
