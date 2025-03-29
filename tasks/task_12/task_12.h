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

    // Литерал: пара (имя переменной, отрицание)
    using Literal = std::pair<std::wstring, bool>;
    using Conjunct = std::set<Literal>;

    int getPowerOfTwo(size_t n);

    vector<bool> generate_vf();

    vector<bool> generate_vf(int n);

    wstring perfect_dnf(int amt_x, const vector<bool> &vf);

    void collect_conjunct(const term *t, Conjunct &current);

    vector<Conjunct> collect_conjuncts(const term *t);

    term *build_term(const vector<Conjunct> &conjuncts);

    vector<Conjunct> parse_conjuncts_from_string(const wstring &expr);

    bool can_merge(const Conjunct &a, const Conjunct &b, Conjunct &merged);

    vector<Conjunct> quine_minimization(const vector<Conjunct> &terms);

    bool is_tautology(const vector<Conjunct> &minimized, int var_count);

    vector<Conjunct> minimize_dnf(const vector<Conjunct> &conjuncts, int var_count);

    wstring main(wstring in);
}