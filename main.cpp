#include "custom_vector.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <vector>
void TestAccessOperator() {
    try {
        CustomVector<int64_t> vec(3, 5);
        if (vec[0] != 5) {
            throw std::runtime_error("Wrong element value receive");
        }
        vec[0] = 10;
        if (vec[0] != 10) {
            throw std::runtime_error("Wrong element after change");
        }
        std::cout << "TestAccessOperator passed!\n";
    } catch(const std::runtime_error&e) {
         std::cout << "TestAccessOperator failed: " << e.what() << std::endl;
    }
}

void TestAtMethod() {
    try {
        CustomVector<int> vec(3, 5);
        if (vec.at(1) != 5) {
            throw std::runtime_error("Wrong element value receive");
        }
        vec.at(1) = 20;
        if (vec.at(1) != 20) {
            throw std::runtime_error("Wrong element after change");
        }
        try {
            vec.at(5);
            throw std::runtime_error("No exception after request outside the bounds of the array");
        } catch(const std::out_of_range e) {
            std::cout << "TestAtMethod passed!\n";
        }

    } catch(const std::runtime_error e) {
        std::cout << "TestAtMethod failed: " << e.what() << std::endl;   
    }
}
void TestPushBackPopBackMethods() {
    try {
        CustomVector<int> vec;
        vec.push_back(5);
        if (vec.size() != 1) {
            throw std::runtime_error("Wrong vector size after 1 push");
        }
        if (vec[0] != 5){
            throw std::runtime_error("Wrong value after 1 push");
        }
        vec.clear();
        std::vector<int>add={1,2,3,4,5,6,10};
        for (auto&c : add) {
            vec.push_back(c);
        }
        if (vec.size() != add.size()) {
            throw std::runtime_error("Wrong vector size");
        }
        for (int i=0; i < vec.size(); ++i) {
            if (vec[i] != add[i]) {
                throw std::runtime_error("Wrong value after push");
            }
        }
        vec.pop_back();
        add.pop_back();
        if (vec.size() != add.size()) {
            throw std::runtime_error("Wrong vector size after pop");
        }
        for (int i=0; i < vec.size(); i++) {
            if (vec[i] != add[i]) {
                throw std::runtime_error("Wrong value after pop");
            }
        }
        std::cout << "TestPushBackPopBackMethods passed!\n";
    } catch(const std::runtime_error&e) {
         std::cout << "TestPushBackPopBackMethods failed: " << e.what() << std::endl;
    }
}

void TestReserveAndShrinkToFit() {
    try {
        CustomVector<int>a(7);
        std::vector<int>b(7);
        a.reserve(10);
        b.reserve(10);
        if (a.capacity() != b.capacity()) {
            throw std::runtime_error("Vectors have different capacity");
        }
        a.reserve(0);
        b.reserve(0);
        if (a.capacity() != b.capacity()) {
            throw std::runtime_error("Vectors have different capacity");
        }
        a.shrink_to_fit();
        b.shrink_to_fit();
        if (a.capacity() != b.capacity()) {
            throw std::runtime_error("Vectors have different capacity");
        }
        std::cout << "TestReserveAndShrinkToFit passed!\n";
    } catch(const std::runtime_error&e) {
         std::cout << "TestReserveAndShrinkToFit failed: " << e.what() << std::endl;
    }
}

void TestResizeMethod() {
    try {
        CustomVector<int> vec(3, 5);
        vec.resize(5,10);
        if (vec.size() != 5) {
            throw std::runtime_error("Vector have wrong size after resize");
        }
        if (vec[3] != 10) {
            throw std::runtime_error("Receive wrong value after resize");
        }
        vec.resize(2);
        if (vec.size() != 2) {
            throw std::runtime_error("Vector have wrong size after resize");
        }
        std::cout << "TestResizeMethod passed!\n";
    } catch(const std::runtime_error&e) {
         std::cout << "TestResizeMethod failed: " << e.what() << std::endl;
    }
}

void TestInsertMethod() {
    try {
        CustomVector<int>a;
        a.assign({1,2,3});
        std::vector<int>b = {1,2,3};
        a.insert(a.begin() + 1, 5);
        b.insert(b.begin() + 1, 5);
        if (a.size() != b.size()) {
            throw std::runtime_error("Vectors have different size after insert");
        }
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                throw std::runtime_error("Vectors net equal after insert");
            }
        }
        std::cout << "TestInsertMethod passed!\n";
    } catch(const std::runtime_error&e) {
         std::cout << "TestInsertMethod failed: " << e.what() << std::endl;
    }
}

void TestEraseMethod() {
    try {
        CustomVector<int> a = {1, 2, 3, 4};
        std::vector<int> b = {1,2,3,4};
        a.erase(a.begin() + 1);
        b.erase(b.begin() + 1);
        if (a.size() != b.size()) {
            throw std::runtime_error("Vectors have different size after erase");
        }
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                throw std::runtime_error("Vectors net equal after erase");
            }
        }
        std::cout << "TestEraseMethod passed!\n";
    } catch(const std::runtime_error&e) {
         std::cout << "TestEraseMethod failed: " << e.what() << std::endl;
    }
}

void TestSwapMethod() {
    try {
        CustomVector<int> a1 = {1, 2, 3};
        CustomVector<int> a2 = {4, 5};
        std::vector<int> b1 = {1,2,3};
        std::vector<int> b2 = {4,5};
        a1.swap(a2);
        b1.swap(b2);
        if (a1.size() != b1.size()) {
            throw std::runtime_error("Vectors have different size after swap");
        }
        for (int i = 0; i < a1.size(); ++i) {
            if (a1[i] != b1[i]) {
                throw std::runtime_error("Vectors net equal after swap");
            }
        }

        if (a2.size() != b2.size()) {
            throw std::runtime_error("Vectors have different size after swap");
        }
        for (int i = 0; i < a2.size(); ++i) {
            if (a2[i] != b2[i]) {
                throw std::runtime_error("Vectors net equal after swap");
            }
        }
        std::cout << "TestSwapMethod passed!\n";
    } catch(const std::runtime_error&e) {
         std::cout << "TestSwapMethod failed: " << e.what() << std::endl;
    }
}

void TestEmplace() {
    try {
        {
            CustomVector<int>a;
            std::vector<int>b;
            auto it1 = a.emplace(a.begin(),10);
            auto it2 = b.emplace(b.begin(),10);

            a.emplace(a.end(),20);
            b.emplace(b.end(),20);
            a.emplace(a.begin() + 1, 15);
            b.emplace(b.begin() + 1, 15);
            if (a.size() != b.size()) {
                throw std::runtime_error("Vectors have different size after emplace");
            }
            for (int i = 0; i < a.size(); ++i) {
                if (a[i] != b[i]) {
                    throw std::runtime_error("Vectors net equal after emplace");
                }
            }
        }
        {
            struct Point {
                int x, y;
                Point(int x_, int y_) : x(x_), y(y_) {}
                Point():  x(0), y(0) {}
            };
            CustomVector<Point>a(0);
            std::vector<Point>b(0);
            a.emplace(a.begin(),1,2);
            b.emplace(b.begin(),1,2);
            a.emplace(a.end(),3,4);
            b.emplace(b.end(),3,4);
            if (a.size() != b.size()) {
                throw std::runtime_error("Vectors have different size after emplace");
            }
            for (int i = 0; i < a.size(); ++i) {
                if (a[i].x != b[i].x || a[i].y != b[i].y) {
                    throw std::runtime_error("Vectors net equal after emplace");
                }
            }
        }
        std::cout << "TestEmplace passed!\n";
    } catch(const std::runtime_error&e) {
         std::cout << "TestEmplace failed: " << e.what() << std::endl;
    }
}


void TestMatrix() {
    try {
        std::vector<std::vector<uint64_t>>b(3,std::vector<uint64_t>(5,10));
        CustomVector<CustomVector<uint64_t>>a(3,CustomVector<uint64_t>(5,10));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (a[i][j] != b[i][j]) {
                    throw std::runtime_error("Matrix not equal");
                }
            }
        }
        std::cout << "TestMatrix passed!\n";
    } catch(const std::runtime_error&e) {
         std::cout << "TestMatrix failed: " << e.what() << std::endl;
    }
}

signed main() {
    TestAccessOperator();
    TestAtMethod();
    TestPushBackPopBackMethods();
    TestReserveAndShrinkToFit();
    TestResizeMethod();
    TestInsertMethod();
    TestEraseMethod();
    TestSwapMethod();
    TestEmplace();
    TestMatrix();
    return 0;
}