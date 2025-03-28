#include "..\..\terms\term.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>
#include <string>

using namespace std;

wstringstream main(wstringstream in)
{
    wstringstream out;
    random_device rd;
    auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();

    mt19937 gen(seed);
    uniform_int_distribution<> dis(0, 15);

    int num = dis(gen);

    out << L"Guess the name of the function by its vector. Name from 1 to 16.\nYou have three attempts\n";
    out << L"\nVector of function: (";

    vector<bool> vf(4);
    for (int i = 3; i >= 0; --i)
    {
        // Сдвигаем биты вправо и проверяем значение текущего бита
        int bit = (num >> i) & 1;
        vf[(i + 4) % 4] = bit;
    }
    for (auto el : vf)
    {
        out << el;
    }
    out << L')' << endl;
    int i = 0;
    int ans;
    out << L"\nEnter the function name:\n";
    while (i < 3)
    {
        in >> ans;
        i++;
        if (ans != num + 1)
        {
            out << L"Incorrect.\n";
        }
        else
        {
            out << L"That's right! Well done, take a pie from the shelf!";
            break;
        }
    }
    out << L"Game over";
    return out;
}