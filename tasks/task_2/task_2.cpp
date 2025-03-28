#include "..\..\terms\term.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <sstream>

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
    return 1 << power;
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

//| x1 | x2 | x3 | f |
//|  0 |  0 |  0 | 0 |
//|  0 |  0 |  0 | 0 |
//|  0 |  0 |  1 | 0 |
//|  0 |  0 |  1 | 0 |
wstringstream main(wstringstream in)
{
    wstringstream out;
    wstring str;
    getline(in, str);
    vector<bool> f;
    int i = 0;
    while (str[i] != L' ')
    {
        // out << str[i] << endl;
        f.push_back(bool(str[i] - L'0'));
        i++;
    }
    i++;
    bool ost_val = bool(str[i] - L'0');
    i += 2;
    int x_num = int(str[i] - L'0');
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

    out << endl;
    for (auto el : ostat)
    {
        out << el;
    }
    out << endl;
    return out;
}