#pragma once
#include "..\..\terms\term.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <utility>
#include <sstream>
#include <string>

namespace task5
{
    using namespace std;

    int twoInPower(int power);

    int getPowerOfTwo(size_t n);

    vector<bool> makeVecFromOstat(wstring ost1, wstring ost2, int x_num);

    bool has_dum_val(vector<bool> &vf);

    wstring main();
}