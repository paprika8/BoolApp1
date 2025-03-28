#include "..\..\terms\term.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>
#include <string>

using namespace std;

wstringstream out;
wstringstream in;
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

int main()
{
    wstring input, result = L"";
    in >> input;
    vector<bool> vf;
    int amt_x = getPowerOfTwo(input.size());
    bool is_full = true;

    if (input.size() != 1 << amt_x)
    {
        out << L"Incorrect vector of function!" << endl;
        return 0;
    }

    for (auto el : input)
    {
        vf.push_back(el - 48);
        is_full = is_full & bool(el - 48);
    }

    if (is_full)
    {
        out << L"Since this is a all-ones vector, there is no CNF." << endl;
        return 0;
    }

    for (int i = 0; i < vf.size(); i++)
    {
        if (!vf[i])
        { // Если нулевой бит
            result += L"(";
            for (int j = 1; j <= amt_x; j++)
            {
                // out << L"i = " << ((i >> 0) & 1) << L' ' << ((i >> 1) & 1) << endl;
                // out << L"(i << amt_x - j) & 1 = " << ((i << j) & 1) << endl;
                if (!((i >> amt_x - j) & 1)) // если ноль
                {                            // Проверяем значение переменной на 0 или 1
                    result += L"x" + to_wstring(j);
                }
                else // если один
                {
                    result += L"!x" + to_wstring(j);
                }
                if (j != amt_x)
                {
                    result += L"|";
                }
            }
            result += L") & ";
        }
    }
    result.erase(result.end() - 3, result.end());
    out << result;
}