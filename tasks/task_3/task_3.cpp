#include "..\..\terms\term.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

int countDigits(int number)
{
    if (number == 0)
    {
        return 1; // Число 0 имеет одну цифру
    }

    int count = 0;
    while (number != 0)
    {
        number /= 10; // Убираем последнюю цифру
        count++;
    }
    return count;
}

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

void log_table(vector<bool> &v)
{
    int n = getPowerOfTwo(v.size());

    cout << '|';
    for (int i = 1; i <= n; i++)
    {
        cout << " x" << i << " |";
    }
    cout << " f |" << '\n';
    for (int i = 0; i < v.size(); i++)
    {
        cout << '|';

        for (int j = n - 1; j >= 0; j--)
        {
            int offs = 1 << j;
            bool t = i & offs;

            for (int k = 0; k < countDigits(n - j) + 1; k++)
            {
                cout << ' ';
            }
            cout << t << " |";
        }

        cout << ' ' << v[i] << " |" << '\n';
    }
}

int main()
{
    string ost1, ost2;
    cin >> ost1 >> ost2;
    int x_num;
    cin >> x_num;

    int sz = ost1.size() + ost2.size();
    int group_amt = twoInPower(x_num - 1);
    int step = sz / group_amt;
    int start_pos = sz / twoInPower(x_num);

    int i_ost = 0;
    vector<bool> res(sz);
    for (int i = 0; i < sz; i += step)
    {
        for (int j = 0; j < start_pos; j++)
        {
            res[i + j] = ost1[i_ost] - 48;
            i_ost++;
        }
    }
    i_ost = 0;
    for (int i = start_pos; i < sz; i += step)
    {
        for (int j = 0; j < start_pos; j++)
        {
            res[i + j] = ost2[i_ost] - 48;
            i_ost++;
        }
    }

    for (auto el : res)
    {
        cout << el << ' ';
    }
}