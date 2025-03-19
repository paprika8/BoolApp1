#include "..\..\terms\term.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

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