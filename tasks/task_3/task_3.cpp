#include "..\..\terms\term.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <sstream>
namespace task3
{
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

    wstringstream main(wstringstream in)
    {
        wstringstream out;
        wstring ost1, ost2;
        in >> ost1 >> ost2;
        int x_num;
        in >> x_num;

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
                res[i + j] = ost1[i_ost] - L'0';
                i_ost++;
            }
        }
        i_ost = 0;
        for (int i = start_pos; i < sz; i += step)
        {
            for (int j = 0; j < start_pos; j++)
            {
                res[i + j] = ost2[i_ost] - L'0';
                i_ost++;
            }
        }

        for (auto el : res)
        {
            out << el << L' ';
        }
        return out;
    }
}