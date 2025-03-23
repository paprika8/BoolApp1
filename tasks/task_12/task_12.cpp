#include "..\..\terms\term.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

random_device rd;
auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();
mt19937 gen(seed);

int getPowerOfTwo(size_t n)
{
    if (n == 0)
    {
        return -1;
    }

    int power = 0;
    while (n > 1)
    {
        n >>= 1;
        power++;
    }

    return power;
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

bool is_in_T0(vector<bool> &vf)
{
    return !vf[0];
}

bool is_in_T1(vector<bool> &vf)
{
    return vf[vf.size() - 1];
}

bool is_in_S(vector<bool> &vf)
{
    auto l = vf.begin();
    auto r = vf.end() - 1;
    for (int i = 0; i < vf.size() / 2; i++, l++, r--)
    {
        if (*l == *r)
        {
            return false;
        }
    }
    return true;
}

bool is_in_M(vector<bool> &vf)
{
    int amt_x = getPowerOfTwo(vf.size());

    for (int i = 0; i < vf.size() - 1; i++)
    {
        for (int j = i + 1; j < vf.size(); j++)
        {
            bool more = 0, less = 0;
            for (int k = 1; k <= amt_x; k++)
            {
                bool first_bit = ((i >> amt_x - k) & 1);
                bool second_bit = ((j >> amt_x - k) & 1);

                if (first_bit < second_bit)
                {
                    less = true;
                }
                if (first_bit > second_bit)
                {
                    more = true;
                }
            }
            if (more && less)
            {
                continue;
            }
            if (less)
            {
                if (vf[i] > vf[j])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool is_in_L(vector<bool> &vf)
{
    int amt_x = getPowerOfTwo(vf.size());
    vector<bool> buf = vf;
    for (int i = 1; i < buf.size(); i++)
    {
        for (int j = i; j < buf.size(); j++)
        {
            buf[j] = (!buf[j - 1] && buf[j] || buf[j - 1] && !buf[j]); // Сложение по модулю два
            if (buf[j] && j == i)
            {
                int cnt = 0;
                for (int k = 1; k <= amt_x; k++) // смотрим на количество
                {
                    if (((i >> amt_x - k) & 1)) // если один
                    {
                        cnt++;
                    }
                }
                if (cnt > 1)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int main()
{
    uniform_int_distribution<> dis_amt_sets(1, 5);
    int amt_vec = dis_amt_sets(gen);

    // T0, T1, S, M, L - классы
    //  0,  1, 2, 3, 4 - индексы
    vector<bool> f_types(5, 1);

    while (amt_vec--)
    {

        /*uniform_int_distribution<> dis(1, 4);
        int amt_x = dis(gen);

        vector<bool> vf = generate_vf(amt_x); // Система предлагает вектор функции
*/
        // Для отладки:
        string input;
        cin >> input;
        vector<bool> vf;
        for (auto el : input)
        {
            vf.push_back(el - 48);
        }

        cout << "Vector of function: (";
        for (auto el : vf)
        {
            cout << el;
        }
        cout << ")\n";

        if (!is_in_T0(vf))
        {
            f_types[0] = false;
        }
        if (!is_in_T1(vf))
        {
            f_types[1] = false;
        }
        if (!is_in_S(vf))
        {
            f_types[2] = false;
        }
        if (!is_in_M(vf))
        {
            f_types[3] = false;
        }
        if (!is_in_L(vf))
        {
            f_types[4] = false;
        }
    }

    if (f_types[0] && f_types[1] && f_types[2] && f_types[3] && f_types[4])
    {
        cout << "System is complete.\n";
        return 0;
    }
    else
    {
        cout << "System is incomplete.\nEnter the enclosed class which the function is in.\n";
        }
}