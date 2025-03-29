#pragma once
#include "..\..\terms\term.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>
#include <string>

namespace task10
{
    using namespace std;

    int getPowerOfTwo(size_t n);

    vector<bool> generate_vf();

    bool is_in_T0(vector<bool> &vf);

    bool is_in_T1(vector<bool> &vf);

    bool is_in_S(vector<bool> &vf);

    bool is_in_M(vector<bool> &vf);

    bool is_in_L(vector<bool> &vf);

    vector<bool> main(const vector<bool> &vf);
}