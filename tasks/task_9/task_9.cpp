#include "..\..\terms\term.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

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
    string input, result = "";
    cin >> input;
    vector<bool> vf;
    int amt_x = getPowerOfTwo(input.size());
    bool is_full = true;

    if (input.size() != 1 << amt_x)
    {
        cout << "Incorrect vector of function!" << endl;
        return 0;
    }

    for (auto el : input)
    {
        vf.push_back(el - 48);
        is_full = is_full & bool(el - 48);
    }

    if (is_full)
    {
        cout << "Since this is a all-ones vector, there is no CNF." << endl;
        return 0;
    }

    for (int i = 0; i < vf.size(); i++)
    {
        if (!vf[i])
        { // Если нулевой бит
            result += "(";
            for (int j = 1; j <= amt_x; j++)
            {
                // cout << "i = " << ((i >> 0) & 1) << ' ' << ((i >> 1) & 1) << endl;
                // cout << "(i << amt_x - j) & 1 = " << ((i << j) & 1) << endl;
                if (!((i >> amt_x - j) & 1)) // если ноль
                {                            // Проверяем значение переменной на 0 или 1
                    result += "x" + to_string(j);
                }
                else // если один
                {
                    result += "!x" + to_string(j);
                }
                if (j != amt_x)
                {
                    result += "|";
                }
            }
            result += ") & ";
        }
    }
    result.erase(result.end() - 3, result.end());
    cout << result;
}