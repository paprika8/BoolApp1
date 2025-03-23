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

using namespace BoolApp;

bool is_literal(term *t)
{
    if (!t)
        return false;
    // Литерал: переменная или отрицание переменной
    if (dynamic_cast<termVAR *>(t))
        return true;
    if (auto not_term = dynamic_cast<termNOT *>(t))
    {
        return dynamic_cast<termVAR *>(not_term->t1) != nullptr;
    }
    return false;
}

bool is_clause(term *t)
{
    if (auto or_term = dynamic_cast<termOR *>(t))
    {
        // Дизъюнкт: OR литералов или вложенных дизъюнктов
        return is_clause(or_term->t1) && is_clause(or_term->t2);
    }
    return is_literal(t); // Литерал — тривиальный дизъюнкт
}

bool is_cnf(term *t)
{
    if (!t)
        return false;

    // Запрещённые операторы (например, равенство)
    if (dynamic_cast<termEQUAL *>(t))
        return false;

    // Если текущий узел — AND, проверяем оба поддерева
    if (auto and_term = dynamic_cast<termAND *>(t))
    {
        return is_cnf(and_term->t1) && is_cnf(and_term->t2);
    }

    // Если текущий узел — OR, проверяем, что это допустимый дизъюнкт
    if (auto or_term = dynamic_cast<termOR *>(t))
    {
        return is_clause(or_term);
    }

    // Литералы разрешены (тривиальная КНФ: один дизъюнкт)
    return is_literal(t);
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
    uniform_int_distribution<> dis(1, 4);
    int amt_x = dis(gen);

    vector<bool> v = generate_vf(amt_x); // Система предлагает вектор функции

    cout << "Enter a CNF, that would be suitable for this vector: (";

    for (auto el : v)
    {
        cout << el;
    }
    cout << ")" << endl;

    string str;
    getline(cin, str);
    char *ch = str.data();
    BoolApp::term *t = BoolApp::parsing(ch);

    // Проверка на КНФ
    if (!t)
    {
        cout << "Invalid expression." << endl;
        return 0;
    }

    if (!is_cnf(t))
    {
        cout << "Wrong answer. Not a CNF." << endl;
        return 0;
    }

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