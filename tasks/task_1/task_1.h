#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <sstream>
#include <string>


using namespace std;

namespace task1
{
    int countDigits(int number);

    int getPowerOfTwo(size_t n);

    void log_table(vector<bool> &v, wstringstream &out);
    //| x1 | x2 | f |
    //|  0 |  0 | 1 |
    //|  0 |  1 | 0 |
    //|  1 |  0 | 1 |
    //|  1 |  1 | 0 |
    wstring main(wstring in);
}