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

namespace task7
{
    using namespace std;

    bool is_literal(term *t);

    bool is_clause(term *t);

    bool is_cnf(term *t);

    vector<bool> generate_vf(int n);

    wstring main(wstring in);
}