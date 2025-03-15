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
//| x1 | x2 | x3 | f |
//|  0 |  0 |  0 | 0 |
//|  0 |  0 |  0 | 0 |
//|  0 |  0 |  1 | 0 |
//|  0 |  0 |  1 | 0 |
int main()
{
    string str;
    getline(cin, str);
    vector<bool> f;
    int i = 0;
    while (str[i] != ' ')
    {
        // cout << str[i] << endl;
        f.push_back(bool(str[i] - 48));
        i++;
    }
    i++;
    bool ost_val = bool(str[i] - 48);
    i += 2;
    int x_num = int(str[i] - 48);
    int amt_of_x = getPowerOfTwo(f.size());

    int group_amt = twoInPower(x_num - 1);
    int start_pos = f.size() / twoInPower(x_num);
    int step = f.size() / group_amt;

    vector<bool> ostat(twoInPower(amt_of_x - 1));
    int i_ost = 0;
    for (int i = ost_val * (start_pos); i < f.size(); i += step)
    {
        for (int j = 0; j < start_pos; j++)
        {
            ostat[i_ost] = f[i + j];
            i_ost++;
        }
    }

    cout << endl;
    for (auto el : ostat)
    {
        cout << el;
    }
    cout << endl;
}