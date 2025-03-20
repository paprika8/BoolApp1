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
    uniform_int_distribution<> dis(1, 4);
    int amt_x = dis(gen);

    vector<bool> v = generate_vf(amt_x); // Система предлагает вектор функции

    cout << "Enter a DNF, that would be suitable for this vector: (";

    for (auto el : v)
    {
        cout << el;
    }
    cout << ")" << endl;

    string str;
    getline(cin, str);
    char *ch = str.data();
    BoolApp::term *t = BoolApp::parsing(ch);
    BoolApp::termData td;
    set<string> st;
    t->get_name_list(st);

    st.erase(string("0"));
    st.erase(string("1"));

    /*for (auto el : st)
    {
        cout << el << endl;
    }*/

    vector<pair<bool, string>> vf;
    for (auto el : st)
    {
        vf.push_back(pair<bool, string>{0, el});
    }
    BoolApp::termData data;
    vector<bool> res;
    for (int i = 0; i < (1 << vf.size()); i++)
    {
        for (int j = 0; j < vf.size(); j++)
        {
            data.nametovar[vf[j].second] = i & (1 << j);
        }
        res.push_back(t->calculate(data));
    }
    cout << endl;
    if (res.size() != v.size())
    {
        cout << "Wrong answer." << endl;
        return 0;
    }

    /*for (auto el : res)
    {
        cout << el;
    }
    cout << endl;*/

    for (int i = 0; i < v.size(); i++)
    {
        if (res[i] != v[i])
        {
            cout << "Wrong answer." << endl;
            return 0;
        }
    }

    cout << "Correct answer!" << endl;
}