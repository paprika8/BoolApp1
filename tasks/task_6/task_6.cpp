#include "..\..\terms\term.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <utility>

using namespace std;

random_device rd;
auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();
mt19937 gen(seed);

int twoInPower(int power)
{
    if (power == 0)
        return 1;

    int res = 2;
    while (power > 1)
    {
        res <<= 1;
        power--;
    }
    return res;
}

vector<bool> generate_vf(int n)
{
    long long k = 1LL << n;
    vector<bool> f(k); // 2^n

    uniform_int_distribution<> dis(0, 1); // Равномерное распределение для 0 и 1

    for (int i = 0; i < k; i++)
    {
        f[i] = dis(gen);
    }

    return f;
}

int main()
{
    vector<bool> v = generate_vf(3); // Система предлагает вектор функции
    string str;
    getline(cin, str);
    char *ch = str.data();
    BoolApp::term *t = BoolApp::parsing(ch);
    BoolApp::termData td;
    set<string> st;
    t->get_name_list(st);

    st.erase(string("0"));
    st.erase(string("1"));

    for (auto el : st)
    {
        cout << el << endl;
    }

    vector<pair<bool, string>> vf;
    for (auto el : st)
    {
        vf.push_back(pair<bool, string>{0, el});
    }
    BoolApp::termData data;
    for (int i = 0; i < (1 << vf.size()); i++)
    {
        for (int j = 0; j < vf.size(); j++)
        {
            data.nametovar[vf[j].second] = i & (1 << j);
        }
        cout << t->calculate(data) << endl;
    }
}