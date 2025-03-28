#pragma once
#include "..\..\terms\term.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <utility>
#include <typeinfo> // Для typeid (может потребоваться)
#include <sstream>
#include <string>

namespace task6
{
    using namespace std;

    bool is_literal(term *t);

    bool is_dnf(term *t);

    bool is_and_child_dnf(term *t);

    vector<bool> generate_vf(int n);

    wstring main(wstring in);
}