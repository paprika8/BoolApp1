#include "..\..\terms\term.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>

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
    random_device rd;
    auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();

    mt19937 gen(seed);
    uniform_int_distribution<> dis(0, 15);

    int num = dis(gen);

    cout << "Guess the name of the function by its vector. Name from 1 to 16.\nYou have three attempts\n";
    cout << "\nVector of function: (";

    vector<bool> vf(4);
    for (int i = 3; i >= 0; --i)
    {
        // Сдвигаем биты вправо и проверяем значение текущего бита
        int bit = (num >> i) & 1;
        vf[(i + 4) % 4] = bit;
    }
    for (auto el : vf)
    {
        cout << el;
    }
    cout << ')' << endl;
    int i = 0;
    int ans;
    cout << "\nEnter the function name:\n";
    while (i < 3)
    {
        cin >> ans;
        i++;
        if (ans != num + 1)
        {
            cout << "Incorrect.\n";
        }
        else
        {
            cout << "That's right! Well done, take a pie from the shelf!";
            break;
        }
    }
    cout << "Game over";
}