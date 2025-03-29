#pragma once
#include "..\..\terms\term.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <set>
#include <string>

namespace task12
{
    using namespace std;
    using namespace BoolApp;

    int getPowerOfTwo(size_t n);

    vector<bool> generate_vf();

    vector<bool> generate_vf(int n);

    wstring main(wstring in);
}